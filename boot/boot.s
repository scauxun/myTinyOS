MBOOT_HEADER_MAGIC 	equ 	0x1BADB002 	

MBOOT_PAGE_ALIGN 	equ 	1 << 0    	
MBOOT_MEM_INFO 		equ 	1 << 1    
					

MBOOT_HEADER_FLAGS 	equ 	MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO

MBOOT_CHECKSUM 		equ 	- (MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]  

section .init.text 


dd MBOOT_HEADER_MAGIC 
dd MBOOT_HEADER_FLAGS  
dd MBOOT_CHECKSUM     

[GLOBAL start] 	
[GLOBAL mboot_ptr_tmp] 	
[EXTERN kern_entry] 	

start:
	cli  				
	mov [mboot_ptr_tmp], ebx	
	mov esp, STACK_TOP  		
	and esp, 0FFFFFFF0H		
	mov ebp, 0 			
    
	call kern_entry	


section .init.data		; 开启分页前的临时数据段
stack:    times 1024 db 0  
STACK_TOP equ $-stack-1 	

mboot_ptr_tmp: dd 0		

