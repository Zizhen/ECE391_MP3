/* rtc.c - function to initialize the rtc interrupt */
#include "lib.h"

#define ASM 1
#include "rtc.h"

#define BASE_RATE 15
#define SUCCESS 0
#define FAILURE -1
#define MIN_FREQ 2
#define MAX_FREQ 1024
#define INVALID 0
#define VALID 1
#define BIT_MASK 0xf0

static int frequency_VALID(int frequency);
volatile int rtc_interrupt_occured;
//static int current_frequency=2;
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
    int rate = BASE_RATE;
    outb(REGISTER_A, REGISTER_SELECT);
    prev = inb(REGISTER_RW);
    outb(REGISTER_A, REGISTER_SELECT);
    outb((prev & RATE_MASK) | rate, REGISTER_RW);
}

/*   int32_t rtc_open(const uint8_t* filename)
 *    DESCRIPTION:
 *      calls the rtc init function that initialize thertc
 *    INPUTS:
 *      none
 *    OUTPUTS:
 *      always return 0
 *    SIDE EFFECTS:
 *      none
 */
int rtc_open()
{
    /* set the interrupt rate to 2Hz */
    cli();
    int rate = BASE_RATE;
    char prev;
    outb(REGISTER_A, REGISTER_SELECT);
    prev = inb(REGISTER_RW);
    outb(REGISTER_A, REGISTER_SELECT);
    outb((prev & RATE_MASK) | rate, REGISTER_RW);
    sti();
    return SUCCESS;
}

/*   iint32_t rtc_close (int32_t fd)
 *    DESCRIPTION:
 *      does nothing since no file was open  
 *    INPUTS:
 *      none
 *    OUTPUTS:
 *      returns 0 
 *    SIDE EFFECTS:
 *      none
 */
int rtc_close()
{
    return SUCCESS;
}

/*   int32_t rtc_read(int32_t fd, void* buf, int32_t nbytes)
 *    DESCRIPTION:
 *      always sets an interrupt flag and returns 0 when flag cleared
 *    INPUTS:
 *      none
 *    RETURN:
 *      always returns 0 
 *    SIDE EFFECTS:
 *      none
 */
int rtc_read()
{
	rtc_interrupt_occured = 0;
    while(!rtc_interrupt_occured);
    rtc_interrupt_occured=0;
    return SUCCESS;
}

/*   int32_t rtc_write(int32_t fd, const void* buf, int32_t nbytes)
 *    DESCRIPTION:
 *      set the rtc frequency to specific rate
 *    INPUTS:
 *      void * buf - pointer to the frequency
 *    OUTPUTS:
 *      0 for success
 *      -1 for FAILURE
 *    SIDE EFFECTS:
 *      modifies the periodic interrupt rate
 */
int rtc_write(int frequency)
{
    int i = RTC_CYCLE_PER_SEC/frequency;
    int rate;
    char prev;

    // check VALIDity of input
    if(!frequency_VALID(frequency))
    {
        return FAILURE;
    }

    // convert frequency to rate
    for(rate=0;i>0;rate++)
    {
        i=i>>1;
    }

    // write the frequency
    cli();
    outb(REGISTER_A, REGISTER_SELECT);
    prev = inb(REGISTER_RW)&BIT_MASK;
    outb(REGISTER_A, REGISTER_SELECT);
    outb((prev & RATE_MASK) | rate, REGISTER_RW);
    sti();
    return SUCCESS;
}

/*
int rtc_read(int frequency)
{
    int cur_freq=current_frequency;
    while(cur_freq/frequency>=1)
    {
        while(!rtc_interrupt_occured);
        cur_freq=cur_freq>>1;
    }
    rtc_interrupt_occured=0;
    return 0;
}
*/

/*
int rtc_write(int frequency)
{
    int i = 32768/frequency;
    int rate;
    char prev;
    if(!frequency_VALID(frequency))
    {
        return -1;
    }
    if(frequency>current_frequency)
    {
      current_frequency=frequency;
      for(rate=0;i>0;rate++)
      {
          i=i>>1;
      }
      cli();
      outb(REGISTER_A, REGISTER_SELECT);
      prev = inb(REGISTER_RW)&0xf0;
      outb(REGISTER_A, REGISTER_SELECT);
      outb((prev & RATE_MASK) | rate, REGISTER_RW);
      sti();
    }
    return 0;
}
*/

/*   int frequency_VALID (int frequency)
 *   DESCRIPTION:
 *     helper function to determine whether a frequency to write is VALID (<= 1024 && power of 2) 
 *   INPUTS:
 *      int frequency - the frequency to be written
 *   OUTPUTS:
 *      0 on FAILURE 
 *      1 on success   
 *   SIDE EFFECTS:
 *      none
 */
int frequency_VALID(int frequency)
{
    int i,count;
    count = 0;              // number of 1s in binary form

    // check frequency range
    if(frequency>MAX_FREQ||frequency<MIN_FREQ)
    {
        return INVALID;
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
        return INVALID;
    }
    return VALID;
}
