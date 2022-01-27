#include <stdint.h>

#include "kernel/gpio.h"
#include "kernel/uart.h"

void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3) {
    init_uart1();

    uart1_puts("Hello World!\n");

    while (1) {
        uart1_send(uart1_getc());
    }
}
