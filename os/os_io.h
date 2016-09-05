#ifndef _OS_IO_H
#define _OS_IO_H
/***
 *  OS IO Header
 *  Charles. 2016-9-1
 */
#include <unistd.h>
#include <stdio.h>

ssize_t os_read(int fd, void *&buf, size_t nbyte);
ssize_t os_write(int fd, void *buf, size_t nbyte, bool sync_flag = false);
int os_fsync(int fd);

int os_fgetc(FILE *stream);
int os_ungetc(int c, FILE *stream);
char *os_fgets(char *s, int size, FILE *stream);

#endif
