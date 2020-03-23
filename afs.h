//WORK IN PROGRESS THE DESCRIPTIONS ARE INCOMPLETE

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
   MORE INFO WILL BE WRITTEN IN AN ANNEX
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
DIR * opendir(const char * path);
/* Opens a directory returning an abstract data structure representing it
   PARAMETERS:
   (char *) path : the abstract path of the objective represented by a string
   RETURNS:
   DIR * : NULL if error, a direction to the new DIR structure if succesful
 */

struct dirent * readdir(DIR * directory);
/* Extracts an entry of the directory aimed by a read pointer and moves the read pointer to the next entry
   PARAMETERS:
   (DIR *) directory : the directory strucure where the entries will be read
   RETURNS:
   struct dirent : NULL if error or end of directory, or the following struct (Susceptible to expansion (Suggestions are welcome)):
          struct dirent {
             char * d_name; (This is the only field that is actually needed, other information can be extracted from this)
             ...
          }
 */

void closedir(DIR * directory);
/* Closes the directory represented by the DIR strucure provided.
   PARAMETERS:
   (DIR *) directory : the structure stated before.
   RETURNS:
 */

int mkdir(const char * path,mode_t mode);
/* Creates a new directory whose path shall be the string provided as argument
   PARAMETERS:
   (const char *) path : the path of the new directory if is not a valid path an error will be generated
   (mode_t) mode : the permissions that correspond to the new directory in the moment of its creation
   RETURNS:
   int : 0 if succesful, something else means an error or a restricted operation
 */

//GLOBAL OPERATIONS

int stat(const char * path, struct stat * buf);
/* Gives to the caller the meta-information of an abstract filesystem object (like a file or a directory) if it is possible
   PARAMETERS:
   (const char * path) : the path of the objective (if not valid an error will be generated)
   (struct stat * buf) : a direction to a memory space ready to be filled with the requested data as an struct stat
   RETURNS:
   int : 0 if succesful, something else means an error or a restricted operation
   THE STAT STRUCT:
      struct stat {
         NOT DEFINED YET
         DATA TO BE EXPECTED:
            - File name
            - File type
            - Size
            - User
            - Permissions
            - Modification data
            ...
      }
 */

int chmod(const char * path,mode_t mode);
/* This function rewrites the permissions of a file as stated in the mode argument if possible
   PARAMETERS:
   (const char *) path : the path of the objective (if not valid an error will be generated)
   (mode_t) mode : the new set of permissions (macros will be defined for the construction of this field)
   RETURNS:
   int : 0 if succesful, something else means an error or a restricted operation
 */

