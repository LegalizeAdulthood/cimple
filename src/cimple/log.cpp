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
#include "config.h"
#include "options.h"

#ifdef CIMPLE_WINDOWS
# include <windows.h>
# include <io.h>
# include <direct.h>
#endif

#define DEFAULT_CONFIG_FILE_NAME ".cimple"

CIMPLE_NAMESPACE_BEGIN

static String cimple_home_envvar = CIMPLEHOME_ENVVAR ;

boolean _log_enabled_state = true;

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

        // Trim trailing whitespace.

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

// validate the text provided against the possible log level
// string definitions.  Return 0 if valid with the correct enum
// in level or -1 if no match.
// Does a no case match against the level definition strings.
static int _validate_log_level(const char * txt, Log_Level& level)
{
    for (size_t i = 0; i < _num_strings; i++)
    {
        if (strcasecmp(_strings[i], txt) == 0)
        {
            level = Log_Level(i);
            return 0;
        }
    }
    return -1;
}
// get the log level string definition from the
// config file and if it is valid return 0.  If it is invalid
// return -1
static int _get_log_level(const char* path, Log_Level& level)
{
    char* value = _get_opt_value(path, "LOG_LEVEL");
    
    if (!value)
        return -1;

    int rtn = _validate_log_level(value, level);

    free(value);
    return rtn;
}

// Initialize the log files using status from the config file if
// it exists. The name of the config file is defined by the
// name variable on input.
static void _initialize(const char* name)
{
    // Get home path for CIMPLE_HOME.
    // Defined originally in options as define and 
    // as String in this file.

    const char* home = getenv(cimple_home_envvar.c_str());

    if (!home)
        return;

    // Read LOG_LEVEL from .<name>rc configuration file.

    char conf_path[1024];
    {
        sprintf(conf_path, "%s/%src", home, name);

        if (_get_log_level(conf_path, _level) != 0)
            return;
    }

    // Create $HOME/.cimple directory.

    char root_path[1024];
    {
        sprintf(root_path, "%s/%s", home, name);
#ifdef CIMPLE_WINDOWS
        _mkdir(root_path);
#else
        mkdir(root_path, 0777);
#endif
    }

    // Form path to log file:

    char log_file_path[1024];
    {
        strlcpy(log_file_path, root_path, sizeof(log_file_path));
        strlcat(log_file_path, "/messages", sizeof(log_file_path));
    }

    // Form path to lock file:

    char lock_file_path[1024];
    {
        strlcpy(lock_file_path, root_path, sizeof(log_file_path));
        strlcat(lock_file_path, "/messages.lock", sizeof(lock_file_path));
    }

    // Create file lock object.

    _lock = new File_Lock(lock_file_path);

    // Fail if cannot create lock file.  This is the out if everything
    // fails.
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

void open_log(const char* name)
{
    // Initialize on the first call.

    if (_initialized == 0)
    {
        _initialize(name);
        _initialized = 1;
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
        _initialize(DEFAULT_CONFIG_FILE_NAME);
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
    buffer.format("%s %s: %s(%d): ", datetime, _strings[int(level)], 
        file, (uint32)line);

    // Format message body:

    buffer.vformat(fmt, ap);

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

int log_enable(boolean x)
{
    // if same state
    if (_log_enabled_state == x)
        return -1;

    // else set new state
    _log_enabled_state = x;
    return 0;
}

// sets the log level based on the input string provided.
// returns 0 if successful or -1 if the string is invalid.
int log_set_level(String level)
{
    // try to set the new state and return result
    return(_validate_log_level(level.c_str(), _level));
}

CIMPLE_NAMESPACE_END
