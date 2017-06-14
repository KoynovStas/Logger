#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>

#include "logger.h"




void ring_log_test()
{
    Logger my_log;

    my_log.open("ring.log");

    my_log.level = Logger::ll_trace;
//    rlog.short_prefix = false;
//    rlog.time_fmt = "%T";

    my_log << "Hello ";
    my_log << 1;
    my_log << std::setw(8) << '#';
    my_log << 2.56;
    my_log << std::endl;


    my_log << 1 << 2 << 3 << 4 << std::endl;
    my_log << 1.10 << 2.22 << 3.123456789 << -4.00001 << std::endl;

    my_log << "--------- rick and morty is cool ---------\n";
    my_log << "--------- Tolik loshara :)))---------\n";
    my_log << "<1234567890>\n";
    my_log << Logger::ll_error << "<1234567890>\n";
    my_log << Logger::ll_error << "<~!@#$%^&*()_+|>\n";
    my_log << Logger::ll_error << "qwertyuiop[]\n";
    my_log << Logger::ll_error << "asdfghjkl;'\n";
    my_log << Logger::ll_error << "zxcvbnm,./\n";


    my_log << Logger::ll_trace << "Trace" << std::endl;
    my_log << Logger::ll_debug << "Debug" << std::endl;
    my_log << Logger::ll_info  << "Info"  << std::endl;
    my_log << Logger::ll_warn  << "Warni" << std::endl;
    my_log << Logger::ll_error << "Error" << std::endl;
    my_log << Logger::ll_crit  << "Criti" << std::endl;
    my_log << Logger::ll_fatal << "Fatal" << std::endl;
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


    my_log.level = Logger::ll_trace;
//    rlog.long_prefix = true;
//    rlog.time_fmt = "%T";

    my_log << "Hello ";
    my_log << 1;
    my_log << std::setw(8) << '#';
    my_log << 2.56;
    my_log << std::endl;


    my_log << 1 << 2 << 3 << 4 << std::endl;
    my_log << 1.10 << 2.22 << 3.123456789 << -4.00001 << std::endl;

    my_log << "--------- rick and morty is cool ---------\n";
    my_log << "--------- Tolik loshara :)))---------\n";
    my_log << "<1234567890>\n";
    my_log << Logger::ll_error << "<1234567890>\n";
    my_log << Logger::ll_error << "<~!@#$%^&*()_+|>\n";
    my_log << Logger::ll_error << "qwertyuiop[]\n";
    my_log << Logger::ll_error << "asdfghjkl;'\n";
    my_log << Logger::ll_error << "zxcvbnm,./\n";



    my_log << Logger::ll_trace << "Trace" << std::endl;
    my_log << Logger::ll_debug << "Debug" << std::endl;
    my_log << Logger::ll_info  << "Info"  << std::endl;
    my_log << Logger::ll_warn  << "Warni" << std::endl;
    my_log << Logger::ll_error << "Error" << std::endl;
    my_log << Logger::ll_crit  << "Criti" << std::endl;
    my_log << Logger::ll_fatal << "Fatal" << std::endl;
}





int main()
{
    ring_log_test();
    index_log_test();

    return EXIT_SUCCESS; // good job
}
