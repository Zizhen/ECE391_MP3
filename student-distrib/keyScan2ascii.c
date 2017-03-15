/* handling keyboard interrupt
 * get the correct character from corresponding scan value */

#define ASM 1
#include "keyScan2ascii.h"

#define ARRAY_LEN 256
#define NULL 0
#define CAPS_LOCK 0x3A

/* constants for keyboard ascii*/
#define ESC 27
#define BACKSPACE 8
#define TAB 9
#define NEWLINE 10
#define S_QUOTATION 39
#define BACKSLASH 92
#define SPACE 32
#define LEFT_CTRL 0x1D
#define L 0x26
#define CTRL_RELEASE 0x9D
#define CLEAN 0XFF

int caps_flag = 0;
int ctrl_flag = 0;

static char k2a_arr[ARRAY_LEN] = {
    NULL, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-',
    '=', BACKSPACE, TAB, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
    '[', ']', NEWLINE, NULL, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
    ';', S_QUOTATION, '`', NULL, BACKSLASH, 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',',
    '.', '/', NULL, '*', NULL, SPACE, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.',
    NULL, NULL};

/*
 *  char scan2ascii(char scan)
 *    DESCRIPTION:
 *      get the ascii value of the character typed from keyboard
 *    INPUT:
 *      char scan -- input from keyboard
 *    OUTPUT:
 *      none
 *    Return value : correct correspoing character
 */
#define Lower_to_Upper 32
#define KEY_RELEASE 0x58
unsigned char scan2ascii(int scan)
{
    char ascii;
    if (scan == CAPS_LOCK)  // check if caps lock key is pressed
    {
        if (caps_flag)
        {
            caps_flag = 0;
        }
        else
        {
            caps_flag = 1;
        }
    }
    if(scan == LEFT_CTRL)
      ctrl_flag = 1;

    else if(scan == CTRL_RELEASE)
      ctrl_flag = 0;

    if(scan == L && ctrl_flag == 1)
      return CLEAN;

    if (scan > KEY_RELEASE) // if the number is larger than 0x58, it means release
    {
        return NULL;
    }

    ascii = k2a_arr[(int)scan];  // get the corresponding ascii value of the key pressed

    if (ascii >= 'A' && ascii <= 'Z' && !caps_flag)  // for alphabets that are not capitalized
    {
        ascii += Lower_to_Upper;  // add 32 to make it not capitalized
    }

    return ascii;
}
