//Operaciones en ficheros

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
FILE * fopen(const char * path,const char * mode);
/*
  int fgetc(FILE *stream);

// Reads nelem elements of size size each, from stream file and stores them into ptr pointer
ssize_t fread(void *ptr, size_t size, size_t nelem, FILE *stream);

//Writes one byte in the stream
int fputc(int c, FILE *stream);

// Writes nelem elements of size size each, from stream file and stores them into ptr point
ssize_t fwrite(void *ptr, size_t size, size_t nelem, FILE *stream);
*/

/* Closes the file represented by the given abstract structure
   Parameters:
       (FILE *) file : a FILE data structure
   RETURNS:
       int : 0 if succesful, non zero value means the opposite
 */
int fclose(FILE * file);


