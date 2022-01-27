// // https://github.com/bztsrc/raspi3-tutorial/blob/master/10_virtualmemory/mmu.c
// #include "kernel/mmu.h"
// #include "kernel/mmio.h"

// extern volatile unsigned char __data_start;
// extern volatile unsigned char __end;

// extern void enable_mmu();

// void init_mmu() {
//     unsigned long data_page = (unsigned long)&__data_start/PAGESIZE;
//     unsigned long *paging = (unsigned long *)&__end;
//     unsigned long b;

//     /* create mmu translation tables at __end */

//     // TTBR0, identity L1
//     paging[0] = (unsigned long)((unsigned char *)&__end+2*PAGESIZE)
//         | PT_PAGE
//         | PT_AF
//         | PT_USER
//         | PT_ISH
//         | PT_MEM;

//     // identity L2, first 512M block
//     paging[2*512] = (unsigned long)((unsigned char *)&__end+3*PAGESIZE)
//         | PT_PAGE
//         | PT_AF
//         | PT_USER
//         | PT_ISH
//         | PT_MEM;

//     // identity L2 2M blocks
//     b = MMIO_BASE >> 21;
//     for (unsigned long i=0; i < 512; ++i) {
//         paging[2*512+i] = (unsigned long)(i << 21)
//             | PT_BLOCK
//             | PT_AF
//             | PT_NX
//             | PT_USER
//             | (i >= b ? (PT_OSH | PT_DEV) : (PT_ISH | PT_MEM));  // different attributes for device mem
//     }

//     // identity L3
//     for (unsigned long i=0; i < 512; ++i) {
//         paging[3*512+i] = (unsigned long)(i*PAGESIZE)
//             | PT_PAGE
//             | PT_AF
//             | PT_USER
//             | PT_ISH
//             | ((i < 0x80 || i >= data_page) ? (PT_RW | PT_NX) : PT_RO);  // different for code and data
//     }

//     // TTBR1, kernel L1
//     paging[512+511] = (unsigned long)((unsigned char *)&__end+4*PAGESIZE)
//         | PT_PAGE
//         | PT_AF
//         | PT_KERNEL
//         | PT_ISH
//         | PT_MEM;

//     // kernel L2
//     paging[4*512+511] = (unsigned long)((unsigned char *)&__end+5*PAGESIZE)
//         | PT_PAGE
//         | PT_AF
//         | PT_KERNEL
//         | PT_ISH
//         | PT_MEM;

//     // kernel L3
//     paging[5*512] = (unsigned long)(MMIO_BASE+0x00201000)
//         | PT_PAGE
//         | PT_AF
//         | PT_NX
//         | PT_KERNEL
//         | PT_OSH
//         | PT_DEV;

//     // Call assembly to enable mmu
//     enable_mmu();
// }
