#ifndef _TERMINAL_H
#define _TERMINAL_H
#include "lib.h"
extern void clean_screen();
extern void delete_char();
extern void scroll();
extern void type(unsigned char input);
extern void clear_buffer();
#endif
