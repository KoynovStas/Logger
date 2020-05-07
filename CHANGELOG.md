# Change Log


[**Logger**](https://github.com/KoynovStas/Logger) - is a simple class to logging on log file(s).

License: BSD 3-Clause

Copyright (c) 2015, Koynov Stas - skojnov@yandex.ru


---
## [v1.1](https://github.com/KoynovStas/Logger/tree/v1.1) (2020-05-07)
[Full Changelog](https://github.com/KoynovStas/Logger/compare/v1.0...v1.1)

> This is the last version that can be easily used for C++03(we dont use std::thread, nullptr, auto and etc). To do this, change method `_open_index_log`, in the line: `log_name += std::to_string(_current_index);`


### Added
- add `LogLocker` class - RAII for lock/unlock inner mutex
-  add `LogFlagSaver` class RAII for save/restore flags fstream
- add build for Windows(mingw)


### Refactoring
 - use static array for prefix see `print_prefix` method


### BugFix
 - Fix `iomanip` for mingw


### Tests
 - add dir `tests` for src of tests



## [v1.0](https://github.com/KoynovStas/Logger/tree/v1.0) (2016-03-02)
