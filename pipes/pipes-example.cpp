#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main()
{

  // Pipes are half duplex one way communication ipc
  // data traveling through the pipe moves through the kernel
  // pipemust must be created befor calling fork , since 
  // both parent and child inherit all fd's
  // Note : Pipes are between realted process only 
  cout << "Hello World!" << endl;
  char writebuff[]= "Jagdish Tirumala";
  char readbuff[100];
  int mypipid[2];
  int retval ;

  // pipe returs two fd's , fd[0] -> read , fd[1] -> write
  retval = pipe(mypipid);

  if(retval == -1) {
    cout<<"pipe creation failed \n";
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();

  if(pid == -1) {
    cout<<"fork call failed  \n";
    exit(EXIT_FAILURE);
  } else if (pid == 0){
    cout<<"This is Child  Process \n";
    write(mypipid[1], writebuff, sizeof (writebuff));
    cout<<"Done writing of data \n";
  } else {
    cout<<"This is Parent Process \n";

    // Here read is blocking call , so even if parent comes first , the call gets blocked
    read(mypipid[0],readbuff,sizeof (readbuff));
    cout<<"read buff = "<<readbuff<<endl;
  }



  return 0;
}

