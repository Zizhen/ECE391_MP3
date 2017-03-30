/* handling keyboard interrupt
 * get the correct character from corresponding scan value */
#include "keyboard.h"

#define ARRAY_LEN 256
#define DNE 0
#define CAPS_LOCK 0x3A
#define L_SHIFT_PRESSED 0x2A
#define R_SHIFT_PRESSED 0x36
#define L_SHIFT_RELEASED 0xAA
#define R_SHIFT_RELEASED 0xB6
#define CTL_PRESSED 0x1D
#define CTL_RELEASED 0x9D
#define L_PRESSED 0x26
#define BACKSPACE_PRESSED 0x0E

#define LIMIT 128
#define L_FILE 257
#define R_FILE_NAME 258
#define R_FILE_INDEX 259
#define RTC_T 260
#define RTC_T_FINISH 261

#define ONE_PRESSED 0x02
#define TWO_PRESSED 0x03
#define THREE_PRESSED 0x04
#define FOUR_PRESSED 0x05
#define FIVE_PRESSED 0x06
#define ONE_RELEASED 0x82
#define TWO_RELEASED 0x83
#define THREE_RELEASED 0x84
#define FOUR_RELEASED 0x85
#define FIVE_RELEASED 0x86

#define INVALID 0
#define STARTING_POINT 0

#define ON 1
#define OFF 0

/* constants for keyboard ascii*/
#define ESC 0
#define BACKSPACE 8
#define TAB 0
#define NEWLINE 10
#define S_QUOTATION 39
#define BACKSLASH 92
#define SPACE 32
#define DOUBLE_quotation 34
#define Vert_line 124
#define CLEAR_SCREEN 256

#define UPPER_TO_LOWER 32
#define LOWER_TO_UPPER -32
#define KEY_RELEASE 0x58

int caps_flag = OFF;
int shift_flag=OFF;
int ctl_flag=OFF;

static char k2a_arr[ARRAY_LEN] = {
    DNE, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '-','=', BACKSPACE, TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    'o', 'p','[', ']', NEWLINE, DNE, 'a', 's', 'd', 'f', 'g', 'h',
    'j', 'k', 'l',';', S_QUOTATION, '`', DNE, BACKSLASH, 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',','.', '/', DNE, '*', DNE, SPACE, DNE, DNE,
    DNE, DNE, DNE, DNE, DNE, DNE, DNE, DNE, DNE, DNE, DNE,DNE,
     DNE, DNE, '-', DNE, DNE, DNE, '+', DNE, DNE, DNE, DNE, '.',
    DNE, DNE};

static char k2a_arr_shifted[ARRAY_LEN] = {
    DNE, ESC, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
    '_','+', BACKSPACE, TAB, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P','{', '}', NEWLINE, DNE, 'A', 'S', 'D', 'F', 'G', 'H',
    'J', 'K', 'L',':', DOUBLE_quotation, '~', DNE, Vert_line, 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', '<','>', '?', DNE, '*', DNE, SPACE, DNE, DNE,
    DNE, DNE, DNE, DNE, DNE, DNE, DNE, DNE, DNE, DNE, DNE,DNE,
     DNE, DNE, '-', DNE, DNE, DNE, '+', DNE, DNE, DNE, DNE, '.',
    DNE, DNE};

/*
 *  int keyboard_read(int scan)
 *    DESCRIPTION:
 *      get the ascii value of the character typed from keyboard ann deal with the input command
 *    INPUT:
 *      char scan -- input from keyboard
 *    OUTPUT:
 *      none
 *    Return value : correct correspoing character or specific number for command
 */
int keyboard_read(int scan)
{
    char ascii=DNE;

    /* check for shift, capslock, control keys */
    if (scan == CAPS_LOCK)  // check if caps lock key is pressed
    {
        if (caps_flag)
        {
            caps_flag = OFF;
        }
        else
        {
            caps_flag = ON;
        }
    }
    else if(scan==L_SHIFT_PRESSED||scan==R_SHIFT_PRESSED) //check if shift is pressed
    {
        //printf("shift pressed\n");
      shift_flag=ON;
    }
    else if(scan==L_SHIFT_RELEASED||scan==R_SHIFT_RELEASED) //check if shift is released
    {
        //printf("shift released\n");
      shift_flag=OFF;
    }
    else if(scan==CTL_PRESSED) //check for control key
    {
      ctl_flag=ON;
    }
    else if(scan==CTL_RELEASED)
    {
      ctl_flag=OFF;
    }

    /* check if need to clear screen */
    if(scan==L_PRESSED&&ctl_flag==ON)
    {
        clear_screen();
        return INVALID;
    }

    /* execute test cases */
    else if(scan==ONE_PRESSED&&ctl_flag==ON)
    {
        return L_FILE;
    }
    else if(scan==TWO_PRESSED&&ctl_flag==ON)
    {
        return DNE;
    }
    else if(scan==TWO_RELEASED&&ctl_flag==ON)
    {
        return R_FILE_NAME;
    }
    else if(scan==THREE_PRESSED&&ctl_flag==ON)
    {
        return DNE;
    }
    else if(scan==THREE_RELEASED&&ctl_flag==ON)
    {
        return R_FILE_INDEX;
    }
    else if(scan==FOUR_PRESSED&&ctl_flag==ON)
    {
        return RTC_T;
    }
    else if(scan==FIVE_PRESSED&&ctl_flag==ON)
    {
        return RTC_T_FINISH;
    }

    /* check if the key is released */
    if (scan > KEY_RELEASE) // if the number is larger than 0x58, it means release
    {
        return DNE;
    }

    /* deal with the situation when shift is pressed */
    if(shift_flag)
    {
        ascii=k2a_arr_shifted[(int)scan];
    }
    else
    {
        ascii = k2a_arr[(int)scan];  // get the corresponding ascii value of the key pressed
    }

    /* switch between upper case and lower case of alphabets */
    if (ascii >= 'A' && ascii <= 'Z' && caps_flag && shift_flag)  // for alphabets that are not capitalized
    {
        ascii += UPPER_TO_LOWER;
    }
    else if (ascii >='a' &&ascii <='z' &&caps_flag&&!shift_flag)
    {
        ascii+=LOWER_TO_UPPER;
    }

    /* delete character */
    if(ascii == BACKSPACE)
    {
        delete_char();
    }
    else if(ascii == NEWLINE)
    {
        flush_line_buffer();
    }
    else if (ascii != INVALID)
    {
        if(index>=LIMIT)
        {
            return INVALID;
        }
        putc(ascii);
        buffer[index]=ascii;
        index++;
    }
    return INVALID;
}

/*  void clear_screen()
 *  DESCRIPTION:
 *      clear the screen and set the cursor
 *    INPUTS:
 *      none
 *    OUTPUTS:
 *      none
 *    RETURN VALUE:
 *      none
 */
void clear_screen()
{
    clear();
    reset_screen_pos();
}

/*  void delete_char()
 *  DESCRIPTION:
 *      delete the character
 *    INPUTS:
 *      none
 *    OUTPUTS:
 *      none
 *    RETURN VALUE:
 *      none
 */
void delete_char()
{
    if(index==STARTING_POINT)
    {
        return;
    }
    index--;
    clear_char();
}

/*  void flush_line_buffer()
 *  DESCRIPTION:
 *     change to a new line
 *    INPUTS:
 *      none
 *    OUTPUTS:
 *      none
 *    RETURN VALUE:
 *      none
 */
void flush_line_buffer()
{
    buffer[index]='\n';
    index++;
    index=STARTING_POINT;
    putc('\n');
}
