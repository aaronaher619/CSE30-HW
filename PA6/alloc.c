#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

size_t HEAP_SIZE = 1028; // in bytes (e.g. 1kb of memory)
int WORD_SIZE = sizeof(int);

void* heap_ptr = NULL;
void* current_free_list = NULL;

void setup_heap() {
  // The mmap system call asks the operating system to please put HEAP_SIZE
  // memory into this process's address space. The resulting addresses
  // start at the very beginning of heap space (more or less). This is the
  // lowest-level interface to access memory without writing an operating
  // system yourself. It returns memory in fairly large chunks (usually
  // at least 1kb gets mapped at a time).
  heap_ptr = mmap(NULL, HEAP_SIZE, PROT_READ | PROT_WRITE, MAP_ANON |
		  MAP_SHARED, -1, 0);
  
  // Set the first word on the heap to hold the total size available.
  // See above for a description of *(int*)ptr
  *(int*)heap_ptr = HEAP_SIZE - WORD_SIZE;
  *(void**)(heap_ptr+WORD_SIZE) = NULL;
  current_free_list = heap_ptr;
}

void teardown_heap(){
  munmap(heap_ptr, HEAP_SIZE);
  heap_ptr = NULL;
  current_free_list = NULL;
}

/**
 *  my_malloc - gives a spcified amount of memory to the user to use
 *
 *  Parameters:
 *    size_t size - the size that the user wants to use for memory
 *
 *  Return value: address for the reserved memory
 */
void* my_malloc(size_t size){
  int free_size; //size of current free pointer
  void* free_ptr = current_free_list; //current free pointer
  void* parent_ptr = current_free_list; //parent of free_ptr
  void* retptr; //retrun pointer

  //If no more free space
  if(current_free_list == NULL){
    return NULL;
  }

  //If size is negative
  if (size <= 0){
    return NULL;
  }

  //If size isnt a multiple of 4
  else if ((size % 4) != 0){
    size = size + (WORD_SIZE - (size % 4));    
  }

  while (1){
    //hold size of current free pointer
    free_size = *(int*)free_ptr;

    //if the free size is big enough
    if (free_size >= size){
      
      //If it found a free spot not to split
      if ((free_size == size) || ((size + 4) == free_size)){

	++ *(int*) free_ptr; //mark as occupied
	retptr = (free_ptr + WORD_SIZE); //get the return pointer
	
	//If it used up rest of free space
	if ((*(void**)(free_ptr + WORD_SIZE) == NULL)){
	  current_free_list = NULL;
	}

	//change the free list
        else if (!(parent_ptr == free_ptr)){
          *(void**)(parent_ptr + WORD_SIZE) = free_ptr + size + WORD_SIZE;
        }

        //change the current free list
        else{
          current_free_list = *(void**) (current_free_list + WORD_SIZE);
        }

	//Return retptr
	return retptr; 
      }
      
      //If it found a tree spot to split
      else {

	//get return pointer
	retptr = (free_ptr + WORD_SIZE);
	
	//mark as occupied
	*(int*) free_ptr = size + 1;

	//modify occupied block size
	free_size = free_size - (size + WORD_SIZE);

	//Change size for free block
	*(int*) (free_ptr + size + WORD_SIZE) = free_size;

	//Change pointer for free block
	*(void**) (free_ptr + size + WORD_SIZE + WORD_SIZE) =
	  *(void**) (free_ptr + WORD_SIZE);

	*(void**)(free_ptr + WORD_SIZE) = (free_ptr + WORD_SIZE);
	
	//change the free list
	if(!(parent_ptr == free_ptr)){
	  *(void**)(parent_ptr + WORD_SIZE) = free_ptr + size + WORD_SIZE;
	}

	//change the current free list
	else{
	  current_free_list = free_ptr + size + WORD_SIZE;
	}
	
	//return
	return retptr;
      }
    }
    
    //check if there are no more free spaces
    else if (!(*(void**)(free_ptr + WORD_SIZE))){
      return NULL;
    }
        
    //change pointers for loop
    else{
      parent_ptr = free_ptr;
      free_ptr = *(void**)(free_ptr + WORD_SIZE);
    }
  }
  return NULL;
}

