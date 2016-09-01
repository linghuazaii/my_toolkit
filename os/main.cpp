/* This file is auto-generated.Edit it at your own peril.*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <termios.h>
#include <inttypes.h>
#include <errno.h>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "os_file.h"
#include "os_error.h"
#include "os_alloc.h"
#include "os_io.h"
using namespace std;

int main(int argc, char **argv) {
    int fd = os_open_r("log");
    void *buf;
    int n;
    while ((n = os_read(fd, buf, OS_PAGE))) {
        cout<<(char *)buf;
    }

    return 0;
}

