#include <stdio.h>

#include "terminal.h"

typedef struct
{
    short width;
    short height;
    bool  valid;

} terminal_size_t;

static bool
enable_virtual_terminal_mode( void );

static bool
enable_console_input_events( void );

static terminal_size_t
get_terminal_size( HANDLE output_handle );


terminal_t
create_terminal( void )
{
    terminal_t result = { 0 };
    if( !enable_virtual_terminal_mode() )
    {
        fprintf( stderr, "[ERROR] Could not enable virtual terminal mode"); // TODO[Jeppe]: Change this to use some kind of logging
        return result;
    }

    if( !enable_console_input_events() )
    {
        fprintf( stderr, "[ERROR] Could not enable console input events"); // TODO[Jeppe]: Change this to use some kind of logging
        return result;
    }

    const HANDLE output_handle = GetStdHandle( STD_OUTPUT_HANDLE );
    if( output_handle == INVALID_HANDLE_VALUE )
    {
        fprintf( stderr, "[ERROR] Could not get output handle"); // TODO[Jeppe]: Change this to use some kind of logging
        return result;
    }

    const HANDLE input_handle = GetStdHandle( STD_INPUT_HANDLE );
    if( input_handle == INVALID_HANDLE_VALUE ) {
        fprintf( stderr, "[ERROR] Could not get input handle"); // TODO[Jeppe]: Change this to use some kind of logging
        return result;
    }

    const terminal_size_t size = get_terminal_size( output_handle );
    if( !size.valid )
    {
        fprintf( stderr, "[ERROR] Could not get terminal size"); // TODO[Jeppe]: Change this to use some kind of logging
        return result;
    }

    result = (terminal_t)
    {
        .output_handle = output_handle,
        .input_handle  = input_handle,
        .valid         = true
    };

    return result;
}



static bool
enable_virtual_terminal_mode( void )
{
    
    const HANDLE output_handle = GetStdHandle( STD_OUTPUT_HANDLE );
    if( output_handle == INVALID_HANDLE_VALUE ) {
        return false;
    }

    DWORD buffer_mode = 0;
    if( !GetConsoleMode(output_handle, &buffer_mode ) ) {
        return false;
    }

    buffer_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if( !SetConsoleMode( output_handle, buffer_mode ) ) {
        return false;
    }

    return true;
}

static bool
enable_console_input_events( void )
{
    const HANDLE input_handle = GetStdHandle( STD_INPUT_HANDLE );
    if( input_handle == INVALID_HANDLE_VALUE ) {
        return false;
    }

    const DWORD buffer_mode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if( !SetConsoleMode( input_handle, buffer_mode ) ) {
        return false;
    }

    return true;
}

static terminal_size_t
get_terminal_size( HANDLE output_handle )
{
    terminal_size_t result = { 0 };

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info = { 0 };
    if( !GetConsoleScreenBufferInfo( output_handle, &screen_buffer_info ) )
    {
        return result;
    }

    const short width  = screen_buffer_info.srWindow.Right - screen_buffer_info.srWindow.Left + 1;
    const short height = screen_buffer_info.srWindow.Bottom - screen_buffer_info.srWindow.Top + 1;
            
    result = ( terminal_size_t )
    {
        .width  = width,
        .height = height,
        .valid  = true
    };

    return result;
}
