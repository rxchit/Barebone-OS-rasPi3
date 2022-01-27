.section ".text.boot"
.globl _start

.org 0xD8
spin_cpu0:
    .quad 0
.org 0xE0
spin_cpu1:
    .quad 0
.org 0xE8
spin_cpu2:
    .quad 0
.org 0xF0
spin_cpu3:
    .quad 0

.org 0x80000

.globl MMIO_BASE

// spin until function address is written to the corresponding address for this cpu
spin:
    wfe
    ldr x4, [x5, x6, lsl #3]
    cbz x4, spin
    mov x0, #0
    b boot_kernel


_start:
    // firmware *does not* ensure that this will only run on cpu0 >:(
    // spin if this isnt cpu0
    mrs x6, mpidr_el1
    and x6, x6, #3
    cbz x6, 2f

    adr x5, spin_cpu0
    b spin

2:
    // set stack pointer to address of _start
    ldr x5, =_start
    mov sp, x5

    // zero bss for crt
    ldr x5, =__bss_start
    ldr x6, =__bss_size
3:
    cbz w6, 4f
    str xzr, [x5], #8
    sub w6, w6, #1
    cbnz w6, 3b

4:
    // load address of MMIO_BASE into x10
    ldr x10, =MMIO_BASE

    // detect board type
    mrs x9, midr_el1
    lsr x9, x9, #4              // turn off all bits except 4:15
    and x9, x9, #0xFFF
    // compare and jump to corresponding branch
    cmp x9, #0xD03
    beq 5f
    cmp x9, #0xD08
    beq 6f
    // no match, halt
    mov x6, #0
    b spin

5:
    // raspberry pi 3
    mov x9, #0x3F000000
    b 7f

6:
    // raspberry pi 4
    mov x9, #0xFE000000

7:
    str x9, [x10]           // write address to MMIO_BASE
    ldr x4, =kernel_main

boot_kernel:
    mov x1, #0
    mov x2, #0
    mov x3, #0
    br x4
