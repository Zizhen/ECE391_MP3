/* rtc.c - function to initialize the rtc interrupt */
#include "rtc.h"
#include "lib.h"

/*
 *  void rtc_init()
 *    DESCRIPTION:
 *      initialize the rtc
 *    INPUTS:
 *      none
 *    OUTPUTS:
 *      none
 *    SIDE EFFECTS:
 *      initialize the rtc
 */
void rtc_init()
{
    /* turn on the periodic interrupt */
    outb(REGISTER_B, REGISTER_SELECT);
    char prev = inb(REGISTER_RW);
    outb(REGISTER_B, REGISTER_SELECT);
    outb(prev | PERIODIC_INTERRUPT_MASK, REGISTER_RW);

    /* set the interrupt rate to 2Hz */
    int rate = RTC_RATE;
    outb(REGISTER_A, REGISTER_SELECT);
    prev = inb(REGISTER_RW);
    outb(REGISTER_A, REGISTER_SELECT);
    outb((prev & RATE_MASK) | rate, REGISTER_RW);
}
