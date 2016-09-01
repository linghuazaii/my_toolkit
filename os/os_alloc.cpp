#include "os_alloc.h"
#include "os_error.h"
#include <stdio.h>

/*
 * size must be multi of 8 to gain best performance
 */
void *os_new(size_t size) {
    void *buf;
    int res = posix_memalign(&buf, 8, size);
    if (res != 0) {
        perror("posix_memalign()");
        return NULL;
    }

    return buf;
}

void *os_malloc(size_t size, size_t nmemb) {
    void *buf = calloc(nmemb, size);

    if (buf == NULL)
        os_err("calloc return NULL");

    return buf;
}

void os_free(void *&ptr) {
    free(ptr);
    ptr = NULL;
}
