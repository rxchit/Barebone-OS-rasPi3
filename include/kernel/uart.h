#ifndef _KERNEL_UART_H_
#define _KERNEL_UART_H_

#include "kernel/gpio.h"

#define UART1_ENABLE    ((volatile unsigned int *)(MMIO_BASE+0x00215004))
#define UART1_IO        ((volatile unsigned int *)(MMIO_BASE+0x00215040))
#define UART1_IER       ((volatile unsigned int *)(MMIO_BASE+0x00215044))
#define UART1_IIR       ((volatile unsigned int *)(MMIO_BASE+0x00215048))
#define UART1_LCR       ((volatile unsigned int *)(MMIO_BASE+0x0021504C))
#define UART1_MCR       ((volatile unsigned int *)(MMIO_BASE+0x00215050))
#define UART1_LSR       ((volatile unsigned int *)(MMIO_BASE+0x00215054))
#define UART1_MSR       ((volatile unsigned int *)(MMIO_BASE+0x00215058))
#define UART1_SCRATCH   ((volatile unsigned int *)(MMIO_BASE+0x0021505C))
#define UART1_CNTL      ((volatile unsigned int *)(MMIO_BASE+0x00215060))
#define UART1_STAT      ((volatile unsigned int *)(MMIO_BASE+0x00215064))
#define UART1_BAUD      ((volatile unsigned int *)(MMIO_BASE+0x00215068))

void init_uart1();

char uart1_getc();
void uart1_send(unsigned int c);
void uart1_puts(char *str);

#endif  // _KERNEL_UART_H_
