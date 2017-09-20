#ifndef INCLUDE_MULTIBOOT_H_
#define INCLUDE_MULTIBOOT_H_

#include "types.h"

typedef
struct multiboot_t {
	u32int flags;			// Multiboot 的版本信息

	u32int mem_lower;
	u32int mem_upper;

	u32int boot_device;	
	u32int cmdline;	
	u32int mods_count;	
	u32int mods_addr;
	

	u32int num;
	u32int size;
	u32int addr;
	u32int shndx;

	u32int mmap_length;		
	u32int mmap_addr;
	
	u32int drives_length; 	
	u32int drives_addr; 		
	u32int config_table; 		
	u32int boot_loader_name; 	
	u32int apm_table; 	    
	u32int vbe_control_info;
	u32int vbe_mode_info;
	u32int vbe_mode;
	u32int vbe_interface_seg;
	u32int vbe_interface_off;
	u32int vbe_interface_len;
} __attribute__((packed)) multiboot_t;


typedef
struct mmap_entry_t {
	u32int size; 		
	u32int base_addr_low;
	u32int base_addr_high;
	u32int length_low;
	u32int length_high;
	u32int type;
} __attribute__((packed)) mmap_entry_t;


extern multiboot_t *mboot_ptr_tmp;

extern multiboot_t *glb_mboot_ptr;

#endif 	// INCLUDE_MULTIBOOT_H_
