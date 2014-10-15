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

#include "config.h"
#include "Adapter_Tracer.h"
#include "log.h"

CIMPLE_NAMESPACE_BEGIN

void AdapterTracer::pEntry(
    const char* name,
    const char* file,
    size_t line)
{
    if(_log_enabled_state)
    {
        log(LL_DBG, file, line, "Enter: %s()", name);
    }
}

void AdapterTracer::pExit(const char* name,
           const char* file,
           size_t line)
{
    if(_log_enabled_state)
    {
        log(LL_DBG, file, line, "Exit: %s", name);
    }
}

void AdapterTracer::pExit(const char* name,
           const char* file,
           size_t line,
           bool value)
{
    if(_log_enabled_state)
    {
        log(LL_DBG, file, line, "Exit: %s %s", name, value? "true": "false");
    }
}

void AdapterTracer::pExit(const char* name,
           const char* file,
           size_t line,
           int value)
{
    if(_log_enabled_state)
    {
        log(LL_DBG, file, line, "Exit: %s %d", name, value);
    }
}
void AdapterTracer::pExit(const char* name,
           const char* file,
           size_t line,
           uint32 value)
{
    if(_log_enabled_state)
    {
        log(LL_DBG, file, line, "Exit: %s %u", name, value);
    }
}

CIMPLE_NAMESPACE_END
