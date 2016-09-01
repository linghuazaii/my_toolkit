#include "os_file.h"
#include "os_error.h"
#include <unistd.h>

int os_open_r(const char *pathname, bool create_flag, int extra_flags) {
    int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int flags = O_RDONLY | extra_flags;
    if (create_flag)
        flags |= O_CREAT;
    
    int res = open(pathname, flags, mode);
    if (res == -1) {
        perror(pathname);
    }

    return res;
}

int os_open_w(const char *pathname, bool create_flag, int extra_flags) {
    int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int flags = O_WRONLY | O_TRUNC | extra_flags;
    if (create_flag)
        flags |= O_CREAT;

    int res = open(pathname, flags, mode);
    if (res == -1)
        perror(pathname);

    return res;
}

int os_open_rw(const char *pathname, bool create_flag, int extra_flags) {
    int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int flags = O_RDWR | extra_flags;
    if (create_flag)
        flags |= O_CREAT;

    int res = open(pathname, flags, mode);
    if (res == -1)
        perror(pathname);

    return res;
}

int os_open_a(const char *pathname, bool create_flag, int extra_flags) {
    int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int flags = O_WRONLY | O_APPEND | extra_flags;
    
    int res = open(pathname, flags, mode);
    if (res == -1)
        perror(pathname);

    return res;
}

int os_close(int fd) {
    int res = close(fd);
    if (res == -1)
        perror("close()");

    return res;
}
