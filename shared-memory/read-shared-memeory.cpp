#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define NAME "/myshm"

using namespace std;

int main(int argc, char *argv[])
{	
    int fd;
    char *addr;
    struct stat sb;
    
    fd = shm_open(NAME , O_RDONLY, 0);    /* Open existing object */
    if (fd == -1){
        cout<<"shm_open failed\n" ;
		exit(EXIT_FAILURE);
	}

    /* Use shared memory object size as length argument for mmap()
       and as number of bytes to write() */

    if (fstat(fd, &sb) == -1){
        cout<<"fstat failed \n";
		exit(EXIT_FAILURE);
	}

    addr = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        cout<<"mmap failed \n";
		exit(EXIT_FAILURE);
	}

    if (close(fd) == -1) {                    /* 'fd' is mo longer needed */
        cout<<"close fd failed\n";
        exit(EXIT_FAILURE);
    }    

    write(STDOUT_FILENO, addr, sb.st_size);
    cout<<endl;
    
    
	return 0;
}	
