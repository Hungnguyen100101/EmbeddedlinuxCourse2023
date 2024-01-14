#include <sys/socket.h>         //socket()
#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int port_no;
    struct sockaddr_in *serv_addr;
    /* Create socket */
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1)  {
        handle_error("Create socket failed");
    }
    /* Initial address for server */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    /* Bind */
    if ( bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)  {
        handle_error("Bind failed");
    }
    
}