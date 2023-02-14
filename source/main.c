#include <stdio.h>
#include <stdlib.h>

#include "core/terminal/terminal.h"

int
main( void )
{
    terminal_t terminal = create_terminal( "Test title" );
    if( !terminal.valid )
    {
        return EXIT_FAILURE;
    }

    while(true)
    {
        
    }
    return EXIT_SUCCESS;
}
