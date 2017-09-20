#include "string.h"

inline void memcpy(u8int *dest, const u8int *src, u32int len)
{
	for (; len != 0; len--) {
		*dest++ = *src++;
	}
}

inline void memset(void *dest, u8int val, u32int len)
{
	u8int *dst = (u8int *)dest;

	for ( ; len != 0; len--) {
		*dst++ = val;
	}
}

inline void bzero(void *dest, u32int len)
{
	memset(dest, 0, len);
}

inline int strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && (*str1++ == *str2++))
	      ;

	if (*str1 == '\0' && *str2 == '\0') {
	      return 0;
	}

	if (*str1 == '\0') {
	      return -1;
	}
	
	return 1;
}

inline char *strcpy(char *dest, const char *src)
{
	char *tmp = dest;

	while (*src) {
	      *dest++ = *src++;
	}

	*dest = '\0';
	
	return tmp;
}

inline char *strcat(char *dest, const char *src)
{
	char *cp = dest;

	while (*cp) {
	      cp++;
	}

	while ((*cp++ = *src++))
	      ;

	return dest;
}

inline int strlen(const char *src)
{
	const char *eos = src;

        while (*eos++)
	      ;
	        
	return (eos - src - 1);
}

