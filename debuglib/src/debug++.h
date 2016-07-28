#pragma once
/*
 * Debug library for C++ projects.
 * 2016-7-27 Charles 
 * temparary email: lsh@kloudpeak.com
 */

class DebugTool {
public:
    DebugTool(string config_file);
    ~DebugTool();
    void printDebugInfo(string extra_info);
    void reloadCofing();

private:
    void loadConfig();
    bool isTagOn(string tag);
    
private:
    string _config_file;
    string _log_file;
    set<string> _debug_tags;
    bool _debug_switch;
    bool _threadsafe;
    int _signal;
    FILE *_file;
    dictionary *_dict;
    pthread_mutex_t _mutex;
};
