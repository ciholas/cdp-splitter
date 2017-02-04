//Ciholas, Inc. - www.ciholas.com
//Licensed under: creativecommons.org/licenses/by/4.0
#ifndef _UTILS__DESTINATION__H
#define _UTILS__DESTINATION__H
#include <stdint.h>
#include <netinet/in.h>  


/*********************
* Public Types
**********************/
typedef struct DESTINATION_T{ 
    struct DESTINATION_T * next;
    int    socket;
    struct sockaddr_in address;
}destination_t;


/*********************
* Public Functions
**********************/
void Destination_Create(char * ip, char * port);
destination_t * Destination_GetFirst(void);

#endif
