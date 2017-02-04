//Ciholas, Inc. - www.ciholas.com
//Licensed under: creativecommons.org/licenses/by/4.0
#include "utils/ip.h"
#include "utils/print.h"
#include "utils/destination.h"
#include <netinet/in.h>  
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>  
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define USE_CDP_1

/*********************
* Private Types
**********************/
typedef struct __attribute__((__packed__)){
    uint32_t magic_number;
    uint32_t sequence;
    char     string[8];
    uint32_t serial_number;
    uint8_t  data_items[];
}cdp_header_t;

typedef struct __attribute__((__packed__)){
    uint16_t type;
    uint16_t length;
    uint8_t  data[];
}cdp2_data_item_t;


/*********************
* Private Definitions
**********************/
#define _MAX_RX_SIZE 10000
#define _CDP_STRING "CDP0002"


/*********************
* Public Functions
**********************/
void AppCdpSplitter_Create(char * ifc, uint32_t ip, uint16_t port){

    uint32_t _ifc_ip = Ip_ForInterface(ifc);
    if(_ifc_ip == 0)
        Print_ExitOnMessage(1, "Unable to get IP for CDP Splitter interface: %s\n", ifc);

    int _input_socket;
    struct sockaddr_in _input_addr;
    static int _so_reuse = 1;  
    struct ip_mreq _multicast_request;
    socklen_t _addrlen = sizeof(_input_addr);

    //RX socket setup
    if((_input_socket = socket(AF_INET,SOCK_DGRAM,0)) < 0)
        Print_ExitOnError("input socket()");  
    if(setsockopt(_input_socket, SOL_SOCKET, SO_REUSEADDR, &_so_reuse, sizeof(_so_reuse)) < 0) 
        Print_ExitOnError("setsockopt(SO_REUSEADDR) input");  
    memset(&_input_addr, 0, sizeof(_input_addr));
    _input_addr.sin_family=AF_INET;
    _input_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    _input_addr.sin_port=htons(port);
    if(bind(_input_socket, (struct sockaddr *)&_input_addr, sizeof(_input_addr)) < 0)
        Print_ExitOnError("bind(2) - input");  
    //setup multicast receive
    _multicast_request.imr_multiaddr.s_addr=(ip);
    _multicast_request.imr_interface.s_addr=htonl(_ifc_ip);
    if(setsockopt(_input_socket,IPPROTO_IP,IP_ADD_MEMBERSHIP,&_multicast_request,sizeof(_multicast_request)) < 0)
        Print_ExitOnError("setsockopt - multicast input");

    //setup the input data buffer
    uint8_t _input_data[_MAX_RX_SIZE];
    cdp_header_t * _cdp_in_header = (cdp_header_t *) _input_data;

    while(1){ ///@todo stop looping on a signal received

        //receive input report
        int32_t _bytes_received = recvfrom(_input_socket, _input_data, _MAX_RX_SIZE, 0, (struct sockaddr *)&_input_addr, &_addrlen);

        if(   _bytes_received >= sizeof(cdp_header_t)
           && strcmp(_cdp_in_header->string, _CDP_STRING) == 0){
            destination_t * _destination = Destination_GetFirst();

            while(_destination){
                if (sendto(_destination->socket, (const void *) _input_data, _bytes_received, 0, (struct sockaddr *) &_destination->address, sizeof(_destination->address)) < 0)
                    Print_ExitOnError("sendto()");
                _destination = _destination->next;
            }
        }else{
            Print_ExitOnError("recvfrom(2) input");
        }
    }
}
