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
#include <vector>
#include <pthread.h>





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
        virtual ~Logger();


        bool        enabled;        // default: true
        bool        short_prefix;   // default: true
        const char *time_fmt;       // default: "%F %T: " see man 3 strftime
        LogLevel    level;          // default: ll_error


        int  open(const std::string &log_name);
        void close();

        bool is_open() { return  _log.is_open(); }


        uint32_t set_max_size(uint32_t max_size);
        uint32_t get_max_size() { return _max_size; }

        uint8_t set_max_index(uint8_t max_index);
        uint8_t get_max_index() { return _max_index; }


        template <typename T>
        friend Logger& operator<<(Logger &os, const T &data)
        {
            if( (!os.enabled) || (os._current_log_level > os.level) )
                return os;

            // write to log
            os._log << data;

            return os;
        }


        // for process iomanipulators (std::endl etc...)
        typedef std::ostream& (*ostream_manipulator)(std::ostream&);
        friend Logger& operator<<(Logger &os, ostream_manipulator pf)
        {
            if(!os.enabled)
                return os;

            return operator<< <ostream_manipulator> (os, pf);
        }


        // Set current log_level (for next messages)
        friend Logger& operator<<(Logger &os, const LogLevel level)
        {
            if(!os.enabled)
                return os;


            os._current_log_level = level;


            if( os._current_log_level > os.level )
                return os;


            os._check_size_log();
            os._print_prefix();

            return os;
        }



    private:

        enum{

            WIDTH_FOR_LAST_POS = 8,
            FIRST_POS_FOR_LOG  = 9  //WIDTH_FOR_LAST_POS +1('\n')
        };


        struct LogLevelPrefix{
            const char *short_prefix;
            const char *long_prefix;
        };


        std::fstream    _log;
        std::string     _log_name;
        LogLevel        _current_log_level;
        uint8_t         _max_index;
        uint8_t         _current_index;
        uint32_t        _max_size;


        std::vector<LogLevelPrefix> _log_level_prefix;


        void     _save_last_pos();
        uint32_t _get_last_pos();
        void     _prepare_first_log();
        int      _get_next_index();
        void     _print_prefix();
        void     _print_time();
        void     _check_size_log();

        int  _open_ring_log(uint32_t last_pos);
        int  _open_index_log(uint32_t index_log);
};





class Logger_r : public Logger
{

    public:

        enum LogMutexAction{

            lm_lock  = 0,
            lm_unlock,
        };


        explicit Logger_r(const std::string log_name = "", LogLevel log_level = ll_error,
                        uint8_t max_index = 1, uint32_t max_size = MIN_SIZE_LOG);
        ~Logger_r();


        // manipulation to inner mutex
        friend Logger_r& operator<<(Logger_r &os, const LogMutexAction action)
        {
            if( action == LogMutexAction::lm_lock )
                pthread_mutex_lock(&os._log_mutex);
            else
                pthread_mutex_unlock(&os._log_mutex);

            return os;
        }



    private:

        pthread_mutex_t _log_mutex;
};





#endif // LOGGER_H
