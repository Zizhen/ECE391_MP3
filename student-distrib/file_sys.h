#ifndef _FILE_SYS_H
#define _FILE_SYS_H
#include "types.h"
#include "lib.h"
#define KB4 4096
typedef struct dentry_t{
    char file_name[32];
    int32_t  file_type;
    // 0 for file giving user level access to RTC
    // 1 for directory
    // 2 for a regular file
    int32_t  inode_num;
    //only meaningful for regular file_sys
    //ignored for the RTC and directory types
    char reserved[24];
}dentry_t
//occupies 64B

typedef struct boot_block_t{
    int32_t num_dentry;
    int32_t num_inode;
    int32_t num_data_block;
    int8_t reserved[52];
    //statistics
    dentry_t dentry[63];
}boot_block_t
//occupies 128B

typedef struct inode_t{
    int32_t length;
    int32_t data_block[1023];
}inode_t

extern int32_t read_dentry_by_name(const uint8_t* fname, dentry_t* dentry);
extern int32_t read_dentry_by_index (uint32_t index, dentry_t* dentry);
extern int32_t read_data_(uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length);
extern boot_block_t* boot_block;
#endif
