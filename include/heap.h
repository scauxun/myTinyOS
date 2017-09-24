#ifndef INCLUDE_HEAP_H_
#define INCLUDE_HEAP_H_

#include "types.h"

#define HEAP_START 0xE0000000

typedef
struct header {
	struct header *prev; 	
	struct header *next;
	u32int allocated : 1;	 // 该块内存是否已被申请
	u32int length : 31;      // 当前内存块的长度
} header_t;

void init_heap();

// 申请内存
void *kmalloc(u32int len);

// 释放内存
void kfree(void *p);

void test_heap();

#endif 
