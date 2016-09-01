#include "os_io.h"
#include "os_error.h"
#include <unistd.h>
#include "os_alloc.h"

/***
 * You need to manage the memory
 */
size_t os_read(int fd, void *&buf, size_t nbyte) {
    buf = os_new(OS_PAGE * ((nbyte / OS_PAGE) + 1));
    int offset = 0, count = 0;

    while (offset = read(fd, (void *)((char *)buf + count), OS_PAGE)) {
        if (offset == -1) {
            perror("read()");
            buf = NULL;
            return offset;
        }

        count += offset;
        if (count == nbyte)
            break;
    }

    return count;
}

