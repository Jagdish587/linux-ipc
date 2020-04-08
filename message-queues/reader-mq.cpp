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
	int flags, opt;
    mqd_t mqd;
    unsigned int prio;
    struct mq_attr attr;
    long  maxsize = attr.mq_msgsize;   
	char readbuff[2048];
    ssize_t numRead;
       
    mqd = mq_open(NAME , O_RDONLY);
    if (mqd == (mqd_t) -1) {
        cout<<"mq_open failed\n";
         exit(EXIT_FAILURE);
    } else {
		cout<<"message queue open success id = "<<mqd<<endl;
	}	

	cout<<"reading from queue ..!!\n";	
    numRead = mq_receive(mqd, readbuff, attr.mq_msgsize, &prio);     
    
    if(numRead == -1) {
		cout<<"message queue read failed\n";
		exit(EXIT_FAILURE);
	} else {
		cout<<"no of bytes read = "<<numRead<<" prio = "<<prio<<endl;		
		write(STDOUT_FILENO, readbuff, numRead);
				
		write(STDOUT_FILENO,"\n",1);		
	}

}
