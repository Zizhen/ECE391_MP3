#include "x86_desc.h"
#include "lib.h"
#include "i8259.h"
#include "debug.h"

#define SIZE_IDT 256
#define SIZE 32

extern void idt_handler_setup();

extern void idt_init();
