#ifndef _OS_ERROR_H
#define _OS_ERROR_H
/***
 *  OS Error Header
 *  Charles. 2016-9-1
 */
#include <stdio.h>
#include <errno.h>

#define os_err(fmt, ...) \
    do { \
        fprintf(stderr, "[%s:%d] [%s] ", __FILE__, __LINE__, __FUNCTION__); \
        fprintf(stderr, fmt, ##__VA_ARGS__); \
        fprintf(stderr, "\n"); \
    } while (0)

#endif
