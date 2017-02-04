//Ciholas, Inc. - www.ciholas.com
//Licensed under: creativecommons.org/licenses/by/4.0
#include "version.h"
#include "applications/cdp_splitter.h"
#include "utils/print.h"
#include "utils/csv.h"
#include <arpa/inet.h>
#include <stdlib.h>


int main(int argc,char **argv) {

    if(argc != 5){
        Print_ExitOnMessage(argc == 1 ? 0 : 1,
                 "Usage: %s UWB_EXT_IFC UWB_EXT_IP UWB_EXT_PORT CSV\r\n"
                 "   UWB_EXT_IFC - Interface to listen on (internal cdp interface, ie: lo) on\r\n"
                 "    UWB_EXT_IP - IP to listen for (internal cdp ip, ie: 239.255.76.67) on\r\n"
                 "  UWB_EXT_PORT - Port to listen on (internal cdp port, ie: 7667) on\r\n"
                 "           CSV - CSV file that contains lines of \"<destination IP>:<destination port>\"\r\n", argv[0]);
    }

    Print_Line("Started CDP Splitter Version: " VERSION_STRING);

    Csv_Read(argv[4]);
    AppCdpSplitter_Create(argv[1], inet_addr(argv[2]), atoi(argv[3]));

    while(1); ///@todo handle CTRL-C and HUP signals and close threads nicely

    return 0;  
}  
