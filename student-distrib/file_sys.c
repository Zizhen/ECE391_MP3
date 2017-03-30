#include "file_sys.h"

/* constants */
#define FAILURE -1
#define SUCCESS 0
#define LEN_LIMIT 32
#define FILE_N_LIMIT 63
#define STARTING 0

boot_block_t *boot_block;

/*  int read_dentry_by_name(const int8_t* fname,dentry_t* dentry)
 *  DESCRIPTION:
 *      read files by name
 *    INPUTS:
 *      const int8_t* fname - pointer to a file name
 *		dentry_t* dentry - pointer to diretory entry
 *    OUTPUTS:
 *      none
 *    RETURN VALUE:
 *      0 for SUCCESS, -1 for fail
 */
int read_dentry_by_name(const int8_t* fname,dentry_t* dentry)
{
    int num_char;
    int i,j;
	
	/* check if file name is valid in length */
    for(num_char=STARTING;fname[num_char]!=STARTING;num_char++);
    if(num_char>LEN_LIMIT)
    {
        printf("too long file name!\n");
        return FAILURE;
    }

	/* find the file matches the name and copy data*/
    for(i=STARTING;i<FILE_N_LIMIT;i++)
    {
        if(!strncmp(boot_block->entries[i].file_name,fname,num_char))
        {
            for(j=STARTING;j<num_char;j++)
            {
                dentry->file_name[j]=boot_block->entries[i].file_name[j];
            }
            dentry->file_type=boot_block->entries[i].file_type;
            dentry->inode_index=boot_block->entries[i].inode_index;
            return SUCCESS;
        }
    }
	
	/* no file found */
    printf("file not found!\n");
    return FAILURE;
}

/*  int read_dentry_by_index(uint32_t index,dentry_t *dentry)
 *  DESCRIPTION:
 *      read files by index
 *    INPUTS:
 *      uint32_t index - index of directory entry
 *		dentry_t* dentry - pointer to directory entry struct
 *    OUTPUTS:
 *      none
 *    RETURN VALUE:
 *      0 for SUCCESS, -1 for fail
 */
int read_dentry_by_index(uint32_t index,dentry_t *dentry)
{
    int i;
	/* invalid index */
    if(index>=FILE_N_LIMIT)
    {
        printf("file not found!\n");
        return FAILURE;
    }
	
	/* find the file matches the index and copy data*/
    for(i=STARTING;i<LEN_LIMIT;i++)
    {
        dentry->file_name[i]=boot_block->entries[index].file_name[i];
    }
    dentry->file_type=boot_block->entries[index].file_type;
    dentry->inode_index=boot_block->entries[index].inode_index;
    return SUCCESS;
}

/*  int read_data(uint32_t inode, uint32_t offset,int8_t *buf,uint32_t length)
 *  DESCRIPTION:
 *      read data from a inode 
 *    INPUTS:
 *      uint32_t inode - index node
 *      uint32_t offset - offset for the data block
 *		int8_t *buf - data reading buffer
 *		uint32_t length - length of data
 *    OUTPUTS:
 *      none
 *    RETURN VALUE:
 *      0 for SUCCESS, -1 for fail
 */
int read_data(uint32_t inode, uint32_t offset,int8_t *buf,uint32_t length)
{
    inode_t *inode_addr=(inode_t *)(boot_block+inode+1);
    int copied,i,j;
    uint8_t *data_start=(uint8_t *)(boot_block+boot_block->num_inodes+1);
    uint8_t *data;
    i=offset/KB4;
    j=offset%KB4;
	/* check for invalid offset */
    if(offset>inode_addr->length)
    {
        printf("offset too big!\n");
        return FAILURE;
    }
    for(copied=STARTING;copied<length&&copied<inode_addr->length;copied++)
    {
        if(inode_addr->data_block_num[i]>boot_block->num_blocks)
        {
            printf("bad data block number\n");
            return FAILURE;
        }
        data=data_start+inode_addr->data_block_num[i]*KB4;
        *(buf+copied)=*(data+j);
        j++;
        if(j>=KB4)
        {
            j=STARTING;
            i++;
        }
    }
    return copied;
}

/*  int directory_read(uint32_t offset,int8_t *buf,uint32_t length)
 *  DESCRIPTION:
 *      read a directory
 *    INPUTS:
 *      uint32_t offset - offset for the directory
 *		int8_t *buf - buffer for directory reading
 *		uint32_t length - length of the data
 *    OUTPUTS:
 *      none
 *    RETURN VALUE:
 *      0 for SUCCESS, or number of data read
 */
int directory_read(uint32_t offset,int8_t *buf,uint32_t length)
{
    int entry_index=STARTING,name_index=STARTING;
    int copied=STARTING;
    entry_index=entry_index+offset/LEN_LIMIT;
    name_index=name_index+offset%LEN_LIMIT;
    while(copied<length)
    {
        if(entry_index>=boot_block->num_dentries)
        {
            return SUCCESS;
        }
        *(buf+copied)=boot_block->entries[entry_index].file_name[name_index];
        copied++;
        name_index++;
        if(name_index>=LEN_LIMIT)
        {
            entry_index++;
            name_index=STARTING;
        }
    }
    return copied;
}
