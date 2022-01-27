#include "kernel/mmu.h"

.globl enable_mmu

/*
 * void enable_mmu();
 */
enable_mmu:
    mrs x0, id_aa64mmfr0_el1

    and x1, x0, #0xF

    // check for 4k granule and at least 36 bits physical address bus
    and x2, x0, #0xF0000000  // 0xF << 28
    cbnz x2, _end
    cmp x1, 1
    bhi _end

    // set memory attributes array
    movz x0, #0x04FF            // ((0xFF << 0) | (0x04 << 8) | (0x44 << 16))
    movk x0, #0x44, lsl #16
    msr mair_el1, x0

    // specify mapping characteristics in translate control register
    // (0b10 << 30) | (0b11 << 28) | (0b01 << 26) | (0b01 << 24) | (25 << 16) | (0b11 << 12) | (0b01 << 10) | (0b01 << 8) | 25
    movz x0, #0x3519
    movk x0, #0xB519, lsl 16
    msr tcr_el1, x0
    isb

    // tell MMU where translation tables are
    ldr x2, =__end + TTBR_CNP
    msr ttbr0_el1, x2
    ldr x2, =__end + TTBR_CNP + PAGESIZE
    msr ttbr1_el1, x2

    // enable page translation
    dsb ish
    isb
    mrs x0, sctlr_el1

    // set mandatory bits
    movz x2, #0x0800
    movk x2, #0xC0, lsl 16
    orr x0, x0, x2

    // clear bits EE, E0E, WXN, I, SA0, SA, C, A
    movz x2, #0x101E
    movk x2, #0x308, lsl 16
    bic x0, x0, x2
    // set M bit
    orr x0, x0, #1

    msr sctlr_el1, x0
    isb

_end:
    ret
