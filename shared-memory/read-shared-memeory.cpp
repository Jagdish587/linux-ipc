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
    char *virt_addr;
    struct stat sb;
    
    fd = shm_open(NAME , O_RDONLY, 0);    /* Open existing object */
    if (fd == -1){
        cout<<"shm_open failed\n" ;
		exit(EXIT_FAILURE);
	}
    
    
    #if 0
         struct stat {
               dev_t     st_dev;         /* ID of device containing file */
               ino_t     st_ino;         /* Inode number */
               mode_t    st_mode;        /* File type and mode */
               nlink_t   st_nlink;       /* Number of hard links */
               uid_t     st_uid;         /* User ID of owner */
               gid_t     st_gid;         /* Group ID of owner */
               dev_t     st_rdev;        /* Device ID (if special file) */
               off_t     st_size;        /* Total size, in bytes */
               blksize_t st_blksize;     /* Block size for filesystem I/O */
               blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

               /* Since Linux 2.6, the kernel supports nanosecond
                  precision for the following timestamp fields.
                  For the details before Linux 2.6, see NOTES. */

               struct timespec st_atim;  /* Time of last access */
               struct timespec st_mtim;  /* Time of last modification */
               struct timespec st_ctim;  /* Time of last status change */

           #define st_atime st_atim.tv_sec      /* Backward compatibility */
           #define st_mtime st_mtim.tv_sec
           #define st_ctime st_ctim.tv_sec
           };
    #endif
    
    // retrive info like size, ownership and permissions
    if (fstat(fd, &sb) == -1){
        cout<<"fstat failed \n";
		exit(EXIT_FAILURE);
	}
	
	cout<<"sb size before = "<<sb.st_size<<endl;

    virt_addr = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (virt_addr == MAP_FAILED) {
        cout<<"mmap failed \n";
		exit(EXIT_FAILURE);
	}

    if (close(fd) == -1) {                    /* 'fd' is mo longer needed */
        cout<<"close fd failed\n";
        exit(EXIT_FAILURE);
    } 
    
    cout<<"after mmap size = sb.st_size "<<sb.st_size<<endl;   

    write(STDOUT_FILENO, virt_addr, sb.st_size);
    cout<<endl;
    
    munmap((void *)virt_addr, sb.st_size);

    
    
	return 0;
}	
