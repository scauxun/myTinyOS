#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include "types.h"

void outb(u16int port, u8int value);

u8int inb(u16int port);

u16int inw(u16int port);

#endif
