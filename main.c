#include <unistd.h> //geteuid
#include <signal.h>
#include "basic.h"
#include "bp_socket.h"
int main(int argc, char *argv[])
{
    int sock;
    int retval;
    void *port = NULL;

    //Check user effective ID
    if (geteuid() != 0)
    {
        fprintf(stderr, "Must run as root permission!\n");
        exit(1);
    }

    //setup socket
    port = (argc == 1) ? NULL:argv[1];
    sock = setup_tcp(port);
    if (sock < 0)
    {
        perror("setup_tcp");
        exit(1);
    }
    
    int client_sock;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);/*
    client_sock = accept(sock, (struct sockaddr*)&addr, &addrlen);
    if (client_sock < 0)
    {
        perror("accept");
    }
    if ((retval = request_handle(client_sock, &addr, addrlen)) < 0)
    {
        perror("request_headle");
        printf("%d\n", retval);
        exit(1);
    }*/
    while (1)
    {
        client_sock = accept(sock, (struct sockaddr*)&addr, &addrlen);
        if (client_sock < 0)
        {
            perror("accept");
            continue;
        }
        if (0 == fork())
        {
            if ((retval = request_handle(client_sock, &addr, addrlen)) < 0)
            {
                perror("request_headle");
                printf("%d\n", retval);
                exit(1);
            }
            exit(0);
        }
        close(client_sock);
    }
}
