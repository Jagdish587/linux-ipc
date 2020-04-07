#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

#define MYFIFO "/tmp/myfifo"

int main()
{
  int fd = open(MYFIFO, O_RDONLY);
   char readbuff[100] ;

   if(fd == -1) {
     cout<<"read file opening failed \n";
     exit(EXIT_FAILURE);
   } else {
     cout<<"read data from fifo\n";
     read(fd, readbuff, sizeof (readbuff));
     cout<<"reading done with value = "<<readbuff;
   }
   
   cout<<endl;

   close(fd);
  
  return 0;
}	


