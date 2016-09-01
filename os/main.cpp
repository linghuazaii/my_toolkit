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
    cout<<os_open_r("log", true)<<endl;
    cout<<os_open_w("log")<<endl;
    cout<<os_open_rw("log")<<endl;
    cout<<os_open_a("log")<<endl;

    return 0;
}

