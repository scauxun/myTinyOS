#ifndef INCLUDE_GDT_H_
#define INCLUDE_GDT_H_

#include "types.h"

// 全局描述符类型
typedef
struct gdt_entry_t {
	u16int limit_low;     // 段界限   15～0
	u16int base_low;      // 段基地址 15～0
	u8int  base_middle;   // 段基地址 23～16
	u8int  access;        // 段存在位、描述符特权级、描述符类型、描述符子类别
	u8int  granularity; 	// 其他标志、段界限 19～16
	u8int  base_high;     // 段基地址 31～24
} __attribute__((packed)) gdt_entry_t;

// GDTR
typedef
struct gdt_ptr_t {
	u16int limit; 	// 全局描述符表限长
	u32int base; 		// 全局描述符表 32位 基地址
} __attribute__((packed)) gdt_ptr_t;

// 初始化全局描述符表
void init_gdt();

// GDT 加载到 GDTR 的函数[汇编实现]
extern void gdt_flush(u32int);

#endif 	// INCLUDE_GDT_H_
