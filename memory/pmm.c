#include "multiboot.h"
#include "common.h"
#include "debug.h"
#include "pmm.h"

static u32int pmm_stack[PAGE_MAX_SIZE+1];

static u32int pmm_stack_top;

u32int phy_page_count;

void show_memory_map()
{
	u32int mmap_addr = glb_mboot_ptr->mmap_addr;
	u32int mmap_length = glb_mboot_ptr->mmap_length;

	printk("Memory map:\n");

	mmap_entry_t *mmap = (mmap_entry_t *)mmap_addr;
	for (mmap = (mmap_entry_t *)mmap_addr; (u32int)mmap < mmap_addr + mmap_length; mmap++) {
		printk("base_addr = 0x%X%08X, length = 0x%X%08X, type = 0x%X\n",
			(u32int)mmap->base_addr_high, (u32int)mmap->base_addr_low,
			(u32int)mmap->length_high, (u32int)mmap->length_low,
			(u32int)mmap->type);
	}
}

void init_pmm()
{
	mmap_entry_t *mmap_start_addr = (mmap_entry_t *)glb_mboot_ptr->mmap_addr;
	mmap_entry_t *mmap_end_addr = (mmap_entry_t *)glb_mboot_ptr->mmap_addr + glb_mboot_ptr->mmap_length;

	mmap_entry_t *map_entry;

	for (map_entry = mmap_start_addr; map_entry < mmap_end_addr; map_entry++) {

		if (map_entry->type == 1 && map_entry->base_addr_low == 0x100000) {
			
			u32int page_addr = map_entry->base_addr_low + (u32int)(kern_end - kern_start);
			u32int length = map_entry->base_addr_low + map_entry->length_low;

			while (page_addr < length && page_addr <= PMM_MAX_SIZE) {
				pmm_free_page(page_addr);
				page_addr += PMM_PAGE_SIZE;
				phy_page_count++;
			}
		}
	}
}

u32int pmm_alloc_page()
{
	assert(pmm_stack_top != 0, "out of memory");

	u32int page = pmm_stack[pmm_stack_top--];

	return page;
}

void pmm_free_page(u32int p)
{
	assert(pmm_stack_top != PAGE_MAX_SIZE, "out of pmm_stack stack");

	pmm_stack[++pmm_stack_top] = p;
}

