#include "gdt.h"
#include "string.h"

#define GDT_LENGTH 5

// 全局描述符表
gdt_entry_t gdt_entries[GDT_LENGTH];

gdt_ptr_t gdt_ptr;

static void gdt_set_gate(i32int num, u32int base, u32int limit, u8int access, u8int gran);

// 声明内核地址
extern u32int stack;

// 初始化全局表述符表
void init_gdt()
{
	gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH - 1;
	gdt_ptr.base = (u32int)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);             
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); 
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); 	
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); 
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); 

	gdt_flush((u32int)&gdt_ptr);
}


static void gdt_set_gate(i32int num, u32int base, u32int limit, u8int access, u8int gran)
{
	gdt_entries[num].base_low     = (base & 0xFFFF);
	gdt_entries[num].base_middle  = (base >> 16) & 0xFF;
	gdt_entries[num].base_high    = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low    = (limit & 0xFFFF);
	gdt_entries[num].granularity  = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access       = access;
}

