#include "basic.h"
#include "bp_config.h"
#include <limits.h>
#include <fcntl.h> 
#include <errno.h>
#include "bp_request_handle.h"

int bp_load_file(char* path, char** buf)
{
    char abs_path[PATH_MAX];
    char mem[BUFSIZ];
    int fd;
    int retval;
    struct stat file_info;
    char *tmp;
    int size;

    if (!strcmp(path, "/"))
    {
        strcpy(abs_path, INDEX_PATH);
    }
    else
    {
        strcpy(abs_path, ROOT);
        strcat(abs_path, path);
    }

    fd = open(abs_path, O_RDONLY);
    if (fd > 0 )
    {
        lstat(abs_path, &file_info);
        size = file_info.st_size + strlen(OK_HEADER);
        *buf = (char*)malloc(size);
        strcpy(*buf, OK_HEADER);
        tmp = *buf + strlen(OK_HEADER);
    }
    else
    {
        strcpy(abs_path, NOT_FOUND_PATH);
        fd = open(abs_path, O_RDONLY);
        lstat(abs_path, &file_info);
        size = file_info.st_size + strlen(NOT_FOUND);
        *buf = (char*)malloc(size);
        strcpy(*buf, NOT_FOUND);
        tmp = *buf + strlen(NOT_FOUND);
    }
    retval = read(fd, tmp, file_info.st_size);
    close(fd);
    return size;
}
