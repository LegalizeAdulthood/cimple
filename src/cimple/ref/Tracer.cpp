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
#include <sys/types.h>
#include <cstdarg>
#include <cctype>
#include "Tracer.h"
#include "Strings.h"
#include "Datetime.h"

#ifdef CIMPLE_WINDOWS
# include <windows.h>
# include <io.h>
# include <direct.h>
#endif

CIMPLE_NAMESPACE_BEGIN

static const char* _level_to_str(Trace_Level level)
{
    switch (level)
    {
        case TRC_FATAL:
            return "FATAL";
        case TRC_SEVERE:
            return "SEVERE";
        case TRC_ERROR:
            return "ERROR";
        case TRC_WARN:
            return "WARN";
        case TRC_INFO:
            return "INFO";
        case TRC_DEBUG:
            return "DEBUG";
    }

    return 0;
}

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

Tracer::Tracer(Trace_Level level, const char* prefix)
{
    _os = NULL;
    _level = level;

    // Locate .cimplerc configuration file.

    const char* home = getenv("HOME");

    if (!home)
        return;

    // Read TRACE_LEVEL option from .cimplerc file (if any).

    char buffer[1024];
    strlcpy(buffer, home, sizeof(buffer));
    strlcat(buffer, "/.cimplerc", sizeof(buffer));

    {
        char* value = _get_opt_value(buffer, "TRACE_LEVEL");

        if (value)
        {
            if (strcmp(value, "FATAL") == 0)
                _level = TRC_FATAL;
            else if (strcmp(value, "SEVERE") == 0)
                _level = TRC_SEVERE;
            else if (strcmp(value, "ERROR") == 0)
                _level = TRC_ERROR;
            else if (strcmp(value, "WARN") == 0)
                _level = TRC_WARN;
            else if (strcmp(value, "INFO") == 0)
                _level = TRC_INFO;
            else if (strcmp(value, "DEBUG") == 0)
                _level = TRC_DEBUG;

            free(value);
        }
    }

#if 0
    // Get ENABLE_TRACING option value.
    {
        char* value = _get_opt_value(buffer, "ENABLE_TRACING");
        bool enable = false;

        if (value && strcmp(value, "TRUE") == 0)
            enable = true;

        if (!enable)
            return;
    }
#endif

    // Create $HOME/.cimple directory if necessary.

    strlcpy(buffer, home, sizeof(buffer));
    strlcat(buffer, "/.cimple", sizeof(buffer));

#ifdef CIMPLE_WINDOWS
    _mkdir(buffer);
#else
    mkdir(buffer, 0777);
#endif

    // Attempt to open log file.

    strlcat(buffer, "/", sizeof(buffer));
    strlcat(buffer, prefix, sizeof(buffer));
    strlcat(buffer, ".log", sizeof(buffer));

    if ((_os = fopen(buffer, "a")) == NULL)
        fprintf(stderr, "Tracer: failed to open log file: %s\n", buffer);
}

Tracer::~Tracer()
{
    if (_os)
        fclose(_os);
}

void Tracer::trace(Trace_Level level, const char* format, ...)
{
    if (_os && level <= _level)
    {
        Datetime dt = Datetime::now();
        char buffer[Datetime::BUFFER_SIZE];
        dt.ascii(buffer, true);

        char* dot = strchr(buffer, '.');

        if (dot)
            *dot = '\0';

        fprintf(_os, "%s %s ", buffer, _level_to_str(level));
        va_list ap;
        va_start(ap, format);
        vfprintf(_os, format, ap);
        va_end(ap);
        fputc('\n', _os);
        fflush(_os);
    }
}

CIMPLE_NAMESPACE_END
