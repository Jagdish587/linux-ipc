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
    unsigned int prio = 60;
    char messagebuffWrite[] = "MyMessage sending first buffer with prio 60";
    char messagebuffWrite2[] = "MyMessage sending second buffer with prio 70";

    flags = O_WRONLY ;
    mqd = mq_open(NAME , flags);

    if (mqd == (mqd_t) -1) {
        cout<<"mq_open failed \n";
    }    

    if (mq_send(mqd,messagebuffWrite, sizeof(messagebuffWrite) , prio) == -1)
        cout<<"mq_send 1 failed \n";
    else {
    	cout<<"message1 write success\n";
    }

	prio = 70;
    if (mq_send(mqd, messagebuffWrite2, sizeof(messagebuffWrite2) , prio) == -1)
        cout<<"mq_send 2 failed ";
    else {
    	cout<<"message2 write success\n";
    }
	
}
