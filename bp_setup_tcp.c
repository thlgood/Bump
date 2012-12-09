#include "basic.h"
#include "bp_socket.h"


/*
   setup tcp socket.
   if success, return socket, or return a value < 0 and set errno
 */
int setup_tcp(char *port)
{
    struct sockaddr_in server_addr;
    in_port_t server_port;
    int sock;
    int retval;                     //return value

    //set port
    if (port == NULL)
    {
        server_port = (in_port_t)DEFAULT_PORT;
    }
    else if ((server_port = atoi(port)) < 0)
    {
        fprintf(stderr, "Error port: %d in line %d\n", (int)server_port, __LINE__);
        fprintf(stderr, "Use default port: %d\n", DEFAULT_PORT);
    }

    //Create socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
    {
        return sock;
    }

    //Bind
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port        = htons(server_port);
    server_addr.sin_family      = AF_INET;
    retval = bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (retval < 0)
    {
        perror("bind");
        return retval;
    }


    //Listen
    retval = listen(sock, 40);
    if (retval < 0)
    {
        return retval;
    }

    return sock;
}

/*
int main()
{
    printf("%d\n", setup_tcp("4558"));
    perror("");
    return 0;
}*/
