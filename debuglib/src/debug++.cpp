#include "debug++.h"
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>
#include <errno.h>
using std::cerr;
using std::endl;

DebugTool::DebugTool(string config_file) {
    _config_file = config_file;
    pthread_mutex_init(&_mutex, NULL);
    debug_switch = false;
    _file = NULL;
    _dict = NULL;
    _threadsafe = true;
    _last_savetime = time(NULL);
    _timeout = 1;
    
    started = false;

    loadConfig();
}

DebugTool::~DebugTool() {
    pthread_mutex_destroy(&_mutex);
    if (_file)
        fclose(_file);
    if (_dict)
        iniparser_freedict(_dict);
}

void DebugTool::loadConfig() {
    _dict = iniparser_load(_config_file.c_str());
    if (_dict == NULL) {
        cerr<<"[libdebug++.so] error happened when loading config file"<<endl;
        started = false;
        return;
    }
    debug_switch = iniparser_getboolean(_dict, "debug:debug_on", 0);
    _threadsafe = iniparser_getboolean(_dict, "debug:debug_threadsafe", 1);

    /*
     * Some compiler does not support c++11 regex now.Eg, Gcc version below
     * 4.9, my Gcc version is now 4.8.5, and develop server Gcc version is 4.8.3
     * .So I just use sscanf to do a simple regex for tags.The true reason is
     * that I downloaded the latest stable version of Gcc,but the compiling is
     * soooooooooooo slowwwwwwwwwwwwww,so I give up!DebugTool g_debugtool(config_file); \
     *
     * NOTE: if you want to use c++11 regex,please use Gcc version after 4.9
     */
    string tags = iniparser_getstring(_dict, "debug:debug_tags", "");
    const char *p_tags = tags.c_str();
    int count = 0, pos = count;
    char buf[1024] = {0};
    while (pos < tags.length()) {
        char temp;
        //consume all of the `spaces , : |` before each tag, `, : |` are treated
        //as delimiters.
        while (!sscanf(p_tags + pos, "%[^ ,|:]%*c", &temp)) {
            pos += 1;
            continue;
        }

        if (sscanf(p_tags + pos, "%[^,|:]%n", buf, &count) && count) {
            pos += count;
            
            //if we read a valid tag, insert into tags
            if (buf[0])
                _debug_tags.insert(string(buf));

            memset(buf, 0, 1024);
        }
    }
   
    debug_signal = iniparser_getint(_dict, "debug:debug_signal", 10);
    
    _log_file = iniparser_getstring(_dict, "debug:debug_logfile", "./debug.log");
    _file = fopen(_log_file.c_str(), "a+");
    if (_file == NULL) {
        cerr<<"[libdebug++.so] open log file failed for ( "<<_log_file<<" ): "<<strerror(errno)<<endl;
        started = false;
        return;
    }

    _save_dir = iniparser_getstring(_dict, "debug:debug_log_savedir", "./");
    if (_save_dir[_save_dir.length() - 1] != '/')
        _save_dir += "/";

    string timeout = iniparser_getstring(_dict, "debug:debug_timeout", "0");
    const char *p_timeout = timeout.c_str();
    count = 0; pos = count;
    memset(buf, 0, 1024);
    while (pos < timeout.length()) {
        char temp;
        while (!sscanf(p_timeout + pos, "%[^ xX*]%*c", &temp)) {
            pos += 1;
            continue;
        }

        if (sscanf(p_timeout + pos, "%[^xX*]%n", buf, &count) && count) {
            pos += count;

            if (buf[0])
                _timeout *= strtol(buf, NULL, 10);

            memset(buf, 0, 1024);
        }
    }

    started = true;
}

bool DebugTool::isTagOn(string tag) {
    if (_debug_tags.find("ALL") != _debug_tags.end() ||
            _debug_tags.find("All") != _debug_tags.end() ||
            _debug_tags.find("all") != _debug_tags.end() ||
            _debug_tags.find(tag) != _debug_tags.end())
        return true;
    return false;
}

void DebugTool::reloadConfig() {
    if (_file)
        fclose(_file);

    if (_dict)
        iniparser_freedict(_dict);

    _last_savetime = time(NULL);
    _timeout = 1;
    _debug_tags.clear();

    pthread_mutex_lock(&_mutex);
    loadConfig();
    pthread_mutex_unlock(&_mutex);
}

void DebugTool::printDebugInfo(string extra_info) {
    time_t now = time(NULL);

    if (_threadsafe)
        pthread_mutex_lock(&_mutex);

    if (_timeout != 0 && now - _last_savetime >= _timeout) {
        char buf[128] = {0};
        struct tm *tm_now = localtime(&now);
        strftime(buf, 128, "%Y_%m_%d_%H_%M_%S.log", tm_now);
        string filename = _save_dir + string(buf);
        string command = "cp " + _log_file + " " + filename;
        system(command.c_str());
        ftruncate(fileno(_file), 0);
        _last_savetime = now;
    }

    fprintf(_file, "%s", extra_info.c_str());
    fflush(_file);

    if (_threadsafe)
        pthread_mutex_unlock(&_mutex);
}
