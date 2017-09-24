#include "common.h"
#include "console.h"
#include "string.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "pmm.h"
#include "vmm.h"
#include "heap.h"
#include "task.h"
#include "sched.h"

void kern_init();

multiboot_t *glb_mboot_ptr;

char kern_stack[STACK_SIZE]  __attribute__ ((aligned(16)));

u32int kern_stack_top;

__attribute__((section(".init.data"))) pgd_t *pgd_tmp  = (pgd_t *)0x1000;
__attribute__((section(".init.data"))) pgd_t *pte_low  = (pgd_t *)0x2000;
__attribute__((section(".init.data"))) pgd_t *pte_hign = (pgd_t *)0x3000;

__attribute__((section(".init.text"))) void kern_entry()
{
	pgd_tmp[0] = (u32int)pte_low | PAGE_PRESENT | PAGE_WRITE;
	pgd_tmp[PGD_INDEX(PAGE_OFFSET)] = (u32int)pte_hign | PAGE_PRESENT | PAGE_WRITE;

	// 映射内核虚拟地址物理地址
	int i;
	for (i = 0; i < 1024; i++) {
		pte_low[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
	}

	for (i = 0; i < 1024; i++) {
		pte_hign[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
	}
	
	// 设置临时页表
	asm volatile ("mov %0, %%cr3" : : "r" (pgd_tmp));

	u32int cr0;

	// 启动分页
	asm volatile ("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= 0x80000000;
	asm volatile ("mov %0, %%cr0" : : "r" (cr0));
	
	// 切换内核栈
	kern_stack_top = ((u32int)kern_stack + STACK_SIZE);
	asm volatile ("mov %0, %%esp\n\t"
			"xor %%ebp, %%ebp" : : "r" (kern_stack_top));

	glb_mboot_ptr = mboot_ptr_tmp + PAGE_OFFSET;

	kern_init();
}

int flag = 0;

int thread(void *arg)
{
	while (1) {
		if (flag == 1) {
			printk_color(rc_black, rc_green, "Z");
			flag = 0;
		}
	}

	return 0;
}

void kern_init()
{
	init_debug();
	init_gdt();
	init_idt();

	console_clear();
	printk_color(rc_black, rc_green, "Hello, OS kernel!\n\n");

	init_timer(200);

	printk("kernel in memory start: 0x%08X\n", kern_start);
	printk("kernel in memory end:   0x%08X\n", kern_end);
	printk("kernel in memory used:   %d KB\n\n", (kern_end - kern_start) / 1024);
	
	init_pmm();
	init_vmm();
	init_heap();

	printk("\nThe Count of Physical Memory Page is: %u\n\n", phy_page_count);

	test_heap();

	init_sched();

	kernel_thread(thread, NULL);

	asm volatile ("sti");

    printk("\ntest task switch\nred Z and green Z represent two different tasks:\n");
	while (1) {
		if (flag == 0) {
			printk_color(rc_black, rc_red, "Z");
			flag = 1;
		}
	}

	while (1) {
		asm volatile ("hlt");
	}
}

