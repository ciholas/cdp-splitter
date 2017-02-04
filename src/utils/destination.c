//Ciholas, Inc. - www.ciholas.com
//Licensed under: creativecommons.org/licenses/by/4.0
#include "destination.h"
#include "utils/print.h"
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*********************
* Private Variables
**********************/
static destination_t * __first_destination = NULL;
static destination_t * __last_destination  = NULL;


/*********************
* Public Functions
**********************/
void Destination_Create(char * ip, char * port){
    bool _failure = false;

    // Check to see if the ip string was found
    if (ip == NULL) {
        Print_Line("Err: Missing ip field\n");
        _failure = true;
    }
    
    // Check to see if the port string was found
    if (port == NULL) {
        Print_Line("Err: Missing port field\n");
        _failure = true;
    }

    if (_failure) {
        Print_Line("CSV Format: `<IPv4 destination addr>:<IPv4 destination port>`\n");
        return;
    }

    //we are going to assume that the destination isn't already in the list when creating
    destination_t * _new = (destination_t *) malloc(sizeof(destination_t));
    if(_new){
        _new->next = NULL;

        if((_new->socket = socket(AF_INET,SOCK_DGRAM, 0)) < 0)
            Print_ExitOnError("socket()");

        memset(&_new->address, 0, sizeof(_new->address));
        _new->address.sin_family = AF_INET;
        _new->address.sin_addr.s_addr = inet_addr(ip);
        _new->address.sin_port = htons(atoi(port));
        
        Print_Line("Adding %s:%d", ip, atoi(port) & 0xffff);
        if(__last_destination)
            __last_destination->next = _new;
        __last_destination = _new;
        if(__first_destination == NULL)
            __first_destination = _new;
    }
}

destination_t * Destination_GetFirst(void){
    return __first_destination;
}
