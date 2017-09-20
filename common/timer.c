#include "timer.h"
#include "debug.h"
#include "common.h"
#include "idt.h"
#include "sched.h"

void timer_callback(pt_regs *regs)
{
	schedule();
}

void init_timer(u32int frequency)
{
	register_interrupt_handler(IRQ0, timer_callback);

	u32int divisor = 1193180 / frequency;

	outb(0x43, 0x36);

	u8int low = (u8int)(divisor & 0xFF);
	u8int hign = (u8int)((divisor >> 8) & 0xFF);
	
	outb(0x40, low);
	outb(0x40, hign);
}
