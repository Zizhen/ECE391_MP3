#include "mp3_2_test.h"

static int name_index=0;
static int file_index=0;
static int frequency=2;

#define FILE_NUM 17
#define RTC_IRQ 0x08
#define BASE_FREQ 2
#define MAX_FREQ 1024
#define BUFFER_SIZE 40000
#define LENGTH 32
#define INIT 0
#define MAX_NUM_FILES 100
// char* fname[FILE_NUM]={".","sigtest","shell","grep","syserr","rtc","fish",
//                 "counter","pingpong","cat","frame0.txt",
//                 "verylargetextwithverylongname.txt","ls","testprint",
//                 "created.txt","frame1.txt","hello"};

int file_num;
char fname[MAX_NUM_FILES][LENGTH];

/*  void test_init()
 *  DESCRIPTION:
 *      initialize test, fill fname by file name in system
 *    INPUTS: none
 *    OUTPUTS:
 *      none
 *    RETURN VALUE:
 *      none
 */
void test_init(){
  dentry_t dentry;
  int i;
	int counter = 0;
  int j = 0;
  for(i=INIT;i<boot_block->num_dentries;i++)
  {
    read_dentry_by_index(i,&dentry);
    if(dentry.file_name[INIT]!=INIT)
    {
      while(dentry.file_name[j]!=INIT){
        fname[counter][j] = dentry.file_name[j]; //problematic
        j++;
      }
      j = 0;
			counter ++;
		}
	}
	file_num = counter;
}

/*  void list_file()
 *  DESCRIPTION:
 *      list the name of all the files
 *    INPUTS: none
 *    OUTPUTS:
 *      none
 *    RETURN VALUE:
 *      none
 */
void list_file()
{
    dentry_t dentry;
    int i;
    /* disable rtc and clear screen */
    disable_irq(RTC_IRQ);
    clear_screen();

    /* output the filenames */
    for(i=INIT;i<boot_block->num_dentries;i++)
    {
        read_dentry_by_index(i,&dentry);
        if(dentry.file_name[INIT]!=INIT)
        {
            printf("filename: ");
            terminal_write((unsigned char *)dentry.file_name,LENGTH);
            putc(' ');
            printf("file type:");
            printf("%d ",dentry.file_type);
            printf("file size:");
            printf(" ");
            printf("%d ",*(boot_block+dentry.inode_index+1));
            putc('\n');

        }
    }

}

/*  void read_file_by_name()
 *  DESCRIPTION:
 *      read files by their name
 *    INPUTS: none
 *    OUTPUTS:
 *      none
 *    RETURN VALUE:
 *      none
 */
void read_file_by_name()
{
    char buffer[BUFFER_SIZE];
    dentry_t dentry;
    int i,size;
    /* disable rtc and clear screen */
    disable_irq(RTC_IRQ);
    clear_screen();

    /* output the content of the file */
    if(read_dentry_by_name(fname[name_index],&dentry)!=-1)
    {
        size=read_data(dentry.inode_index,INIT,buffer,BUFFER_SIZE);
        terminal_write((unsigned char *)buffer,size);
    }
    putc('\n');
    putc('\n');
    printf("file name: ");
    for(i=INIT;*(fname[name_index]+i)!=INIT;i++)
    {
        putc(*(fname[name_index]+i));
    }
    putc('\n');
    name_index++;
    if(name_index>=file_num)
    {
        name_index=INIT;
    }
}

/*  void read_file_by_index()
 *  DESCRIPTION:
 *      read files by their index
 *    INPUTS: none
 *    OUTPUTS:
 *      none
 *    RETURN VALUE:
 *      none
 */
void read_file_by_index()
{
    char buffer[BUFFER_SIZE];
    dentry_t dentry;
    int size;
    disable_irq(RTC_IRQ);
    clear_screen();
    if(read_dentry_by_index(file_index,&dentry)!=-1)
    {
        size=read_data(dentry.inode_index,INIT,buffer,BUFFER_SIZE);
        terminal_write((unsigned char *)buffer,size);
        putc('\n');
        putc('\n');
        printf("file name: ");
        terminal_write((unsigned char *)dentry.file_name,LENGTH);
    }
    printf("   file index: %d",file_index);
    putc('\n');
    file_index++;
    if(file_index>=file_num)
    {
        file_index=INIT;
    }
}

/*  void rtc_test()
 *  DESCRIPTION:
 *      adjust the rate of rtc
 *    INPUTS: none
 *    OUTPUTS:
 *      none
 *    RETURN VALUE:
 *      none
 */
void rtc_test()
{
    clear_screen();
    enable_irq(RTC_IRQ);
    printf("current frequency: %d\n",frequency);
    rtc_write(frequency);
    frequency=frequency<<1;
    if(frequency>MAX_FREQ)
    {
        frequency=BASE_FREQ;
    }
}

/*  void rtc_test_finished()
 *  DESCRIPTION:
 *      end rtc test
 *    INPUTS: none
 *    OUTPUTS:
 *      none
 *    RETURN VALUE:
 *      none
 */
void rtc_test_finished()
{
    disable_irq(RTC_IRQ);
    clear_screen();
    frequency=BASE_FREQ;
    rtc_write(frequency);
    printf("rtc test finished, return to default frequency\n");
}
