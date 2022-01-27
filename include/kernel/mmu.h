#ifndef _KERNEL_MMU_H_
#define _KERNEL_MMU_H_

#define PAGESIZE 4096

#define PT_PAGE  0b11
#define PT_BLOCK 0b01

#define PT_KERNEL   (0 << 6)     // EL1 access level
#define PT_USER     (1 << 6)     // EL0 access level
#define PT_RW       (0 << 7)     // read-write access
#define PT_RO       (1 << 7)     // read only
#define PT_AF       (1 << 10)    // access flag
#define PT_NX       (1UL << 54)  // no execute

#define PT_OSH (2 << 8)  // outer shareable
#define PT_ISH (3 << 8)  // inner shareable

#define PT_MEM (0 << 2)  // normal memory
#define PT_DEV (1 << 2)  // MMIO
#define PT_NC  (2 << 2)  // non-cacheable

#define TTBR_CNP 1

#ifndef __ASSEMBLY__
void init_mmu();
#endif  // __ASSEMBLY__

#endif  // _KERNEL_MMU_H_
