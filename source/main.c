#include <stdio.h>
#include <stdlib.h>

#include "core/terminal/terminal.h"

int
main( void )
{
    terminal_t terminal = create_terminal();
    if( !terminal.valid )
    {
        return EXIT_FAILURE;
    }
    
    fprintf( stdout, "Hello World!" );
    return EXIT_SUCCESS;
}
