
Region *allocreg(FILE * fd,int type){                    
    region new_region;
                                                        // * Should add a malloc when creating it.
    remove_region(free_regions,new_region);             // Remove region from linked list of free regions
    locked_region->r_type=type;                         // Assign region type
    locked_region->fd=fd;                               // Assign region file descriptor
    if (fd)
        (fd->ref_count)++;                              // Increment inode reference count
    add_region(active_regions,new_region);              // Add the region to the active list.
    return new_region;
}

Region *dupreg(Region * region){
    Region new_region;                                  // * Should add a malloc when creating it.
    if (region.r_shared)
        (region->ref_count)++;
        attachreg(region, , region->loc, SHARED);/* caller will increment region reference count with subsequent attachreg call */
        return region;
    allocreg(, region->r_type);
                                    //set up auxiliary memory management structures, as currently exists in input region;
                                    //allocate physical memory for region contents;
                                    //"copy" region contents from input region to newly allocated region;
    return * newregion;
}

attachreg (region * region, process process, int address, int r_type){   /* attach a region to a process */
//(1) pointer to (locked) region being attached
//(2) process to which region is being attached
//(3) virtual address in process where region will be attached
//(4) region type
//output: per process region table entry
                                        //allocate per process region table entry for process;
                                        //initialize per process region table entry;
                                        //set pointer to region being attached;
    region->r_type=r_type;              //set type field;
    region->loc=address;                //set virtual address field;
                                        //check legality of virtual address, region size;
    (region->ref_count)++;              //increment region reference count;
    //(process->size)+=region->r_size;  //increment process size according to attached region;
                                        //initialize new hardware register triple for process;

    return (per process region table entry);
}

void detachreg(per_process_region_table_entry * pregion){ /* detach a region from a process */
    //get auxiliary memory management tables for process,
        //release as appropriate;
    //decrement process size;
    //(region.ref_count)--;   //decrement region reference count;
    //if (region_ref_count=0 && region not sticky bit)
        //freereg( );
    //else{  either reference count non-0 or region sticky bit on */
        //free inode lock, if applicable (inode associated with region);
        //free region lock;
    //}
}

void growreg(per_process_region_table_entry * pregion, int changesize) {    /* change the size of a region */
    //(1) pointer to per process region table entry
    //(2)change in size of region (may be positive or negative)
    if (changesize>0){
                                                            //check legality of new region size;
                                                            //allocate auxiliary tables(page tables); //physical addresses
        if (not system supporting demand paging) {
                                                            //allocate physical memory;
                                                            //initialize auxiliary tables, as necessary;
        }
    } else {    /* region size decreasing */
                                                            //free physical memory, as appropriate;
                                                            //free auxiliary tables, as appropriate;
    }
                                                            //do (other) initialization of auxiliary tables, as necessary;
    //                                                      //set size field in process table;
}

void loadreg(per_process_region_table_entry * pregion, int address, inode * inode, int offset, int amount) {/* load a portion of a file into a region */
//(1) pointer to per process region table entry
//(2) virtual address to load region
//(3) inode pointer of file for loading region
//(4) byte offset in file for start of region
//(5) byte count for amount of data to load
    growreg();
    //r_state=              //mark region state: being loaded into memory;
    //r_status=UNLOCKED;    //unlock region;
                            //set up u area parameters for reading file:
                                //target virtual address where data is read to,
                                //start offset value for reading file,
                                //count of bytes to read from file;
                            //read file into region (internal variant of read algorithm);
    //r_status=LOCKED;      //lock region;
    //r_state=              //mark region state: completely loaded into memory;
                            //awaken all processes waiting for region to be loaded;
}

void freereg(region * region){ /* free an allocated region */
if (region->ref_count!=0){ /* some process still using region */
    //region->r_status      //release region lock;
    if //(region->inode)    //(region has an associated inode)
                            //release inode lock;
    return;
}
if (region has associated inode)
    //iput();                       //release inode (algorithm iput);
                                    //free physical memory still associated with region;
                                    //free auxiliary tables associated with region;
                                    //clear region fields;
                                    //place region on region free list;
    //region->r_status=UNLOCKED;    //unlock region;
}