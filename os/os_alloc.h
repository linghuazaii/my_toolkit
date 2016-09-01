#ifndef _OS_ALLOC_H
#define _OS_ALLOC_H
/***
 *  OS Alloc Header
 *  Charles. 2016-9-1
 */
#include <stdlib.h>

#define OS_PAGE 8192

void *os_new(size_t size);
void *os_malloc(size_t size, size_t nmemb = 1);
void os_free(void *&ptr);

#endif
