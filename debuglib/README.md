#Debug++ Library

###_What does this library use for?_

This library is a simple debug logging system.You can you use it in your project to do logging stuff.
It is simple but powerful, I ensure you that it is easy to use and easy to config.

###_Now let's start our journey._
I use an open-source project [iniparser](https://github.com/ndevilla/iniparser) to do config stuff.Iniparser is easy to use and I 
[pulled request](https://github.com/ndevilla/iniparser/pull/79) to it.  
In Debug++, I use sscanf to make config more flexible,since the version of my GNU-Gcc compiler is lower than 4.9.It doesn't support 
C++11 regex,so I use sscanf("%[^]%*n") to do simple regex.I learn this trick from the iniparser project.You can find it in [debug++.cpp](https://github.com/linghuazaii/my_toolkit/blob/master/debuglib/src/debug++.cpp)

####_usage_
You can learn how to config Debug++ in [debug.ini](https://github.com/linghuazaii/my_toolkit/blob/master/debuglib/conf/debug.ini)  
Also there is an little example in [test.cpp](https://github.com/linghuazaii/my_toolkit/blob/master/debuglib/test/test.cpp) 

Use  `git clone https://github.com/linghuazaii/my_toolkit.git` to clone Debug++.  
Then `cd my_toolkit/debuglib`.  
Then `make`.  
Then `make test`. And test log will be wrote into `log/debug.log`

###There is a simple guide
```  
//use DEBUG_START(debug_config_file) to start the logging system.This macro must place before the main function ,such as 
DEBUG_START("../log/debug.log");  
  
int main() {  
    //use this macro if your program needs to run continuely,such as a server progress.
    //and then you can use kill -signum (your program pid) to reload the config.
    //Use this macro if needed.And use it at your own peril.
    DEBUG_REGIST_SIGNAL();
    
    //use DEBUG() and TDEBUG() to log debug info,such as
    DEBUG("This is a debug info");
    DEBUG("This is another debug info %s", "xixi");
    
    TDEBUG("ssl", "This is a debug info which will be write only if tag 'ssl' is set");
    TDEBUG("ssl", "same as the later one,but I can use %d", 2016);
}
```

####Please see [debug.ini](https://github.com/linghuazaii/my_toolkit/blob/master/debuglib/conf/debug.ini) to learn how to config Debug++

####Any questions,please feel free to contact me: lsh@kloudpeak.com
