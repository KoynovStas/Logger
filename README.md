# Logger is C++ class for logging on file(s)


## Description (**[Logger](./logger.h)**)

**Logger** is a simple class to logging on log file(s).


**Mode:**
* (cycle) - a single file  // max_index == 1 - **default mode**
* (index) - a lot of files // max_index > 1  - specifies the maximum file index.

The logger will overwrite from the beginning of the file (cycle mode) or write to the next file (index mode) if overflow file size (see method set_max_size)


**The class has the following public methods:**
```C++
explicit Logger(const std::string log_name = "", LogLevel log_level = ll_error,
                uint32_t max_size = MIN_SIZE_LOG, uint8_t max_index = 1);

virtual ~Logger();

int  open(const std::string &log_name);
void close();

bool is_open() { return  _log.is_open(); }

uint32_t set_max_size(uint32_t max_size);
uint32_t get_max_size() { return _max_size; }

uint8_t set_max_index(uint8_t max_index);
uint8_t get_max_index() { return _max_index; }
```


**The class has the following public fields:**
```C++
bool        enabled;        // default: true
bool        long_prefix;    // default: false
const char *time_fmt;       // default: "%F %T: " see man 3 strftime
LogLevel    level;          // default: ll_error
```

for time_fmt see **[man 3 strftime](http://man7.org/linux/man-pages/man3/strftime.3.html)**

**The class has the following public constants and enums:**
```C++
static const uint32_t MIN_SIZE_LOG = 1024;  // 1 KiB


enum LogLevel{

    ll_fatal = 0, // Unrecoverable error.
    ll_crit,      // Critical error
    ll_error,     // Error
    ll_warn,      // Potentially harmful situation.
    ll_info,      // Normal operational messages that require no action
    ll_debug,     // Fine-grained debugging.
    ll_trace,     // Verbose debugging.
};
```

## Description (**[Logger_r](./logger.h)**)

**Logger_r** is a Logger + mutex(pthread) for multithreading apps. _r (reenterable)

**The class has the following public enum:**
```C++
enum LogMutexAction{

    lm_lock  = 0,
    lm_unlock,
};
```


For Thread-safety coding and protection of Log file, you should use the following method:
```C++
rlog << Logger_r::lm_lock;   //lock inner mutex

rlog << Logger_r::ll_error << "messages" << std::endl;

rlog << Logger_r::lm_unlock; //unlock inner mutex
```

Or use LogLocker:
```C++
{
    LogLocker lock(rlog);
    rlog << Logger_r::ll_error << "messages" << std::endl;
}
```



For Thread-safety coding and protection of object, you should use the following method:
```C++
rlog << Logger_r::lm_lock;   //lock inner mutex

rlog.enable       = true;
rlog.short_prefix = false;
rlog.time_fmt     = "%T ";

rlog << Logger_r::lm_unlock; //unlock inner mutex
```


More details see: **[logger.h](./logger.h)**



## Usage
**To start working, perform the following steps:**

1. You need to include **[logger.h](./logger.h)** file in your **.cpp** file.
2. And add file **[logger.cpp](./logger.cpp)** to list of source files to compile. (see an example)

#### Note:
> The compiler must support the C++11 standard. (`std::to_string`)




## Examples

1. **[logger_test](./test/logger_test.cpp)** - how to work with the class **[Logger](./logger.h)**
2.  **[logger_r_test](./test/logger_r_test.cpp)** - how to work with the class **[Logger_r](./logger.h)**



## Build tests

```console
make
```


## License

[BSD-3-Clause](./LICENSE).



## Copyright
Copyright (C) 2015 Koynov Stas - skojnov@yandex.ru
