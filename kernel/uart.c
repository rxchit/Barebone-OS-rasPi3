#include "kernel/uart.h"

void init_uart1() {
    register unsigned int r;

    // initialize UART1
    *UART1_ENABLE |= 1;
    *UART1_CNTL = 0;
    *UART1_LCR = 3;
    *UART1_MCR = 0;
    *UART1_IER = 0;
    *UART1_IIR = 0xC6;
    *UART1_BAUD = 270;

    // map to gpio pins
    r = *GPFSEL1;
    r &= ~((7 << 12) | (7 << 15));
    r |= (2 << 12) | (2 << 15);
    *GPFSEL1 = r;

    *GPPUD = 0;
    r = 150; while (r--) { asm volatile("nop"); } 
    *GPPUDCLK0 = (1 << 14) | (1 << 15);
    r = 150; while (r--) { asm volatile("nop"); }
    *GPPUDCLK0 = 0;

    *UART1_CNTL = 3;
}

char uart1_getc() {
    do { asm volatile("nop"); } while (!(*UART1_LSR & 0x01));

    char c = (char)(*UART1_IO);

    return (c == '\r') ? '\n' : c;
}

void uart1_send(unsigned int c) {
    do { asm volatile("nop"); } while (!(*UART1_LSR & 0x20));

    *UART1_IO = c;
}

void uart1_puts(char *str) {
    for (; *str; ++str) {
        if (*str == '\n') {
            uart1_send('\r');
        }
        uart1_send(*str);
    }
}
