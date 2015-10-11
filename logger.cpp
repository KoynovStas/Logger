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
#include <iomanip>

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



void Logger::_save_last_pos()
{
    uint32_t last_pos;


    _log.flush();

    if( _max_index == 1)
    {
        last_pos = _log.tellp();
    }
    else
    {
        last_pos = _get_next_index();
        _prepare_first_log();

        _log.close();
        _log.open(_log_name, std::fstream::out | std::fstream::in); //open first log
    }


    _log.seekp(0);

    _log << std::setw(WIDTH_FOR_LAST_POS) << last_pos << std::endl;
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



void Logger::_prepare_first_log()
{
    // will create file(_log_name) if file not exist
    std::fstream file(_log_name, std::fstream::out | std::fstream::in | std::fstream::app);


    // get length of file:
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);

    if( length == 0)
        file << std::setw(WIDTH_FOR_LAST_POS) << FIRST_POS_FOR_LOG << std::endl; // do setw for saving last_pos
}



int Logger::_get_next_index()
{
    if( ++_current_index >= _max_index )
        _current_index = 0;

    return _current_index;
}



int Logger::_open_ring_log(uint32_t last_pos)
{

}



int Logger::_open_index_log(uint32_t index_log)
{

}
