#include "debug++.h"

DebugTool::DebugTool(string config_file) {
    _config_file = config_file;
    _mutex = PTHREAD_MUTEX_INITIALIZER;
    _debug_swith = false;
    _file = NULL;
    _threadsafe = true;
}

DebugTool::~DebugTool() {
    pthread_mutex_destroy(&_mutex);
    if (_file)
        fclose(_file);
}



