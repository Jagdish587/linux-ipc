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
	// lets create shared memory object 
	// you can check your shared memeory in /dev/shm/
	int fd;
				
	fd = shm_open(NAME , O_CREAT | O_RDWR , 0777);
    if (fd == -1){
        cout<<"shm_open failed\n";
        exit(EXIT_FAILURE);
    } else {
    	cout<<"shared memory open success fd = "<<fd<<endl;
    }

	return 0;	
	
}	
