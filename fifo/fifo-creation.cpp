#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

#define MYFIFO "/tmp/myfifo"

int main()
{
	int fd;
  /* Create the FIFO if it does not exist */
  umask(0);
  mkfifo(MYFIFO, 0666);
  
	return 0;
}	
