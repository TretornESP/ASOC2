
//FILE OPERATIONS


FILE * fopen(const char * path,const char * mode);
/*Opens the file that corresponds to the path, in the specified mode and returns a pointer to it
  PARAMETERS:
  (const char *) path : a string (abstract path) that indentifies the file to be opened by this call.
  (const char *) mode : a string that holds the permission values
  that this call will use to give access to a file.
  The format is explained below.
  RETURNS:
  FILE * : an abstract data structure that represents an opened file and
  is used by the other functions to operate with the file.
  --There is no official way to communicate errors yet
*/


int fclose(FILE * file);
/* Closes the file represented by the given abstract structure
   PARAMETERS:
   (FILE *) file : a FILE data structure
   RETURNS:
   int : 0 if succesful, non zero value means the opposite
*/


void * getablock(FILE * file,blk_num_t blk_num);
/* This function purpose is to be used by the I/O functions that are meant to deal with data stored in files.
   getablock() grants access to the data stored in a file with the corresponding permissions set by fopen.
   More specifically, this function pushes abstract data blocks from the secondary storage to main memory.
   If the block is already in memory this function gives to the process access to the block.
   If the block is modified during its presence in memory a daemon shall apply the modified block to the secondary
   storage, this is going to be done sistematically.
   If a non-existing block is requested, the block will be generated in memory like the others. When the flush occurs
   the new block will be added to the file in the filesystem. A block is considered in existence if is present in
   main memory OR in the filesystem.
   MORE INFO WILL BE WRITTEN IN A ANNEX
   PARAMETERS:
   (FILE *) file : the file where the requested abstract block stays.
   (blk_num_t) blk_num : the requested block (from 0)
   RETURNS:
   void * : NULL if there is an error, in the other hand it returns the direction of the first byte of the abstract block
*/

void flush();
/* This function tells the corresponding daemon to apply the changes in main memory to the filesystem.
   The daemon will try to accomplish this task as soon as is reasonable.
   PARAMETERS:
   RETURNS:
 */

//DIRECTORY OPERATIONS
DIR * opendir(char * path);
/**/ (Me estoy tomando un descanso vuelvo en un ratillo)

struct dirent * readdir(DIR * directory);
/**/

void closedir(DIR * directory);
/**/

int mkdir(const char * path,mode_t mode);
/**/

//GLOBAL OPERATIONS

int stat(const char * path, struct stat * buf);
/**/

int chmod(const char * path,mode_t mode);
/**/

