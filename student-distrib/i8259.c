/* i8259.c - Functions to interact with the 8259 interrupt controller
 * vim:ts=4 noexpandtab
 */

#include "i8259.h"
#include "lib.h"

/* Interrupt masks to determine which interrupts
 * are enabled and disabled */
uint8_t master_mask; /* IRQs 0-7 */
uint8_t slave_mask;  /* IRQs 8-BIT_MASK5 */

/* Initialize the 8259 PIC */
/*
 *  void i8259_init(void)
 *    DESCRIPTION:
 *      initialize PIC
 *    INPUT:
 *      none
 *    OUTPUT:
 *      none
 */
void i8259_init(void)
{
    /* mask all irq on pic */
    outb(IRQ_MASK, MASTER_8259_DATA);
    outb(IRQ_MASK, SLAVE_8259_DATA);

    /* send first initial control word to master and slave */
    outb(ICW1, MASTER_8259_PORT);
    outb(ICW1, SLAVE_8259_PORT);

    /* send second initial contorl word to master and slave */
    outb(ICW2_MASTER, MASTER_8259_DATA);
    outb(ICW2_SLAVE, SLAVE_8259_DATA);

    /* send third initial control word to master and slave */
    outb(ICW3_MASTER, MASTER_8259_DATA);
    outb(ICW3_SLAVE, SLAVE_8259_DATA);

    /* send the last initial control word to master and slave */
    outb(ICW4, MASTER_8259_DATA);
    outb(ICW4, SLAVE_8259_DATA);

    /* mask all irq and pic */
    outb(IRQ_MASK, MASTER_8259_DATA);
    outb(IRQ_MASK, SLAVE_8259_DATA);
}

/* Enable (unmask) the specified IRQ */
/*  void enable_irq(uint32_t irq_num)
 *    DESCRIPTION:
 *      enable specific IRQ
 *    INPUT:
 *      none
 *    OUTPUT:
 *      none
 */
void enable_irq(uint32_t irq_num)
{
    /* check if the interrupt is on master or slave */
    if (irq_num < SLAVE_IRQ)
    {
        /* enable the irq on master */
        master_mask = inb(MASTER_8259_DATA);
        master_mask &= (~(BIT_MASK << irq_num));
        outb(master_mask, MASTER_8259_DATA);
    }
    else
    {
        /* enable irq on master */
        master_mask = inb(MASTER_8259_DATA);
        master_mask &= (~(BIT_MASK << MASTER_SLAVE));
        outb(master_mask, MASTER_8259_DATA);

        /* enable irq on slave */
        slave_mask = inb(SLAVE_8259_DATA);
        slave_mask &= (~(BIT_MASK << (irq_num - SLAVE_IRQ)));
        outb(slave_mask, SLAVE_8259_DATA);
    }
}

/* Disable (mask) the specified IRQ */
/*  void disable_irq(uint32_t irq_num)
 *    DESCRIPTION:
 *      disable specific IRQ
 *    INPUT:
 *      none
 *    OUTPUT:
 *      none
 */
void disable_irq(uint32_t irq_num)
{
    /* check if the interrupt is on master or slave */
    if (irq_num < SLAVE_IRQ)
    {
        /* disable the irq on master */
        master_mask = inb(MASTER_8259_DATA);
        master_mask |= (BIT_MASK << irq_num);
        outb(master_mask, MASTER_8259_DATA);
    }
    else
    {
        /* disable the irq on master */
        master_mask = inb(MASTER_8259_DATA);
        master_mask |= (BIT_MASK << MASTER_SLAVE);
        outb(master_mask, MASTER_8259_DATA);

        /* disable the irq on slave */
        slave_mask = inb(SLAVE_8259_DATA);
        slave_mask |= (BIT_MASK << (irq_num - SLAVE_IRQ));
        outb(slave_mask, SLAVE_8259_DATA);
    }
}

/* Send end-of-interrupt signal for the specified IRQ */
/*  void send_eoi(uint32_t irq_num)
 *    DESCRIPTION:
 *      send end of interrupt signal
 *    INPUT:
 *      none
 *    OUTPUT:
 *      none
 */
void send_eoi(uint32_t irq_num)
{
    /* check if the interrupt is on master or slave */
    if (irq_num < SLAVE_IRQ)
    {
        /* send eoi to master */
        outb(EOI | irq_num, MASTER_8259_PORT);
    }
    else
    {
        /* send eoi to slave */
        outb(EOI | (irq_num - SLAVE_IRQ), SLAVE_8259_PORT);
        /* send eoi to master */
        outb(EOI | MASTER_SLAVE, MASTER_8259_PORT);
    }
}
