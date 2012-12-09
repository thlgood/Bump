#include "basic.h"
#include "bp_socket.h"
#include "bp_request_handle.h"
#include <string.h>
#include "bp_load_file.h"

int request_handle(int client_sock, struct sockaddr_in *addr, socklen_t *addrlen)
{
    char buf[BUFSIZ];
    char source[BUFSIZ];
    ssize_t ret_size;
    int retval;
    char *content;
    retval = recv(client_sock, buf, BUFSIZ, 0);
    if (retval < 0)
        return retval;

    retval = sscanf(buf, "%s%s", source, source);
    if (retval < 0)
    {
        return 0;
    }

    retval = bp_load_file(source, &content);
    if (retval < 0)
        return retval;

    retval = write(client_sock, content, retval);
    close(client_sock);
    free(content);
    return 0;
}
