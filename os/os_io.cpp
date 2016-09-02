#include "os_io.h"
#include "os_error.h"
#include <unistd.h>
#include "os_alloc.h"

/***
 * You need to manage the memory
 */
ssize_t os_read(int fd, void *&buf, size_t nbyte) {
    buf = os_new(OS_PAGE * ((nbyte / OS_PAGE) + 1));
    int offset = 0, count = 0;

    while (offset = read(fd, (void *)((char *)buf + count), OS_PAGE)) {
        if (offset == -1) {
            int errnum = errno;
            if (errno == EINTR)
                continue;
            perror("read()");
            buf = NULL;
            return offset;
        }

        count += offset;
        if (count <= nbyte)
            break;
    }

    return count;
}

ssize_t os_write(int fd, void *buf, size_t nbyte, bool sync_flag) {
    int res = write(fd, buf, nbyte);
    if (res == -1)
        perror("write()");

    if (sync_flag)
        os_fsync(fd);

    return res;
}

int os_fsync(int fd) {
    int res = fdatasync(fd);
    if (res == -1)
        perror("fdatasync()");

    return res;
}
