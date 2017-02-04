//Ciholas, Inc. - www.ciholas.com
//Licensed under: creativecommons.org/licenses/by/4.0
#include <errno.h>  
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>


/*********************
* Public Functions
**********************/
void  Print_ExitOnError(const char *on_what) {  
    fputs(strerror(errno),stderr);  
    fputs(": ",stderr);  
    fputs(on_what,stderr);  
    fputc('\n',stderr);  
    exit(1);  
}  
int Print_Line(const char * format, ...){
    struct timeval _cur_time;
    struct tm * _human_time;
    char _time_string[100];
    va_list _args;
    int _rv;

    //get timestamp
    gettimeofday(&_cur_time, NULL);
    _human_time = localtime(&_cur_time.tv_sec);
    strftime(_time_string, 100, "%F %T", _human_time);

    //print
    printf("%s.%06d - ", _time_string, (int)_cur_time.tv_usec);
    va_start(_args, format);
    _rv = vprintf(format, _args);
    va_end(_args);
    printf("\r\n");
    fflush(stdout);

    return _rv;
}
void Print_ExitOnMessage(int exit_code, const char *format, ...){
    FILE * _fs = stderr;
    if(exit_code == 0)
        _fs = stdout;
    va_list _args;
    va_start(_args, format);
    vfprintf(_fs, format, _args);
    va_end(_args);
    fflush(_fs);
    exit(exit_code);
}
