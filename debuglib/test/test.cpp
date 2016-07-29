/* This file is auto-generated.Edit it at your own peril.*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "debug++.h"
using namespace std;

DEBUG_START("./conf/debug.ini");

int main() {
    DEBUG_REGIST_SIGNAL();

    int n = 1;
    while (n <= 100) {
        DEBUG("Hi there! [%d]", n);
        TDEBUG("ssl", "I am ssl tag [%d]", n);
        TDEBUG("cdn", "I am cnd tag [%d]", n);
        TDEBUG("sdn", "I am sdn tag [%d]", n);
        ++n;
    }

    return 0;
}

