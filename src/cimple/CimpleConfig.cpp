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

#include "CimpleConfig.h"
#include "log.h"
#include "options.h"

CIMPLE_NAMESPACE_BEGIN

CimpleConfig::CimpleConfig()
{
}

CimpleConfig::~CimpleConfig()
{
}
bool CimpleConfig::setLogLevel(String& level)
{
    // try to set the new state and return result
    // TODO modify validate to return bool
    return (log_set_level(level) == 0);
    //return(_validate_log_level(level.c_str(), _level) == 0);
}

bool CimpleConfig::setLogLevel(Log_Level level)
{
    // try to set the new state and return result
    // TODO modify validate to return bool
    return log_set_level(level);
}

Log_Level CimpleConfig::getLogLevel()
{
    return log_get_level();
}

const char * CimpleConfig::getLogLevelString()
{
    return log_get_level_string();
}

// TODO This is unprotected in that it is setting a char* that we
// know nothing about into another char*.
bool CimpleConfig::setHomeEnv(const char* env_var)
{
    set_cimple_home_envvar(env_var);
    return true;
}

const char* CimpleConfig::getHomeEnv()
{
    return get_cimple_home_envvar();
}

uint32 CimpleConfig::getLogFileMaxSize()
{
    return log_get_maxFileSize();
}

bool CimpleConfig::setLogFileMaxSize(uint32 new_size)
{
    log_set_maxlogFileSize(new_size);
    // TODO test limits before setting
    return true;
}

uint32 CimpleConfig::getLogMaxBackupFiles()
{
    return log_get_maxLogBackupFiles();
}

bool CimpleConfig::setLogMaxBackupFiles(uint32 new_size)
{
    return log_set_maxlogBackupFiles(new_size);
}

bool CimpleConfig::setLogEnabledState(bool newState)
{
    _log_enabled_state = newState;
    return true;
}
bool CimpleConfig::getLogEnabledState()
{
    return _log_enabled_state;
}

void CimpleConfig::readConfig()
{
    read_config_file();
}
bool CimpleConfig::removeLogFiles()
{
    return log_remove_all_logfiles();
}

bool CimpleConfig::setEnableLoggingState(bool newState)
{
    return log_enable(newState);
}
bool CimpleConfig::getEnableLoggingState()
{
    return get_log_enable_state();
}

CIMPLE_NAMESPACE_END
