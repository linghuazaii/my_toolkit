#ifndef _OS_IO_H
#define _OS_IO_H
/***
 *  OS IO Header
 *  Charles. 2016-9-1
 */
#include <unistd.h>

size_t os_read(int fd, void *&buf, size_t nbyte);

#endif
