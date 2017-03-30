#ifndef _PAGING
#define _PAGING

#ifndef ASM
#define ENABLE 1
#define DISABLE 0
#define PAGE_LARGE 1
#define PAGE_SMALL 0
#define VIDEO 0x000b8000
#define PAGE_SIZE 1024
#define KB4 4096
#define NOT_PRESENT 0
#define KERNEL_LOCATION 0x400000
#define PAGE_OTHERS 0
#define PAGE_KERNEL 1
#define ENTRY_CONTENTS 0x7
#define PAGE_SHIFT 7
#define TABLE_INDEX_SHIFT 12
#define TABLE_INDEX_MASK 0x3ff

#include "lib.h"

/* function to initialize paging */
extern void page_init();

#endif
#endif
