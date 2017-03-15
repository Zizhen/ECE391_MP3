#include "terminal.h"
#include "lib.h"
#define BUFFER_LEN 128
#define NEWLINE 10
char buffer[BUFFER_LEN];

int buffer_ptr = 0;

void clean_screen(){
  clear();
  reset_screen_pos();
}

void delete_char(){
  if(screen_x == 0 && screen_y == 0)
    return;
  if(buffer_ptr > 0){
    if(screen_x == 0){      //back to the line above
      screen_y--;
      screen_x = NUM_COLS-1;
    }
    else{
      screen_x --;
    }
    *(uint8_t *)(video_mem + ((NUM_COLS * screen_y + screen_x) << 1)) = ' ';
    *(uint8_t *)(video_mem + ((NUM_COLS * screen_y + screen_x) << 1)+1) = ATTRIB;
    buffer_ptr--;
  }
}

void scroll(){
  int i;
  memcpy(video_mem, video_mem+NUM_COLS*2, NUM_COLS*(NUM_ROWS-1)*2);
  for(i = 0; i < NUM_COLS; i++){
    *(uint8_t *)(video_mem + NUM_COLS*(NUM_ROWS-1)*2 + (i << 1)) = ' ';
    *(uint8_t *)(video_mem + NUM_COLS*(NUM_ROWS-1)*2 + (i << 1) + 1) = ATTRIB;
  }
  // printf("x: %d\n", screen_x);
  // printf("y: %d\n", screen_y);
  screen_x = 0;
  screen_y = NUM_ROWS-1;

}

void type(unsigned char input){
  if(buffer_ptr < BUFFER_LEN){
    if(input == NEWLINE){           //ENTER is pressed
      clear_buffer();
      if(screen_y == (NUM_ROWS-1))
        scroll();
      else{
        screen_x = 0;
        screen_y ++;
      }
    }
    else if(screen_x==79){          //at the end of a line
      buffer[buffer_ptr] = NEWLINE;
      buffer_ptr++;
      if(screen_y == (NUM_ROWS-1))
        scroll();
      else{
        screen_x = 0;
        screen_y ++;
      }
      buffer[buffer_ptr] = input;
      printf("%c", input);
      buffer_ptr++;
    }
    else{                           //normal typing
      buffer[buffer_ptr] = input;
      printf("%c", input);
      buffer_ptr++;
    }
  }
}

void clear_buffer(){
  buffer_ptr = 0;
}
