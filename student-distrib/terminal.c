#include "terminal.h"

#define LIMIT 128
#define STARTING_POINT 0
#define SUCCESS 0
#define NEW_LINE 10


unsigned char buffer[LIMIT];
int index=STARTING_POINT;

/*
 *  int terminal_open()
 *    DESCRIPTION:
 *      open terminal
 *    INPUTS:
 *      none
 *    OUTPUTS:
 *      none
 *    Return value : 0 for success
 */
int terminal_open()
{
    return SUCCESS;
}

/*
 *  int terminal_close()
 *    DESCRIPTION:
 *      close terminal
 *    INPUTS:
 *      none
 *    OUTPUTS:
 *      none
 *    RETURN:
 *      0 for success
 */
int terminal_close()
{
    return SUCCESS;
}

/*
 *  int terminal_write(unsigned char *c,int length)
 *    DESCRIPTION:
 *      write a char to terminal for it to be displayed immediately
 *    INPUTS:
 *      unsigned char *c - the data to be written to terminal
 *      int length - length of the data
 *    OUTPUTS:
 *      none
 *    RETURN:
 *      0 for success
 *    SIDE EFFECT:
 *      display character to terminal
 */
int terminal_write(unsigned char *c,int length)
{
    int i;
    cli();
    for(i=STARTING_POINT;i<length;i++)
    {
        putc(*(c+i));  //output character to terminal
    }
    sti();
    return SUCCESS;
}

/*
 *	int terminal_read(unsigned char *ret_buf,int length)
 *    DESCRIPTION:
 *      read from terminal until a newline char is met
 *      or maximum buffer size reached
 *    INPUTS:
 *      unsigned char *ret_buf - buffer to store the data read from terminal
 *      int length - length of the data
 *    OUTPUTS:
 *      none
 *    RETURN:
 *      the number of bytes read
 */
 int terminal_read(unsigned char *ret_buf, int length)
 {
     int copied = STARTING_POINT;
     while (index == STARTING_POINT || buffer[index] != NEW_LINE)
         ;
     index++;
     cli();
     while (copied < length && copied < index)
     {
         ret_buf[copied] = buffer[copied];
         copied++;
     }
     sti();

     return copied;
 }
