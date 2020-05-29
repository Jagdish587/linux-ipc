#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

#define PORT 8080
#define serveraddr 192.168.16.128


int main()
{
    // lets create socket first

    char buffer[1024] = {0};
    int opt = 1;
    struct sockaddr_in addr;
    
    // Here SOCK_STREAM = TCP , SOCK_DGRAM = UDP
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) {
        cout<<"socket creation failed "<<strerror(errno);
        exit(EXIT_FAILURE);
    } else {
        cout<<"server socket creation success fd = "<<fd<<endl;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    int addrlen = sizeof (addr);

    // Forcefully attaching socket to the port 8080
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        cout<<"setsockopt failed ";
        exit(EXIT_FAILURE);
    }
    
    // bind an adress to the socket 
    bind(fd, (struct sockaddr *)&addr, sizeof (addr));

    while(1) {
        char writebuff[1024] = "Hello client , Welcome to World of Socket ";
        
        // queue limit for incoming connections are specified with listen
        listen(fd, 3);

		 cout<<"Server Waiting for Clients  \n";
		
		// accept a connection on a socket
        int clientfd = accept(fd, (struct sockaddr*)&addr, (socklen_t*)&addrlen);

        read(clientfd, buffer, sizeof (buffer));

        cout<<"Server : Message from client = "<<buffer;

        cout<<endl;

        write(clientfd, writebuff, sizeof (writebuff));

    }
    return 0;
}
