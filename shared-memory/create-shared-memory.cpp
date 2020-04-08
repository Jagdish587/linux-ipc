#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>

#define NAME "/myshm"

using namespace std;

int main()
{
	// lets create shared memeory object 
	int fd;
	size_t size = getpagesize();
	void *addr ;
				
	fd = shm_open(NAME , O_CREAT | O_RDWR , 0777);
    if (fd == -1){
        cout<<"shm_open failed\n";
        exit(EXIT_FAILURE);
    } else {
    	cout<<"shared memory open success fd = "<<fd<<endl;
    }
	
	if (ftruncate(fd, size) == -1){        /* Resize object to hold string */
        cout<<"ftruncate call failed ";
		exit(EXIT_FAILURE);
	}	
	
    addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED){
        cout<<"mmap failed \n";
        exit(EXIT_FAILURE);
    }
	
	return 0;	
	
}	
