#include "file_sys.h"

boot_block_t* boot_block;

/* read_dentry_by_name
 *  input: file_name
 *         directory entry
 *  output: directory entry written with the file name
 *          file type and num_inode
 *  return: -1 on failure(non existent dile or invalid index)
 *          0 on success
 */
int32_t read_dentry_by_name(const int8_t* fname, dentry_t* dentry){
  int i,j;
  int num_chars;
  if(fname == NULL || dentry == NULL){
    printf("NULL pointer!\n");
    return -1;
  }

  for(num_chars = 0; fname[num_chars]!=0; num_chars++){
      if(num_chars > 32){
        printf("file_name too long!\n");
        return -1;
      }
  }

  for(i = 0; i < 63; i ++){
      if(strncmp(fname,boot_block->dentry[i].file_name,32) == 0){
        for(j = 0; j < 32; j++){
          dentry->file_name[j] = boot_block->dentry[i].file_name[j];
        }
        dentry->file_type = boot_block->dentry[i].file_type;
        dentry->num_inode = boot_block->dentry[i].num_inode;
        return 0;
      }
  }
  printf("file not found!\n");
  return -1;
}

/* read_dentry_by_index
 *  input: index
 *         directory entry
 *  output: directory entry written with the file name
 *          file type and num_inode
 *  return: -1 on failure(non existent dile or invalid index)
 *          0 on success
 */
int32_t read_dentry_by_index (uint32_t index, dentry_t* dentry){
  int i;
  if(dentry == NULL){
    printf("NULL pointer!\n");
    return -1;
  }

  if(index > 62){
    printf("index not valid!\n");
    return -1;
  }

  for(i = 0; i < 32; i++){
    dentry->file_name[i] = boot_block->dentry[index].file_name[i];
  }
  dentry->file_type = boot_block->dentry[index].file_type;
  dentry->num_inode = boot_block->dentry[index].num_inode;
  return 0;
}

/* read_data
 *  input: inode  -- to find the file
 *         offset -- starting point to read
 *         buffer -- place the bytes read there
 *         length -- num of bytes to read
 *  output: directory entry written with the file name
 *          file type and num_inode
 *  return: -1 on failure(non existent dile or invalid index)
 *          0 on success
 */
int32_t read_data (uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length){
  int i,j,copy_index;
  inode_t *inode_addr = (inode_t *)(boot_block+inode+1);
  uint8_t *data_start = (uint8_t *)(boot_block+boot_block->num_inode+1);
  uint8_t *data;
  if(buf == NULL){
    return -1;
  }
  i=offset/KB4;//index for number of data block to start reading from
  j=offset%KB4;//index for number of bytes in the starting data block to start with
  for(copy_index = 0; copy_index < length; copy_index++){
    if(inode_addr->data_block[i]>boot_block->num_data_block){
      printf("invalid block num!\n");
      return -1;
    }
    data = data_start + inode_addr->data_block[i]*KB4;
    *(buf+copy_index) = *(data+j);
    j++;
    if(j>KB4){
      j = 0;
      i++;
    }
  }
  return copy_index;
}
