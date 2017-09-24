#ifndef INCLUDE_VMM_H
#define INCLUDE_VMM_H

#include "types.h"
#include "idt.h"
#include "vmm.h"

// 内核的地址
#define PAGE_OFFSET 	0xC0000000


#define PAGE_PRESENT 	0x1


#define PAGE_WRITE 	0x2

#define PAGE_USER 	0x4

#define PAGE_SIZE 	4096

#define PAGE_MASK      0xFFFFF000

#define PGD_INDEX(x) (((x) >> 22) & 0x3FF)

#define PTE_INDEX(x) (((x) >> 12) & 0x3FF)

#define OFFSET_INDEX(x) ((x) & 0xFFF)

typedef u32int pgd_t;

typedef u32int pte_t;

#define PGD_SIZE (PAGE_SIZE/sizeof(pte_t))

#define PTE_SIZE (PAGE_SIZE/sizeof(u32int))

#define PTE_COUNT 128

extern pgd_t pgd_kern[PGD_SIZE];

void init_vmm();

// 更换目录页
void switch_pgd(u32int pd);

//  把物理地址映射到虚拟地址
void map(pgd_t *pgd_now, u32int va, u32int pa, u32int flags);

// 取消映射
void unmap(pgd_t *pgd_now, u32int va);

u32int get_mapping(pgd_t *pgd_now, u32int va, u32int *pa);

void page_fault(pt_regs *regs);

#endif 	// INCLUDE_VMM_H
