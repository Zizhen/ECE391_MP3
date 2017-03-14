#include "paging.h"

/* an array for page directory */
static uint32_t page_directory[PAGE_SIZE] __attribute__((aligned(KB4)));
/* an array for a singel page table */
static uint32_t page_table[PAGE_SIZE] __attribute__((aligned(KB4)));

/* function to initialize an page directory entry */
static void initialize_pd_entry(int index, uint32_t addr, uint8_t type);
/* function to initialize an page table entry */
static void initialize_pt_entry(uint32_t addr);
/* function to enable paging */
static void enable(uint32_t *pd);

/*
 *  void page_init()
 *    DESCRIPTION:
 *      initialize paging
 *    INPUT:
 *      none
 *    OUTPUT:
 *      none
 *    SIDE EFFECT:
 *      set two 4mb pages in memory
 */
void page_init()
{
    int i;

    /* set all entries in the page directory and page table to 0 */
    for (i = 0; i < PAGE_SIZE; i++)
    {
        page_directory[i] = NOT_PRESENT;
        page_table[i] = NOT_PRESENT;
    }

    initialize_pd_entry(PAGE_OTHERS, (uint32_t)page_table, PAGE_SMALL);
    initialize_pd_entry(PAGE_KERNEL, KERNEL_LOCATION, PAGE_LARGE);

    initialize_pt_entry(VIDEO);

    //enable_paging();
    enable(page_directory);
}

/*
 *  void initialize_pd_entry(int index, uint32_t addr, uint8_t type)
 *    DESCRIPTION:
 *      initialize a page directory entry
 *    INPUTS:
 *      int index - the index of page directory to be changed
 *      uint32_t addr - the address for the page table that the entry point to
 *      uint8_t type - the type of the entry (4kb page or 4mb page)
 *    OUTPUTS:
 *      none
 *    SIDE EFFECTS:
 *      initialize a page directory entry
 */
void initialize_pd_entry(int index, uint32_t addr, uint8_t type)
{
    page_directory[index] = addr | ENTRY_CONTENTS | type << PAGE_SHIFT;
}

/*
 *  void initialize_pt_entry(uint32_t addr)
 *    DESCRIPTION:
 *      initialize a page table entry
 *    INPUTS:
 *      uint32_t addr - the address for the page that the entry point to
 *    OUTPUTS:
 *      none
 *    SIDE EFFECTS:
 *      initialize a page table entry
 */
void initialize_pt_entry(uint32_t addr)
{
    int ptIndex = (addr >> TABLE_INDEX_SHIFT) & TABLE_INDEX_MASK;
    page_table[ptIndex] = addr | ENTRY_CONTENTS;
}

/*
 *  enable(uint32_t *pd)
 *    DESCRIPTION:
 *      enable the page table
 *    INPUTS:
 *      uint32_t *pd - the addreess of the top of page directory
 *    OUTPUTS:
 *      none
 *    SIDE EFFECTS:
 *      enable the page table
 */
void enable(uint32_t *pd)
{
    asm volatile("              \n\
    movl %0,%%eax               \n\
    movl %%eax,%%cr3            \n\
    movl %%cr4,%%eax            \n\
    orl $0x00000010,%%eax       \n\
    movl %%eax,%%cr4            \n\
    movl %%cr0,%%eax            \n\
    orl $0x80000001,%%eax       \n\
    movl %%eax,%%cr0            \n\
    "
                 :
                 : "g"(pd)
                 : "eax");
}
