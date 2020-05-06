#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>

#include "logger.h"





void test_log(Logger& log)
{
    log.level = Logger::ll_trace;
//    log.long_prefix = true;
//    log.time_fmt = "%T";

    log << "Hello ";
    log << 1;
    log << std::setw(8) << '#';
    log << 2.56;
    log << std::endl;

    log << 1 << 2 << 3 << 4 << std::endl;
    log << 1.10 << 2.22 << 3.123456789 << -4.00001 << std::endl;

    log << Logger::ll_info  << "--------- rick and morty is cool ---------\n";
    log << Logger::ll_error << "<1234567890>\n";
    log << Logger::ll_error << "<~!@#$%^&*()_+|>\n";
    log << Logger::ll_error << "qwertyuiop[]\n";
    log << Logger::ll_error << "asdfghjkl;'\n";
    log << Logger::ll_error << "zxcvbnm,./\n";

    log << Logger::ll_trace << "Trace"    << std::endl;
    log << Logger::ll_debug << "Debug"    << std::endl;
    log << Logger::ll_info  << "Info"     << std::endl;
    log << Logger::ll_warn  << "Warning"  << std::endl;
    log << Logger::ll_error << "Error"    << std::endl;
    log << Logger::ll_crit  << "Critical" << std::endl;
    log << Logger::ll_fatal << "Fatal"    << std::endl;
}



void ring_log_test()
{
    Logger my_log;

    my_log.open("ring.log");

    if( !my_log.is_open() )
    {
        std::cout << "Cant open test.log" << std::endl;
        return;
    }

    test_log(my_log);
}



void index_log_test()
{
    Logger my_log;

    my_log.set_max_index(3);
    my_log.open("test.log");

    if( !my_log.is_open() )
    {
        std::cout << "Cant open test.log" << std::endl;
        return;
    }

    test_log(my_log);
}





int main()
{
    ring_log_test();
    index_log_test();

    return EXIT_SUCCESS; // good job
}
