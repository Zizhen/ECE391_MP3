#ifndef _KEYBOARD
#define _KEYBOARD

#include "lib.h"
#include "terminal.h"

extern int keyboard_read(int scan);

extern void clear_screen();

extern void delete_char();

extern void flush_line_buffer();

#endif
