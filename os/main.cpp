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
using namespace std;

int main(int argc, char **argv) {
    int fd = os_open_w("log", true);
    const char *name = "I am Charles";
    const char *nothing = "to overwrite";

    write(fd, name, strlen(name));
    os_close(fd);
    fd = os_open_a("log");
    write(fd, nothing, strlen(nothing));
    os_close(fd);

    return 0;
}

