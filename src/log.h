/*************************************************************************
    > File Name: log.h
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2016-01-08 10:20:53
 ************************************************************************/

#ifndef __XML_LOG_H__
#define __XML_LOG_H__

#include <stdio.h>
#include <stdarg.h>

typedef enum _eLogLevel {
    LOG_EMER    = 0,
    LOG_ALERT,
    LOG_CRIT,
    LOG_ERR,
    LOG_WARN,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG,
} eLogLevel;

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_DEBUG
#else
#if LOG_LEVEL > 7
#define LOG_LEVEL LOG_DEBUG
#endif
#endif

static void log_error(unsigned int level, const char * fmt, ...) 
{
    va_list args;
    
    if (level <= LOG_LEVEL) {
        va_start(args, fmt);
        char buf[1024];
        vsnprintf(buf, 1024, fmt, args);
        va_end(args);
        printf("%s\n", buf);
    }
}

#endif

