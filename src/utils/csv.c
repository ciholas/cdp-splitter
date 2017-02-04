//Ciholas, Inc. - www.ciholas.com
//Licensed under: creativecommons.org/licenses/by/4.0
#include "utils/print.h"
#include "utils/destination.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void Csv_Read(char * file){
    FILE * _csv = fopen(file, "r");
    if(_csv == NULL)
        Print_ExitOnError("fopen");
    char _line[1024];


    while(fgets(_line, 1024, _csv)){
        char * _ip, * _port;
        _ip   = strtok(_line, ":");
        _port = strtok( NULL, ":");
        Destination_Create(_ip, _port);
    }
}
