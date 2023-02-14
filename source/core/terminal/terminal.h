#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <stdbool.h>
#include <windows.h>

typedef struct 
{
    HANDLE output_handle;
    HANDLE input_handle;
    short  width;
    short  height;
    bool   valid;
    
} terminal_t;


terminal_t
create_terminal( void );

#endif // _TERMINAL_H_
