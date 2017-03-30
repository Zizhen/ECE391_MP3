#ifndef _FILE_SYS_H
#define _FILE_SYS_H

#include "types.h"
#include "lib.h"
#define KB4 4096

#define NUM_DATA_BLOCKS 1023
#define NUM_DENTRIES 63
#define SIZE_RESERVED_BOOT 52
#define SIZE_RESERVED_DENTRY 24
#define SIZE_FILENAME 32
// directory entry struct 64B total
typedef struct dentry_t
{
    char file_name[SIZE_FILENAME];  // 32B
    uint32_t file_type;             // 4B
    uint32_t inode_index;           // idx of corresponded inode 4B 
    uint8_t reserved[SIZE_RESERVED_DENTRY];           // 24B reserved
}dentry_t;

// boot_block struct 4kB total
typedef struct boot_block_t
{
    uint32_t num_dentries;      // number of directory entries - 4B
    uint32_t num_inodes;        // number of index nodes - 4B
    uint32_t num_blocks;        // number of data blocks - 4B
    uint8_t reserved[SIZE_RESERVED_BOOT];       // 52 byte of reserved space
    dentry_t entries[NUM_DENTRIES];       // 63 derectory entries 64B each
}boot_block_t;

// information node struct 4kB total
typedef struct inode_t
{
    uint32_t length;                // length of data 4B
    uint32_t data_block_num[NUM_DATA_BLOCKS];  // data block numbers 4B each up to 1023 blocks
}inode_t;

extern int read_dentry_by_name(const int8_t *fname, dentry_t *dentry);

extern int read_dentry_by_index(uint32_t index,dentry_t *dentry);

extern int read_data(uint32_t inode,uint32_t offset,int8_t *buf,uint32_t length);

extern int directory_read(uint32_t offset,int8_t *buf,uint32_t length);

extern boot_block_t *boot_block;

#endif
