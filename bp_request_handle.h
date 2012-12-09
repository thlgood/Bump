#ifndef REQUEST_HANDLE
#define REQUEST_HANDLE
#include "bp_socket.h"

#define OK_HEADER "HTTP/1.0 200 OK\r\n\r\n"
#define NOT_FOUND "HTTP/1.0 404 Not Found\r\n\r\n"

int request_handle(int client_sock, struct sockaddr_in *addr, socklen_t *addrlen);

#endif
