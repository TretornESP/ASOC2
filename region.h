//The region table entry contains the information necessary to describe a region.

typedef struct{
    FILE * fd;                      // A pointer to the file descriptor of the file 
                                    //      whose contents were originally loaded into the region
    int r_type;                     // The region type (text, private data or stack)
    int r_shared;                   // Indicates that is or not shared memory
    int r_size;                     // The size of the region
    int r_loc;                      // The location of the region in physical memory
    int r_status;                   // The status of a region, which may be a combination of
                                    //      locked
                                    //      in demand
                                    //      in the process of being loaded into memory
                                    //      valid, loaded into memory
    int ref_count;                  // Amount of processes that reference the region.
}Region;

typedef Region  *Free_regions;      // Table that contains all free regions

typedef Region  *Free_regions;      // Table that contains all active regions

/*  ALLOCREG
    Allocates a new region for a process
    PARAMETERS:
        FILE * fd       : File descriptor if there is of the file that is loaded in the region
        int type        : Type of region to allocate
        
    RETURNS:
        Region          : The new region allocated
*/ 

Region *allocreg(FILE *,int);

/*  DUPREG
    Duplicates a region 
    PARAMETERS:
        Region * region : Region we want to duplicate
        
    RETURNS:
        Region          : The new region generated
*/ 

Region *dupreg(Region * region);

/*  
    ATTACHREG
    Ataches a region to a process
    PARAMETERS:
        FILE * fd       : File descriptor if there is of the file that is loaded in the region
        int type        : Type of region to allocate
        
    RETURNS:
        Region          : The new region allocated
*/ 

void attachreg (Region *, Proc, int /*address*/, int /*r_type*/);

/*  DETACHREG
    Detaches a region from the process
    PARAMETERS:
        Region * reg    : Region you want to detach
        int size        : Amount of Bytes to change (it allows negative values to decrement it)
        
    RETURNS:
        void            : There is no return value
*/ 

void detachreg(Region*,Proc *);


/*  GROWREG
    Modifies the size of a region
    PARAMETERS:
        Region * reg    : Region you want to detach
        Proc * process  : Process from which you want to detach it
        
    RETURNS:
        void            : There is no return value
*/ 

void growreg(Region *, int);

/*  LOADREG
    Loads data to a region
    PARAMETERS:
        Region * reg    : Region you want to load data in
        FILE * fd       : File descriptor from where to load the data
        int offset      : Byte offset in the file to start reading
        int amount      : Amount of bytes to read
        
    RETURNS:
        void            : There is no return value
*/ 

void loadreg(Region *, FILE *, int, int);

/*  FREEREG
    Free an allocated region
    PARAMETERS:
        Region * reg    : Region to free
        
    RETURNS:
        void            : There is no return value
*/ 

void freereg(Region *);
