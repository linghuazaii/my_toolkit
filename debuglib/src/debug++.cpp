#include "debug++.h"

DebugTool::DebugTool(string config_file) {
    _config_file = config_file;
    _mutex = PTHREAD_MUTEX_INITIALIZER;
    _debug_swith = false;
    _file = NULL;
    _dict = NULL;
    _threadsafe = true;
}

DebugTool::~DebugTool() {
    pthread_mutex_destroy(&_mutex);
    if (_file)
        fclose(_file);
}

void DebugTool::loadConfig() {
    _dict = iniparser_load(_config_file.c_str());
    _debug_switch = iniparser_getboolean(_dict, "debug:debug_on", 0);
    _threadsafe = iniparser_getboolean(_dict, "debug:debug_threadsafe", 1);

    /*
     * Some compiler does not support c++11 regex now.Eg, Gcc version below
     * 4.9, my Gcc version is now 4.8.5, and develop server Gcc version is 4.8.3
     * .So I just use sscanf to do a simple regex for tags.The true reason is
     * that I downloaded the latest stable version of Gcc,but the compiling is
     * soooooooooooo slowwwwwwwwwwwwww,so I give up!
     *
     * NOTE: if you want to use c++11 regex,please use Gcc version after 4.9
     */
    string tags = iniparser_getstring(_dict, "debug:debug_tags", "");
    const char *p_tags = tags.c_str();
    int count = 0, pos = count;
    char buf[1024] = {0};
    while (1) {
        char temp;
        //consume all of the `spaces , : |` before each tag, `, : |` are treated
        //as delimiters.
        while (!sscanf(p_tags + pos, "%[^ ,|:]%*c", &ch))
            pos += 1;

        if (sscanf(p_tags + pos, "%[^,|:]%n", buf, &count)) {
            pos += count;

            _debug_tags.insert(string(buf));

            memset(buf, 0, 1024);
            if (pos > tags.length())
                break;
        }
    }

    int _signal = iniparser_getint(_dict, "debug:debug_signal", 10);
    
    _log_file = iniparser_getstring(_dict, "debug:debug_logfile", "./debug.log");
    _file = fopen(_log_file.c_str(), "a+");
    if (_file == NULL) {
        cerr<<"[libdebug++.so] open log file failed for ( "<<_log_file<<" )"<<endl;
    }
}

bool DebugTool::isTagOn(string tag) {
    if (_debug_tags.find(tag) != _debug_tags.end())
        return true;
    return false;
}
