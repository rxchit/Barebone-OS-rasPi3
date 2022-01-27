.globl delay

delay:
    subs x0, x0, #1
    cbnz x0, delay
    ret
