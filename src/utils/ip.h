//Ciholas, Inc. - www.ciholas.com
//Licensed under: creativecommons.org/licenses/by/4.0
#ifndef _UTILS__IP__H_
#define _UTILS__IP__H_
#include <stdint.h>


/*********************
* Public Functions
**********************/
uint32_t Ip_ForInterface(char * ifc);
void Ip_DecimalToString(uint32_t ip, char * string);
#endif
