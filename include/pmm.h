#ifndef INCLUDE_PMM_H
#define INCLUDE_PMM_H

#include "multiboot.h"

#define STACK_SIZE 8192

#define PMM_MAX_SIZE 0x20000000

#define PMM_PAGE_SIZE 0x1000

#define PAGE_MAX_SIZE (PMM_MAX_SIZE/PMM_PAGE_SIZE)

#define PHY_PAGE_MASK 0xFFFFF000

extern u8int kern_start[];
extern u8int kern_end[];

extern u32int phy_page_count;

void show_memory_map();

void init_pmm();

u32int pmm_alloc_page();

void pmm_free_page(u32int p);

#endif 	// INCLUDE_PMM_H

