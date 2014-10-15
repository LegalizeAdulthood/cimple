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

/*
    A class that provides for dynamic configuration of the CIMPLE environment
*/

#ifndef _cimple_configuration_h
#define _cimple_configuration_h

#include "config.h"
#include "log.h"

CIMPLE_NAMESPACE_BEGIN

/**
   Public Class that controls configuration of a CIMPLE Environment. 
   Today this is exclusively logging and tracing but expect this class to 
   expand to other parameters that may be set to manage the configuration. 
   ****EXPERIMENTAL**** This class is experimental in the current version 
 */
class CIMPLE_CIMPLE_LINKAGE CimpleConfig
{
public:
    /**
       Set the log level to the level defined by the input level 
       @param level String parameter that defines log level. Must be one 
       of the predefined constants 
       @return true if set correctly Else false 
     */
    static bool setLogLevel(String& level);

    /**
       set the log level to the level defined by the enum variable input
       @param level - Level to set
       @return bool true if operation executed.
     */
    static bool setLogLevel(Log_Level level);

    /**
       Get the current log level
       @return Log_Level 
     */
    static Log_Level getLogLevel();

    /**
       Get the String that defines the current log level (i.e. DBG, WARN, etc.) 
       @return String that defines the current log level 
    */

    static const char * getLogLevelString();

    /**
       Set the HOME environment variable that defines the location of the 
       various files used by CIMPLE.
       @param env_var 
       @return bool true if accepted
     */
    static bool setHomeEnv(const char* env_var);

    /**
     * Get the HOME current value of the HOME environment variable 
     * that defines location of various files used by CIMPLE 
     */
    static const char* getHomeEnv();

    /**
       Set the maximum size in bytes of the log file before it is pruned and 
       a new file started. 
       @param newSize uint32 variable that defines the maximum size in bytes. 
           If zero (0) the size is unlimited.  This is the default unless the
           log size varaible is set either by this method or the CIMPLE
           config file.
       @return bool Returns true if the input is accepted. 
     */
    static bool setLogFileMaxSize(uint32 newSize);

    /**
       Get the value of the variable that defines the maximum size of the 
       log file. 
       @return uint32 
     */
    static uint32 getLogFileMaxSize();

    /**
       Set the internal variable that controls the maximum number of log files 
       that CIMPLE will maintain.  If the logFileMaxSize is set to a non-zero 
       value, each time the log file reaches that size, it is closed, the name 
       changed and a new log file started.  This variable controls the maximum 
       number of backup log files maintained.  When this limit is reached, 
       old files will be deleted. If the current value set by this variable is 
       zero (0) no old files will be maintained and the current file will be 
       deleted when it reaches the maximum size.  Zero is the default value for 
       the variable if it is not set by this method or the CIMPLE config file. 
       The backup log files are numbered messages.n where n is the number of 
       backup file, 1 being the newest. 
       @param number uint32
       @return bool Returns true if the method is accepted. 
       NOTE: Maximum number of backup files is 9. Also there is a cost to 
       keeping many files because of the renaming process. 
     */
    static bool setLogMaxBackupFiles(uint32 number);

    /**
     * Get the current value for the variable that controls the maximum 
     * number of log files maintained 
     * @return uint32 
     */
    static uint32 getLogMaxBackupFiles();

    /**
     * Set the logging enabled state to either true or false. When the logging 
     * state is true, logging is enabled. Otherwise it is completely disabled. 
     * The default before being set by either this method or the CIMPLE 
     * configuration files is true. 
     * @param netState Boolean defining the new state
     * @return bool 
     */
    static bool setLogEnabledState(bool netState);

    /**
     * Get current logEnabledState
     * @return bool Returns the current state 
     */
    static bool getLogEnabledState();

    /**
     * Forces a reread of the CIMPLE configuration file.  Normally this is 
     * for testing only.
     */
    static void readConfig();

    /**
     * Remove Log files.  Cleans and restarts the log files.  This removes any 
     * log backup files also.  Use this ONLY if you want to completely delete 
     * log files.  Removes all files in the log directory with the logfile 
     * name. 
     * @return true if operation successfully executed. False 
     *         indicates some error in trying to remove files.
     */
    static bool removeLogFiles();

    /**
       Enable or Disable the logging calls from log macros. This corresponds 
       to the ENABLELOGGING runtime configure parameter in .cimplerc 
       @param newState - The state to which this variable is to be set.  If 
       false, logging is immediatly disabled (no more log entries are generated) 
       @return bool defining the previous state before newState is set into 
       the variable 
     */
    static bool setEnableLoggingState(bool newState);

    /**
       Get the current state of the enable logging variable. 
       @return true if logging enabled.  
     */
    static bool getEnableLoggingState();
private:
    // hide constructor, destructor, etc.
    CimpleConfig();
    ~CimpleConfig();

};
CIMPLE_NAMESPACE_END

#endif /* _cimple_configuration_h */

