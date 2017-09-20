[GLOBAL gdt_flush]

gdt_flush:
	mov eax, [esp+4] ; eax就是GDT的地址
	lgdt [eax]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush   ; 远跳转，0x08是我们的代码段描述符
			  ; 远跳目的是清空流水线并串行化处理器
.flush:
	ret
