#ifndef _TERMINAL_H
#define _TERMINAL_H

#include "lib.h"

extern unsigned char buffer[128];

extern int index;

extern int terminal_write(unsigned char *c,int length);

extern int terminal_read(unsigned char *ret_buf,int length);

extern int terminal_open();

extern int terminal_close();

#endif
