#ifndef _RTC
#define _RTC

#define REGISTER_B 0x8b
#define REGISTER_SELECT 0X70
#define REGISTER_RW 0x71
#define REGISTER_A 0x8a
#define RTC_RATE 15
#define PERIODIC_INTERRUPT_MASK 0x40
#define RATE_MASK 0xf0
#define RTC_CYCLE_PER_SEC 32768

#ifndef ASM
/* function to enable rtc */
extern void rtc_init();

extern int rtc_write(int frequency);

//extern int32_t rtc_write(int frequency);

extern int rtc_read();

extern int rtc_open();

extern int rtc_close();

extern volatile int rtc_interrupt_occured;

#endif
#endif
