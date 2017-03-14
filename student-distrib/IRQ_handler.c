/* IRQ_handler.c - functions for IRQ handler */

#include "IRQ_handler.h"
#include "i8259.h"
#include "lib.h"
#include "keyScan2ascii.h"

/*  void Interrupt()
 *    DESCRIPTION: interrtup
 *  input /output : none */
void Interrupt()
{
    printf("interrupt!\n");
    while (1)
        ;
}

/*  void Interrupt_0()
 *    DESCRIPTION: exception - division by zero
 *  input /output : none */
void Interrupt_0()
{
    printf("Division by zero!\n");
    while (1)
        ;
}

/*  void Interrupt_1()
 *    DESCRIPTION: Debugger
 *  input /output : none */
void Interrupt_1()
{
    printf("Debugger!\n");
    while (1)
        ;
}

/*  void Interrupt_2()
 *    DESCRIPTION: NMI
 *  input /output : none */
void Interrupt_2()
{
    printf("NMI!\n");
    while (1)
        ;
}

/*  void Interrupt_3()
 *    DESCRIPTION: Breakpoint
 *  input /output : none */
void Interrupt_3()
{
    printf("Breakpoint!\n");
    while (1)
        ;
}

/*  void Interrupt_4()
 *    DESCRIPTION: Overflow
 *  input /output : none */
void Interrupt_4()
{
    printf("Overflow!\n");
    while (1)
        ;
}

/*  void Interrupt_5()
 *    DESCRIPTION: Bounds!
 *  input /output : none */
void Interrupt_5()
{
    printf("Bounds!\n");
    while (1)
        ;
}

/*  void Interrupt_6()
 *    DESCRIPTION: Invalid Opcode
 *  input /output : none */
void Interrupt_6()
{
    printf("Invalid Opcode!\n");
    while (1)
        ;
}

/*  void Interrupt_7()
 *    DESCRIPTION: Coprocessor not available
 *  input /output : none */
void Interrupt_7()
{
    printf("Coprocessor not available!\n");
    while (1)
        ;
}

/*  void Interrupt_8()
 *    DESCRIPTION: Double fault
 *  input /output : none */
void Interrupt_8()
{
    printf("Double fault!\n");
    while (1)
        ;
}


/*  void Interrupt_9()
 *    DESCRIPTION: Coprocessor Segment Overrun
 *  input /output : none */
void Interrupt_9()
{
    printf("Coprocessor Segment Overrun (386 or earlier only)!\n");
    while (1)
        ;
}

/*  void Interrupt_10()
 *    DESCRIPTION: Invalid Task State Segment
 *  input /output : none */
void Interrupt_10()
{
    printf("Invalid Task State Segment!\n");
    while (1)
        ;
}

/*  void Interrupt_11()
 *    DESCRIPTION:Segment not presen
 *  input /output : none */
void Interrupt_11()
{
    printf("Segment not present!\n");
    while (1)
       ;
}

/*  void Interrupt_12()
 *    DESCRIPTION: Stack Fault
 *  input /output : none */
void Interrupt_12()
{
    printf("Stack Fault!\n");
    while (1)
        ;
}

/*  void Interrupt_13()
 *    DESCRIPTION: General protection fault
 *  input /output : none */
void Interrupt_13()
{
    printf("General protection fault!\n");
    while (1)
        ;
}

/*  void Interrupt_0()
 *    DESCRIPTION: exception - division by zero
 *  input /output : none */
void Interrupt_14()
{
    printf("Page fault!\n");
    while (1)
        ;
}

/*  void Interrupt_15()
 *    DESCRIPTION: mathfault
 *  input /output : none */
void Interrupt_15()
{
    printf("reserved!\n");
    while (1)
        ;
}

/*  void Interrupt_16()
 *    DESCRIPTION: Math Fault
 *  input /output : none */
void Interrupt_16()
{
    printf("Math Fault!\n");
    while (1)
        ;
}

/*  void Interrupt_17()
 *    DESCRIPTION: Alignment Check
 *  input /output : none */
void Interrupt_17()
{
    printf("Alignment Check!\n");
    while (1)
        ;
}

/*  void Interrupt_18()
 *    DESCRIPTION: Machine Check
 *  input /output : none */
void Interrupt_18()
{
    printf("Machine Check!\n");
    while (1)
        ;
}

/*  void Interrupt_19()
 *    DESCRIPTION: SIMD Floating-Point Exception
 *  input /output : none */
void Interrupt_19()
{
    printf("SIMD Floating-Point Exception!\n");
    while (1)
        ;
}

/*  void Interrupt_20()
 *    DESCRIPTION: Virtualization Exception
 *  input /output : none */
void Interrupt_20()
{
    printf("Virtualization Exception!\n");
    while (1)
        ;
}

/*  void Interrupt_21()
 *    DESCRIPTION: Control Protection Exception
 *  input /output : none */
void Interrupt_21()
{
    printf("Control Protection Exception!\n");
    while (1)
        ;
}

void Interrupt_32()
{
    printf("PIT!\n");
    while(1);
}

/*  void Interrupt_33()
 *    DESCRIPTION: keyboard interrupt
 *  input /output : none */
void Interrupt_33()
{
    char in = scan2ascii(inb(KEYBOARD_PORT));
    if (in != NULL)
    {
        printf("%c", in);
    }
    send_eoi(KEYBOARD_IRQ_NUM);
}

/*  void Interrupt_40()
 *    DESCRIPTION: RTC interrupt
 *  input /output : none */
void Interrupt_40()
{
    outb(REGISTER_C, REGISTER_SELECT);
    inb(REGISTER_RW);
    test_interrupts();
    send_eoi(RTC_IRQ_NUM);
}

void Interrupt_128()
{
    printf("System Call!\n");
    system_call();
    while(1);
}
