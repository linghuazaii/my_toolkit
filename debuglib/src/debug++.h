#pragma once
/*
 * Debug library for C++ projects.
 * 2016-7-27 Charles 
 * temparary email: lsh@kloudpeak.com
 */
#include <iostream>
#include <set>
#include <pthread.h>
#include <stdio.h>
#include <string>
#include <signal.h>
#include "iniparser.h"
using std::string;
using std::set;

#define DEBUG_START(config_file) \
    void debugtool_reload_config(int) { \
        extern DebugTool g_debugtool; \
        g_debugtool.reloadConfig(); \
    } \
    DebugTool g_debugtool(config_file); \

#define DEBUG_REGIST_SIGNAL() \
    do { \
        signal(g_debugtool.debug_signal, debugtool_reload_config); \
    } while (0)

/*
 * Debug without tag
 */
#define DEBUG(fmt, ...) \
    do { \
        if (g_debugtool.started && g_debugtool.debug_switch) { \
            char buf[1024] = {0}; \
            char timebuf[128] = {0}; \
            time_t now = time(0); \
            struct tm *tm_now = localtime(&now); \
            strftime(timebuf, 128, "[ %Y-%m-%d %H:%M:%S ]", tm_now); \
            snprintf(buf, 1024, "%s [%s:%d] [%s] " fmt "\n", timebuf, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
            g_debugtool.printDebugInfo(buf); \
        } \
    } while (0)

/*
 * Debug with tag
 */
#define TDEBUG(tag, fmt, ...) \
    do { \
        if (g_debugtool.isTagOn(tag)) { \
            if (g_debugtool.started && g_debugtool.debug_switch) { \
                char buf[1024] = {0}; \
                char timebuf[128] = {0}; \
                time_t now = time(0); \
                struct tm *tm_now = localtime(&now); \
                strftime(timebuf, 128, "[ %Y-%m-%d %H:%M:%S ]", tm_now); \
                snprintf(buf, 1024, "%s [%s:%d] [%s] [%s] " fmt "\n", timebuf, __FILE__, __LINE__, __FUNCTION__, tag, ##__VA_ARGS__); \
                g_debugtool.printDebugInfo(buf); \
            } \
        } \
    } while (0)


class DebugTool {
public:
    DebugTool(string config_file);
    ~DebugTool();
    void printDebugInfo(string extra_info);
    void reloadConfig();
    bool isTagOn(string tag);

private:
    void loadConfig();
    
private:
    string _config_file;
    string _log_file;
    set<string> _debug_tags;
    bool _threadsafe;
    FILE *_file;
    string _save_dir;
    long int _timeout;
    long int _last_savetime;
    dictionary *_dict;
    pthread_mutex_t _mutex;

public:
    bool debug_switch;
    bool started;
    int debug_signal;
};
