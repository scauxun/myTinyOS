#ifndef INCLUDE_TASK_H_
#define INCLUDE_TASK_H_

#include "types.h"
#include "pmm.h"
#include "vmm.h"

typedef
enum task_state {
	TASK_UNINIT = 0, 	
	TASK_SLEEPING = 1, 	
	TASK_RUNNABLE = 2, 	
	TASK_ZOMBIE = 3, 	
} task_state;

struct context {
	u32int esp;
	u32int ebp;
	u32int ebx;
	u32int esi;
	u32int edi;
	u32int eflags;
};

struct mm_struct {
	pgd_t *pgd_dir; 	
};

struct task_struct {
	volatile task_state state; 	
	pid_t 	 pid; 		
	void  	*stack; 		
	struct mm_struct *mm; 	
	struct context context; 
	struct task_struct *next; 	
};

extern pid_t now_pid;

i32int kernel_thread(int (*fn)(void *), void *arg);

void kthread_exit();

#endif 	// INCLUDE_TASK_H_

