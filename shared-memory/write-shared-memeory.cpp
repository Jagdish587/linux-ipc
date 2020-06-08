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

int main(int argc, char *argv[])
{
	int fd;
    size_t len;                 /* Size of shared memory object */
    char *virt_addr;
    char writebuff[] = "Jagdish Tirumala , Hello mmap ";

    fd = shm_open(NAME , O_RDWR, 0);      /* Open existing object */
    if (fd == -1){
        cout<<"shm_open failed \n";
		exit(EXIT_FAILURE);
	} else {
		cout<<"shm_open with fd = "<<fd<<endl;
	}	

    len = sizeof(writebuff);

    // changes in size , set size for object
    if (ftruncate(fd, len) == -1){        /* Resize object to hold string */
        cout<<"ftruncate failed\n";
		exit(EXIT_FAILURE);
	}
	
	cout<<"len before = "<<len<<endl;

#if 0
    
    void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);
           
     int munmap(void *addr, size_t length);


#endif
    virt_addr = (char *)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (virt_addr == MAP_FAILED) {
        cout<<"mmap failed\n";
        exit(EXIT_FAILURE);        
    }    

   if (close(fd) == -1)                    /* 'fd' is no longer needed */
        cout<<"close fd failed \n";

    cout<<" copying bytes "<<len<<endl;
    memcpy(virt_addr, writebuff, len);
    
    
    
    cout<<endl;
    
    munmap((void *)virt_addr, len);
	
	return 0;
}	
