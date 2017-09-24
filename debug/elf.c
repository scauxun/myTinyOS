#include "common.h"
#include "string.h"
#include "elf.h"
#include "vmm.h"

// 从multiboot_t结构体中获取ELF信息
elf_t elf_from_multiboot(multiboot_t *mb)
{
	int i;
	elf_t elf;
	elf_section_header_t *sh = (elf_section_header_t *)mb->addr;

	u32int shstrtab = sh[mb->shndx].addr;
	for (i = 0; i < mb->num; i++) {
		const char *name = (const char *)(shstrtab + sh[i].name) + PAGE_OFFSET;
		if (strcmp(name, ".strtab") == 0) {
			elf.strtab = (const char *)sh[i].addr + PAGE_OFFSET;
			elf.strtabsz = sh[i].size;
		}
		if (strcmp(name, ".symtab") == 0) {
			elf.symtab = (elf_symbol_t *)(sh[i].addr + PAGE_OFFSET);
			elf.symtabsz = sh[i].size;
		}
	}

	return elf;
}

// 查看ELF的符号信息
const char *elf_lookup_symbol(u32int addr, elf_t *elf)
{
	int i;

	for (i = 0; i < (elf->symtabsz / sizeof(elf_symbol_t)); i++) {
		if (ELF32_ST_TYPE(elf->symtab[i].info) != 0x2) {
		      continue;
		}
		if ( (addr >= elf->symtab[i].value) && (addr < (elf->symtab[i].value + elf->symtab[i].size)) ) {
			return (const char *)((u32int)elf->strtab + elf->symtab[i].name);
		}
	}

	return NULL;
}

