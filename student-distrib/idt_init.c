/* idt_ini,c - Function)s to initialize idt_handler
*/
#include "idt_init.h"
#include "IRQ.h"


/*
 * void idt_handler_setup()
 *    DESCRIPTION:
 *      set up the IDT handler
 *    INPUT:
 *      none
 *    OUTPUT:
 *      none
 */
void idt_handler_setup()
{
    int i;
    for(i=0;i<SIZE_IDT;i++)
    {
        SET_IDT_ENTRY(idt[i],IntHandler);
    }
    SET_IDT_ENTRY(idt[0],IntHandler_0);
    SET_IDT_ENTRY(idt[1],IntHandler_1);
    SET_IDT_ENTRY(idt[2],IntHandler_2);
    SET_IDT_ENTRY(idt[3],IntHandler_3);
    SET_IDT_ENTRY(idt[4],IntHandler_4);
    SET_IDT_ENTRY(idt[5],IntHandler_5);
    SET_IDT_ENTRY(idt[6],IntHandler_6);
    SET_IDT_ENTRY(idt[7],IntHandler_7);
    SET_IDT_ENTRY(idt[8],IntHandler_8);
    SET_IDT_ENTRY(idt[9],IntHandler_9);
    SET_IDT_ENTRY(idt[10],IntHandler_10);
    SET_IDT_ENTRY(idt[11],IntHandler_11);
    SET_IDT_ENTRY(idt[12],IntHandler_12);
    SET_IDT_ENTRY(idt[13],IntHandler_13);
    SET_IDT_ENTRY(idt[14],IntHandler_14);
    SET_IDT_ENTRY(idt[15],IntHandler_15);
    SET_IDT_ENTRY(idt[16],IntHandler_16);
    SET_IDT_ENTRY(idt[17],IntHandler_17);
    SET_IDT_ENTRY(idt[18],IntHandler_18);
    SET_IDT_ENTRY(idt[19],IntHandler_19);
    SET_IDT_ENTRY(idt[20],IntHandler_20);
    SET_IDT_ENTRY(idt[21],IntHandler_21);
    SET_IDT_ENTRY(idt[32],IntHandler_32);
    SET_IDT_ENTRY(idt[33],IntHandler_33);
    SET_IDT_ENTRY(idt[40],IntHandler_40);
    SET_IDT_ENTRY(idt[128],IntHandler_128);
}


/*
 * void idt_init(int i)
 *    DESCRIPTION:
 *      initialize IDT
 *    INPUT:
 *      int i  -- index
 *    OUTPUT:
 *      none
 */
void idt_init()
{
    int i;
    idt_handler_setup();

    for(i=0;i<SIZE_IDT;i++)
    {
        /* check if the entry is an interrupt or exception */
        if(i<SIZE)
        {
            /* set the entry as an trap gate */
            idt[i].present = 1;
            idt[i].dpl = 0;
            idt[i].reserved0 = 0;
            idt[i].size  = 1;
            idt[i].reserved1 = 1;
            idt[i].reserved2 = 1;
            idt[i].reserved3 = 1;
            idt[i].reserved4 = 0;
            idt[i].seg_selector = KERNEL_CS;
        }
        else
        {
            /* set the entry as an interrupt gate */
            idt[i].present = 1;
            idt[i].dpl = i==0x80? 3:0;
            idt[i].reserved0 = 0;
            idt[i].size  = 1;
            idt[i].reserved1 = 1;
            idt[i].reserved2 = 1;
            idt[i].reserved3 = 0;
            idt[i].reserved4 = 0;
            idt[i].seg_selector = KERNEL_CS;
        }
    }
}
