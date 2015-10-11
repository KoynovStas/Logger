/*
 * logger.h
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

#ifndef LOGGER_H
#define LOGGER_H


#include <stdint.h>
#include <fstream>





class Logger
{

    public:

        static const uint32_t MIN_SIZE_LOG = 1024;


        enum LogLevel{

            ll_fatal = 0, // Unrecoverable error.
            ll_crit,      // Critical error
            ll_error,     // Error
            ll_warn,      // Potentially harmful situation.
            ll_info,      // Normal operational messages that require no action
            ll_debug,     // Fine-grained debugging.
            ll_trace,     // Verbose debugging.
        };



        explicit Logger(const std::string log_name = "", LogLevel log_level = ll_error,
                        uint8_t max_index = 1, uint32_t max_size = MIN_SIZE_LOG);
        ~Logger();


        bool        enabled;
        LogLevel    level;


        void close();



    private:


        std::fstream    _log;
        std::string     _log_name;
        LogLevel        _current_log_level;
        uint8_t         _max_index;
        uint8_t         _current_index;
        uint32_t        _max_size;


};


#endif // LOGGER_H
