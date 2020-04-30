#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

#define PORT 8080



int main()
{

    // socket creates end point for communication and returns file desciptor
    // that refers to the end point
    string buffer = "Hello I am from client";
    char readbuff[1024] = {0};
    
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) {
        cout<<"socket creation  failed "<<strerror(errno);
        exit(EXIT_FAILURE);
    } else {
        cout<<"client socket fd = "<<fd<<endl;
    }

    struct sockaddr_in serveraddr;
    serveraddr.sin_family =  AF_INET;
    serveraddr.sin_port = htons(PORT);

    // inet_pton - convert IPv4 and IPv6 addresses from text to binary form
    inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr);

    int ret = connect(fd, (struct sockaddr* )&serveraddr, sizeof (serveraddr));
    if(ret < 0) {
        cout<<"socket connect failed "<<strerror(errno)<<endl;
        exit(EXIT_FAILURE);
    }


    ret = send(fd, buffer.c_str(), buffer.length(), 0);
    if(ret < 0) {
        cout<<"client send call failed \n";
        exit(EXIT_FAILURE);
    } else {
        cout<<"send call no of bytes written = "<<ret<<endl;
    }
    
    read(fd, readbuff, sizeof(readbuff));
    
    cout<<"Message from server = " <<readbuff<<endl;

    close(fd);

    return 0;
}
