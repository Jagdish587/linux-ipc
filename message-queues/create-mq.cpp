#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

using namespace std;

#define NAME "/mymsgq"

int main()
{
  mqd_t mqd;
  struct mq_attr attr;

  attr.mq_maxmsg = 50;
  attr.mq_msgsize = 2048;

  mqd = mq_open(NAME,O_RDWR | O_CREAT, 666, &attr);

  if(mqd == (mqd_t) -1) {
    cout<<"message queue creation failed \n";
    exit(EXIT_FAILURE);
  } else {
    cout<<"message queue creation Sucess id = "<<mqd;
  }
  
  cout<<endl;
	
	return 0;
}
