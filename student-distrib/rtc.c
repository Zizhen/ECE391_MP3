/* rtc.c - function to initialize the rtc interrupt */
#include "lib.h"
//#define ASM 1
#include "rtc.h"
static int frequency_valid(int frequency);

/*
 *  int rtc_init()
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

/*
 *  int rtc_open()
 *    DESCRIPTION:
 *      open rtc, set freq to 2Hz
 *    INPUTS:
 *      none
 *    OUTPUTS:
 *      none
 *    SIDE EFFECTS:
 *      reopen the rtc to 2Hz
 */
int rtc_open(){
    cli();
    /* set the interrupt rate to 2Hz */
    int rate = RTC_RATE;
    outb(REGISTER_A, REGISTER_SELECT);
    char prev = inb(REGISTER_RW);
    outb(REGISTER_A, REGISTER_SELECT);
    outb((prev & RATE_MASK) | rate, REGISTER_RW);
    sti();
    return 0;
}

/*
 *  int rtc_read()
 *    DESCRIPTION:
 *      open rtc, set freq to 2Hz
 *    INPUTS:
 *      none
 *    OUTPUTS:
 *      none
 *    SIDE EFFECTS:
 *      reopen the rtc to 2Hz
 */
int rtc_read(){
    rtc_interrupt_occured = 0;

    while(rtc_interrupt_occured)
      rtc_interrupt_occured = 0;

    return 0;
}

/*
 *  int rtc_write()
 *    DESCRIPTION:
 *      set freq to input
 *    INPUTS:
 *      input
 *    OUTPUTS:
 *      none
 *    SIDE EFFECTS:
 *      set rtc to input Hz
 */
int rtc_write(int input){
  if(!frequency_valid(input)){
    return -1;
  }
  int rate = 32768 >> (input-1);
  outb(REGISTER_A, REGISTER_SELECT);
  int prev = inb(REGISTER_RW);
  outb(REGISTER_A, REGISTER_SELECT);
  outb((prev & RATE_MASK) | rate, REGISTER_RW);
  return 0;
}

int rtc_close(){
    return 0;
}

/*   int frequency_valid (int frequency)
 *   DESCRIPTION:
 *     helper function to determine whether a frequency to write is valid (<= 1024 && power of 2)
 *   INPUTS:
 *      int frequency - the frequency to be written
 *   OUTPUTS:
 *      0 on failure
 *      1 on success
 *   SIDE EFFECTS:
 *      none
 */
int frequency_valid(int frequency)
{
    int i,count;
    count = 0;              // number of 1s in binary form

    // check frequency range
    if(frequency>1024||frequency<2)
    {
        return 0;
    }

    // count the number of 1s in the binary form of freq
    for(i=frequency;i>0;i=i>>1)
    {
        if(i&1)
        {
            count++;
        }
    }

    // if more than one 1s, it's not a power of 2
    if(count>1)
    {
        return 0;
    }
    return 1;
}
