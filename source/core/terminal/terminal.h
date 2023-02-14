#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <stdbool.h>
#include <windows.h>

#define MAX_TITLE_SIZE 128


typedef struct 
{
    char   title[MAX_TITLE_SIZE]; 
    HANDLE output_handle;
    HANDLE input_handle;
    short  width;
    short  height;
    bool   valid;

} terminal_t;


terminal_t
create_terminal( const char *p_title );

#endif // _TERMINAL_H_
