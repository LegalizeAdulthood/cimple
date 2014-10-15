
/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer
** 
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
** 
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
** 
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
**==============================================================================
*/

#include <sys/stat.h>
#include <cctype>
#include <pthread.h>
#include "log.h"
#include "File_Lock.h"
#include "Buffer.h"
#include "Datetime.h"

#ifdef CIMPLE_WINDOWS
# include <windows.h>
# include <io.h>
# include <direct.h>
#endif

CIMPLE_NAMESPACE_BEGIN

static File_Lock* _lock;
static FILE* _os;
static Log_Level _level;
static int _initialized;
static pthread_mutex_t _mutex = PTHREAD_MUTEX_INITIALIZER;

static const char* _strings[] =
{
    "FATAL",
    "ERR", 
    "WARN",
    "INFO",
    "DBG",
};

static const size_t _num_strings = sizeof(_strings) / sizeof(_strings[0]);

static char* _get_opt_value(const char* path, const char* opt)
{
    size_t opt_len = strlen(opt);

    // Open file.

    FILE* is = fopen(path, "r");

    if (!is)
        return 0;

    // Scan file looking for option.

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), is) != 0)
    {
        if (buffer[0] == '#')
            continue;

        // Trim traling whitespace.

        char* p = buffer;

        while (*p)
            p++;

        while (p != buffer && isspace(p[-1]))
            *--p = '\0';

        // Skip blank lines.

        if (buffer[0] == '\0')
            continue;

        // Check for "TRACE_LEVEL=" flag.

        if (strncmp(buffer, opt, opt_len) == 0)
        {
            const char* p = buffer + opt_len;

            while (isspace(*p))
                p++;

            if (*p == '=')
            {
                p++;

                while (isspace(*p))
                    p++;

                fclose(is);
                return strdup(p);
            }
        }
    }

    fclose(is);

    return 0;
}

static Log_Level _get_log_level(const char* path)
{
    char* value = _get_opt_value(path, "LOG_LEVEL");
    
    if (!value)
        return LL_INFO;

    for (size_t i = 0; i < _num_strings; i++)
    {
        if (strcasecmp(_strings[i], value) == 0)
            return Log_Level(i);
    }

    return LL_INFO;
}

static void _initialize()
{
    // Get home path:

    const char* home = getenv("HOME");

    if (!home)
        return;

    // Read LOG_LEVEL from .cimplerc configuration file.

    char config_file_path[1024];
    {
        strlcpy(config_file_path, home, sizeof(config_file_path));
        strlcat(config_file_path, "/.cimplerc", sizeof(config_file_path));
        _level = _get_log_level(config_file_path);
    }

    // Create $HOME/.cimple directory.

    char cimple_dir_path[1024];
    {
        strlcpy(cimple_dir_path, home, sizeof(cimple_dir_path));
        strlcat(cimple_dir_path, "/.cimple", sizeof(cimple_dir_path));
#ifdef CIMPLE_WINDOWS
        _mkdir(cimple_dir_path);
#else
        mkdir(cimple_dir_path, 0777);
#endif
    }

    // Form path to log file:

    char log_file_path[1024];
    {
        strlcpy(log_file_path, cimple_dir_path, sizeof(log_file_path));
        strlcat(log_file_path, "/messages", sizeof(log_file_path));
    }

    // Form path to lock file:

    char lock_file_path[1024];
    {
        strlcpy(lock_file_path, cimple_dir_path, sizeof(log_file_path));
        strlcat(lock_file_path, "/messages.lock", sizeof(lock_file_path));
    }

    // Create file lock object.

    _lock = new File_Lock(lock_file_path);

    if (!_lock->okay())
    {
        delete _lock;
        _lock = 0;
        return;
    }

    // Open log file for append.

    _os = fopen(log_file_path, "a");

    if (!_os)
    {
        delete _lock;
        _lock = 0;
        return;
    }
}

void vlog(
    Log_Level level, 
    const char* file, 
    size_t line, 
    const char* fmt,
    va_list ap)
{
    pthread_mutex_lock(&_mutex);

    // Initialize on the first call.

    if (_initialized == 0)
    {
        _initialize();
        _initialized = 1;
    }

    // Bail out if initialize failed.

    if (!_os)
    {
        pthread_mutex_unlock(&_mutex);
        return;
    }

    // Skip if log level is too high.

    if (level > _level)
    {
        pthread_mutex_unlock(&_mutex);
        return;
    }

    // Format time string:

    char datetime[Datetime::BUFFER_SIZE];
    {
        Datetime dt = Datetime::now();
        dt.ascii(datetime, true);
        char* dot = strchr(datetime, '.');

        if (dot)
            *dot = '\0';
    }

    // Format message prefix:

    Buffer buffer;
    buffer.format(
        "%s %s: %s(%d): ", datetime, _strings[int(level)], file, line);

    // Format message body:

    buffer.format(fmt, ap);

    if (buffer[buffer.size()-1] != '\n')
        buffer.append('\n');

    // Write to log file:

    _lock->lock();
    fwrite(buffer.data(), buffer.size(), 1, _os);
    fflush(_os);
    _lock->unlock();

    pthread_mutex_unlock(&_mutex);
}

void log(Log_Level level, const char* file, size_t line, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vlog(level, file, line, fmt, ap);
    va_end(ap);
}

CIMPLE_NAMESPACE_END
