/*
 * logger.cpp
 *
 *
 * Copyright (c) 2015, Koynov Stas - skojnov@yandex.ru
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1 Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  2 Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  3 Neither the name of the <organization> nor the
 *    names of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <iostream>

#include "logger.h"





Logger::Logger(const std::string log_name, Logger::LogLevel log_level, uint8_t max_index, uint32_t max_size):
    //public
    enabled(true),
    level(log_level),

    //private
    _log_name(log_name),
    _current_log_level(ll_info)
{

    set_max_index(max_index);
    set_max_size(max_size);
    open(log_name);
}



Logger::~Logger()
{
    close();
}



int Logger::open(const std::string &log_name)
{
    if(log_name.empty())
        return -1; //error


    _log_name = log_name;


    if( _max_index == 1)
        return _open_ring_log(_get_last_pos());
    else
        return _open_index_log(_get_last_pos());
}



void Logger::close()
{
    if( !_log.is_open() )
        return;

    _log.close();
}



uint32_t Logger::set_max_size(uint32_t max_size)
{
    if( max_size < MIN_SIZE_LOG )
        max_size = MIN_SIZE_LOG;

    _max_size = max_size;

    return _max_size;
}



uint8_t Logger::set_max_index(uint8_t max_index)
{
    if( max_index == 0 )
        max_index = 1;

    _max_index = max_index;

    return _max_index;
}



uint32_t Logger::_get_last_pos()
{
    uint32_t ret;
    std::ifstream temp_stream(_log_name, std::fstream::in);


    if( !temp_stream.is_open() )
        return 0;


    temp_stream >> ret;

    return ret;
}



int Logger::_open_ring_log(uint32_t last_pos)
{

}



int Logger::_open_index_log(uint32_t index_log)
{

}
