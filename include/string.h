#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_

#include "types.h"

void memcpy(u8int *dest, const u8int *src, u32int len);

void memset(void *dest, u8int val, u32int len);

void bzero(void *dest, u32int len);

int strcmp(const char *str1, const char *str2);

char *strcpy(char *dest, const char *src);

char *strcat(char *dest, const char *src);

int strlen(const char *src);

#endif 	// INCLUDE_STRING_H_
