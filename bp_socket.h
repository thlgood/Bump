#ifndef BP_SOCKET
#define BP_SOCKET

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int setup_tcp(char* port);

#endif //end file
