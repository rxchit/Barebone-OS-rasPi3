#include <stdint.h>

#include "kernel/gpio.h"
#include "kernel/uart.h"

/*
    All it does is call the init_uart function, print "Hello, World!", and print out any character you type
*/

void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3)
// atags, and pointer to the atags
{
    init_uart1();

    // uart1_puts("Hello World!\n");
    uart1_puts("Hello rxchit!\n");      // the print statement 

    while (1)
    {
        uart1_send(uart1_getc());       // this prints all the input to the console *loops forever*
    }
}
