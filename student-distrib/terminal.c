#include "terminal.h"
#include "lib.h"
#define BUFFER_LEN 128

char buffer[BUFFER_LEN];

int buffer_ptr = 0;
void clean_screen(){
  clear();
  reset_screen_pos();
}

void delete_char(){
  // printf("screen_x: %d\n", screen_x);
  // printf("screen_y: %d\n", screen_y);
  if (screen_x == 0)
  {
    screen_y--;
    screen_x = NUM_COLS-1;
  }
  else screen_x --;
  // printf("after reset screen_x: %d\n", screen_x);
  // printf("after reset screen_y: %d\n", screen_y);

  putc(0x20);
  if (screen_x == 0)
  {
    screen_y--;
    screen_x = NUM_COLS-1;
  }
  else screen_x --;
  // printf("after clean screen_x: %d\n", screen_x);
  // printf("after clean screen_y: %d\n", screen_y);
  if(buffer_ptr>=2)
    buffer_ptr -= 2;

}

void type(unsigned char input){
  if(buffer_ptr < BUFFER_LEN){
    buffer[buffer_ptr] = input;
    printf("%c", input);
//    printf("\n%d\n", buffer_ptr);
    buffer_ptr++;
  }
}
