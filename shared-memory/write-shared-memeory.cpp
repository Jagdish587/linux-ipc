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
    char *addr;
    char writebuff[] = "Jagdish Tirumala";

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

    addr = (char *)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        cout<<"mmap failed\n";
        exit(EXIT_FAILURE);        
    }    

   if (close(fd) == -1)                    /* 'fd' is mo longer needed */
        cout<<"close fd failed \n";

    cout<<" copying bytes "<<len<<endl;
    memcpy(addr, writebuff, len);
    
    cout<<endl;
	
	return 0;
}	