/**
 *  my_free - frees the reserved memory
 *
 *  Parameters:
 *    void* ptr - pointer to the reserved memory
 *
 *  Return value: 1 or 0 for success or failure respectively
 */
int my_free(void* ptr){

  //If ptr equals current_free_list or is empty
  if((current_free_list == ptr) && (current_free_list !=NULL)){
    return 0;
  }
  
  //Change pointer to get size
  void* pointer = ptr - WORD_SIZE;
  
  //Checks if address is a multiple of 4 or in range of heap
  if ((((int)ptr) % 4) != 0){ //|| (ptr > (heap_ptr + HEAP_SIZE))){
    return 0;
  }
  
  //If already freed
  else if (!(*(int*)(pointer) & 0x1)){
    return 0;
  }

  //mark as free
  -- *(int*)(pointer);

  //Change current free list
  if(current_free_list !=NULL){
    *(void**)(ptr) = current_free_list;
  } 
  current_free_list = pointer;
 
  //Return success
  return 1;
}

/**
 *  consolidate - combines adjacent free blocks of memory
 *
 */
void consolidate(){
  void* current_ptr = heap_ptr; //the current pointer

  //iterate through spaces
  while (1){

    //If its an occupied space the skip
    if (*(int*)current_ptr - *(int*)current_ptr){
      current_ptr += *(int*)current_ptr + WORD_SIZE;
      continue;
    }

    else{
      
    }

    //check if there are no more free spaces
    if (!(*(void**) (current_ptr + WORD_SIZE))){
      break;
    }

    //Change current ptr to continue loop
    current_ptr += *(int*)current_ptr + WORD_SIZE;
  }	
}

/**
 *  print_heap - prints the memory layout of the heap
 *
 */
void print_heap(){
  int i;
  int* addr = heap_ptr;
  int howmany = 10;
  
  for(i = 0; i < howmany; i += 1) {
    // In the format below,
    // - %p means "format as pointer"
    // - %d means "format as integer"
    // - %#010x means "format as 10 hex digits with a leading 0x"
    printf("%10p:\t%d\t%#010x\n", addr + i, *(addr + i), *(addr + i));
  }
}

/**
 *  free_space - counts the bites of free space in heap
 *
 *  Return value: amount of bites of free memory
 */
int free_space(){
  int retval = 0; // return value
  void* current_ptr = current_free_list; //the current pointer

  //If there is no free space
  if (current_free_list == NULL){
    return 0;
  }

  //iterate through my current_free_list
  while (1){
    
    if(*(int*) current_ptr > 1024){
      break;
    }

    //add up free space sizes
    retval += *(int*) current_ptr;
    
    //check if there are no more free spaces
    if (! (*(void**)(current_ptr + WORD_SIZE))){
      break;
    }
    
    //Change current ptr to continue loop
    current_ptr = *(void**) (current_ptr + WORD_SIZE);    
  }

  //Return retval
  return retval;
}

/**
 *  live_data - counts the bites of occupied space in heap
 *
 *  Return value: amount of bites of occupied memory
 */
int live_data(){
  int retval = 0; // return value
  void* current_ptr = heap_ptr; //the current pointer
  
  //iterate through all spaces
  while (1){
        
    //If its an occupied space then add to retval the size
    if ((*(int*)current_ptr & 0x1)){

      //add the size to retval
      retval += *(int*) current_ptr - 1;

      //Change current ptr to continue loop
      current_ptr += *(int*)current_ptr + WORD_SIZE - 1;
    }

    //check if its a free space and don't do aything to retval
    else if(!(*(int*)current_ptr & 0x1)){

      //If at the end of heap
      if (!(*(void**) (current_ptr + WORD_SIZE))){
	break;
      }

      //Change current ptr to continue loop
      current_ptr += *(int*)current_ptr + WORD_SIZE ;
    }
  }

  //Return retval
  return retval;
}
