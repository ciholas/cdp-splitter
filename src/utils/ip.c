//Ciholas, Inc. - www.ciholas.com
//Licensed under: creativecommons.org/licenses/by/4.0
#include <sys/types.h>
#include <ifaddrs.h> 
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/if_link.h>

#include <netinet/in.h>  
#include <net/if.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>

#include <stdio.h>
/*********************
* Public Functions
**********************/
uint32_t Ip_ForInterface(char * ifc){

    uint32_t _rv = 0;

    struct ifaddrs *ifaddr, *ifa;
    int family, s, n;

    getifaddrs(&ifaddr);
    for(ifa=ifaddr, n=0; ifa!=NULL && _rv == 0; ifa=ifa->ifa_next, n++){
        if(   ifa->ifa_addr 
           && ifa->ifa_addr->sa_family == AF_INET){
            if(strcmp(ifa->ifa_name, ifc) == 0){
                _rv = (uint32_t) ((struct sockaddr_in *)ifa->ifa_addr)->sin_addr.s_addr;
                _rv = __builtin_bswap32(_rv);
            }
        }
    }
    freeifaddrs(ifaddr);
    return _rv;
}
void Ip_DecimalToString(uint32_t ip, char * string){
    sprintf(string, "%d.%d.%d.%d", 
            (ip >> 24) & 0xff,
            (ip >> 16) & 0xff,
            (ip >>  8) & 0xff,
            (ip >>  0) & 0xff);
}
