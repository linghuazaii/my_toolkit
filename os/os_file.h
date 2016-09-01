#ifndef _OS_FILE_H
#define _OS_FILE_H
/***
 *  Os File Header
 *  Charles. 2016-9-1
 ***/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int os_open_r(const char *pathname, bool create_flag = false, int extra_flags = O_RDONLY);
int os_open_w(const char *pathname, bool create_flag = false, int extra_flags = O_WRONLY);
int os_open_rw(const char *pathname, bool create_flag = false, int extra_flags = O_RDWR);
int os_open_a(const char *pathname, bool create_flag = false, int extra_flags = O_APPEND);

#endif
