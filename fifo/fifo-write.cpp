#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

#define MYFIFO "/tmp/myfifo"

int main()
{
  int fd = open(MYFIFO, O_WRONLY);
  char writebuff[] = "Jagdish Tirumala writing";

  if(fd == -1) {
    cout<<"file opening failed \n";
    exit(EXIT_FAILURE);
  } else {
    cout<<"wrrting data to fifo\n";
    write(fd,writebuff,sizeof (writebuff));
    cout<<"writing done\n";
  }

  close(fd);
  
  return 0;
}	

