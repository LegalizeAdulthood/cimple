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

#include <cimple/cimple.h>
#include <cassert>
#include <cstdio>
#include <cimple/log.h>
#include <cimple/String.h>
#include <unistd.h>
#include <cimple/CimpleConfig.h>
#include <cimple/Adapter_Tracer.h>
#include <fstream>

using namespace cimple;

static bool verbose;

// conditionally display start test message
void startTestMsg(const char * text)
{
    if(verbose)
    {
        printf("Start test %s\n", text);
    }
}
// return line count
bool fileLineCountRange(const char* path, uint32 min, uint32 max)
{
    assert(FileSystem::exists(path));
    uint32 lineCount = 0;

    std::ifstream fs;

    fs.open(path);

    //std::fstream fs;
    Buffer buffer;
    while(FileSystem::get_line(fs, buffer))
    {
        lineCount++;
    }

    if(verbose)
    {
        if(!((lineCount >= min) && (lineCount <= max)))
            printf("ERROR: lineCount %s, rtnd cnt=%u min=%u, max=%u\n",
                   path, lineCount, min, max);        {
        }
    }
    return ((lineCount >= min) && (lineCount <= max));
}
bool fileSizeRange(const char* path, uint32 min, uint32 max)
{
    uint32 fileSize;
    assert(FileSystem::get_size(path, fileSize));
    if(verbose)
    {
        if(!(fileSize >= min && fileSize <= max))
        {
            printf("ERROR: fileSizeRange %s, rtnd size=%u min=%u, max=%u\n",
                   path, fileSize, min, max);
        }
    }
    return ((fileSize >= min && fileSize <= max)? true : false);
}

void showConfigParams()
{
    if(verbose)
    {
        printf("Show log info: log_level = %u (%s), maxLogFiles = %u,"
               " maxLogSize = %u enableState = %s\n",
           CimpleConfig::getLogLevel(),
           CimpleConfig::getLogLevelString(),
           CimpleConfig::getLogMaxBackupFiles(),
           CimpleConfig::getLogFileMaxSize(),
           (CimpleConfig::getEnableLoggingState()?"true": "false"));
    }
}

// set the contents variable into a file named .cimplerc and copy the
// contents of the file into the test result file.
void set_cimplerc(const char* contents)
{
    // write the chars to the cimple config file
    {
        FILE* fp;
        if((fp=fopen(".cimplerc", "w")) == NULL)
        {
            printf("Cannot open file.\n");
            exit(1);
        }
        fprintf(fp, "%s",contents); /* write to file */
        fclose(fp);
    }

    // append the created .cimplerc into the result file
    // write the chars to the cimple config file
    {
        FILE* fp;
        if((fp=fopen("result", "a")) == NULL)
        {
            printf("Cannot open file.\n");
            exit(1);
        }
        fprintf(fp, "%s",contents); /* write to file */
        fclose(fp);
    }
}
                          

//Test setting the directory location via setting the env var. This test
// does not use the readconfig function to set configuration.  It is set
// when the first log macro is called.
void test01()
{
    startTestMsg("test01 - test setting directory via env var");

    // start test by cleaning out all log files
    assert(CimpleConfig::removeLogFiles());
    assert(!FileSystem::exists(".cimple/messages"));

    // set the config file .cimplerc
    const char * cimplerc =
    "LOG_LEVEL=DBG\n";
    set_cimplerc(cimplerc);

    assert(FileSystem::exists(".cimplerc"));

    // generate a set of log entries
    String test_string("test string");
    int i = 3;

    uint32 test1 = 9999;

    CIMPLE_DBG(("Generate DBG msg: %s", test_string.c_str()));
    CIMPLE_INFO(("Start Log test01: %d", i));
    CIMPLE_INFO(("Generate INFOTest uint32 for Log String: %u", test1));
    CIMPLE_ERR(("Generate ERR msg"));
    CIMPLE_FATAL(("generate FATAL message"));

    showConfigParams();

#ifdef DISABLE_LOG_MACROS_OPT
    assert(CimpleConfig::getLogLevel() == 0);
    assert(CimpleConfig::getLogFileMaxSize() == 0);
    assert(CimpleConfig::getLogMaxBackupFiles() == 0);
#else
    assert(CimpleConfig::getLogLevel() == LL_DBG);
    assert(CimpleConfig::getLogFileMaxSize() == 0);
    assert(CimpleConfig::getLogMaxBackupFiles() == 0);
#endif
    assert(FileSystem::exists(".cimple/messages"));
}

// Test dynamic change of log configuration parameters
void test02()
{
    startTestMsg("test02 - test dynamic change of log config params");

    // start test by cleaning out all log files
    assert(CimpleConfig::removeLogFiles());
    assert(!FileSystem::exists(".cimple/messages"));

    // Set the configuration from the config file
    const char * cimplerc =
    "LOG_LEVEL=DBG\n"
    "MAX_LOG_FILE_SIZE=100000\n"
    "MAX_LOG_BACKUP_FILES=5\n";

    set_cimplerc(cimplerc);
    CimpleConfig::readConfig();

    CIMPLE_INFO(("Start Log test02a"));

    showConfigParams();

    assert(CimpleConfig::getLogLevel() == LL_DBG);
    assert(CimpleConfig::getLogFileMaxSize() == 100000);
    assert(CimpleConfig::getLogMaxBackupFiles() == 5);


    CIMPLE_INFO(("Start Log test02b. Should only show WARN and higher msgs"));

    const char * cimplerc1 =
    "LOG_LEVEL=WARN\n"
    "MAX_LOG_FILE_SIZE=100000\n"
    "MAX_LOG_BACKUP_FILES=5\n";

    set_cimplerc(cimplerc1);
    CimpleConfig::readConfig();

    CIMPLE_DBG(("Generate DBG msg: %s", "blah"));
    CIMPLE_INFO(("Start Log test01:"));
    CIMPLE_INFO(("Generate INFO Test"));
    CIMPLE_ERR(("Generate ERR msg"));
    CIMPLE_FATAL(("Generate FATAL message"));

    showConfigParams();

    assert(CimpleConfig::getLogLevel() == LL_WARN);
    assert(strcmp(CimpleConfig::getLogLevelString(),"WARN") == 0);
    assert(CimpleConfig::getLogFileMaxSize() == 100000);
    assert(CimpleConfig::getLogMaxBackupFiles() == 5);

    // change the various parameters with CimpleConfig and try again:

    CimpleConfig::setLogLevel(LL_DBG);
    CimpleConfig::setLogFileMaxSize(5000);
    CimpleConfig::setLogMaxBackupFiles(8);

    assert(CimpleConfig::getLogLevel() == LL_DBG);
    assert(strcmp(CimpleConfig::getLogLevelString(),"DBG") == 0);
    assert(CimpleConfig::getLogFileMaxSize() == 5000);
    assert(CimpleConfig::getLogMaxBackupFiles() == 8);
}

// Test generation of multiple log files. Test generates logs that
// require log file prune.
void test03()
{
    startTestMsg("test03 - Test generation of multiple log files");

    // start test by cleaning out all log files
    assert(CimpleConfig::removeLogFiles());
    assert(!FileSystem::exists(".cimple/messages"));

    const char * cimplerc =
    "LOG_LEVEL=DBG\n"
    "MAX_LOG_FILE_SIZE=500\n"
    "MAX_LOG_BACKUP_FILES=5\n";

    set_cimplerc(cimplerc);
    CimpleConfig::readConfig();
    CIMPLE_INFO(("Start Log test03"));

    showConfigParams();

    assert(CimpleConfig::getLogLevel() == LL_DBG);
    assert(CimpleConfig::getLogFileMaxSize() == 500);
    assert(CimpleConfig::getLogMaxBackupFiles() == 5);
  
    // generate  log entries
    for(uint32 i = 0; i < 10000 ; i++)
    {
        CIMPLE_INFO(("Generate INFO Test %u", i));
    }

    // should be about 5 files at this point
    assert(FileSystem::exists(".cimple/messages"));
    assert(fileLineCountRange(".cimple/messages", 8, 8));
    assert(FileSystem::exists(".cimple/messages.1"));
    assert(FileSystem::exists(".cimple/messages.2"));
    assert(FileSystem::exists(".cimple/messages.3"));
    assert(FileSystem::exists(".cimple/messages.4"));
    assert(fileSizeRange(".cimple/messages.4", 300, 700));
    assert(FileSystem::exists(".cimple/messages.5"));
}

// test the removelog functions
void test04()
{
    startTestMsg("test04 - test removeLogFiles functions");

    assert(FileSystem::exists(".cimple/messages"));
    assert(fileLineCountRange(".cimple/messages", 8, 8));
    assert(FileSystem::exists(".cimple/messages.4"));
    assert(fileLineCountRange(".cimple/messages.4", 8, 8));
    assert(FileSystem::exists(".cimple/messages.5"));

    assert(CimpleConfig::removeLogFiles());

    // confirm that the messages file no longer exists.
    assert(!FileSystem::exists(".cimple/messages"));
    assert(!FileSystem::exists(".cimple/messages.1"));
    assert(!FileSystem::exists(".cimple/messages.4"));
    assert(!FileSystem::exists(".cimple/messages.5"));
}

void test05()
{
    startTestMsg("test05 - test enablelogstate API");

    // start test with empty log file
    assert(!FileSystem::exists(".cimple/messages"));

    const char * cimplerc =
    "LOG_LEVEL=DBG\n"
    "MAX_LOG_FILE_SIZE=5000\n"
    "MAX_LOG_BACKUP_FILES=5\n";

    set_cimplerc(cimplerc);
    CimpleConfig::readConfig();

    // turn off all logging
    bool rtn = CimpleConfig::setEnableLoggingState(false);

    // Should have been true since that is default
    assert(rtn == true);

    showConfigParams();
    CIMPLE_INFO(("Start Log test05"));

    CIMPLE_DBG(("Generate DBG msg: %s", "blah"));
    CIMPLE_INFO(("Start Log test01:"));
    CIMPLE_INFO(("Generate INFO Test"));
    CIMPLE_ERR(("Generate ERR msg"));
    CIMPLE_FATAL(("Generate FATAL message"));

    // assert that there is no log or it is empty
    assert(! FileSystem::exists(".cimple/messages") ||
        fileSizeRange(".cimple/messages", 0, 0));

    // turn on all logging. returns old state
    rtn = CimpleConfig::setEnableLoggingState(true);

    // Should have been false since that is default
    assert(rtn == false);

    CIMPLE_DBG(("Generate DBG msg: %s", "blah"));
    CIMPLE_INFO(("Start Log test01:"));
    CIMPLE_INFO(("Generate INFO Test"));
    CIMPLE_ERR(("Generate ERR msg"));
    CIMPLE_FATAL(("Generate FATAL message"));

    assert(FileSystem::exists(".cimple/messages"));
    // TODO Following test commented because fails on windows May 2010
    //assert(fileSizeRange(".cimple/messages", 200, 1000));
    assert(fileLineCountRange(".cimple/messages",5,5));
}

// test ENABLE_LOGGING turned on with api call. Start with no 
// logs and disabled and then turn on
void test06()
{
    startTestMsg("test06 - Test ENABLE_LOGGING api");

    // start test by cleaning out all log files
    assert(CimpleConfig::removeLogFiles());
    assert(!FileSystem::exists(".cimple/messages"));

    const char * cimplerc =
    "LOG_LEVEL=DBG\n"
    "MAX_LOG_FILE_SIZE=5000\n"
    "MAX_LOG_BACKUP_FILES=5\n"
    "ENABLE_LOGGING=false\n";

    set_cimplerc(cimplerc);
    CimpleConfig::readConfig();

    showConfigParams();
    CIMPLE_INFO(("Start Log test06"));

    CIMPLE_DBG(("Generate DBG msg: %s", "blah"));
    CIMPLE_INFO(("Start Log test01:"));
    CIMPLE_INFO(("Generate INFO Test"));
    CIMPLE_ERR(("Generate ERR msg"));
    CIMPLE_FATAL(("Generate FATAL message"));

    // assert that there is no log or it is empty
    assert(! FileSystem::exists(".cimple/messages") ||
        fileSizeRange(".cimple/messages", 0, 0));

    // turn on all logging
    bool rtn;
    rtn = CimpleConfig::setEnableLoggingState(true);

    // Should have been true since that is default
    assert(rtn == false);

    CIMPLE_DBG(("Generate DBG msg: %s", "blah"));
    CIMPLE_INFO(("Start Log test01:"));
    CIMPLE_INFO(("Generate INFO Test"));
    CIMPLE_ERR(("Generate ERR msg"));
    CIMPLE_FATAL(("Generate FATAL message"));

    assert(FileSystem::exists(".cimple/messages"));
    // TODO Following test commented because fails on windows May 2010
    //assert(fileSizeRange(".cimple/messages", 200, 1000));
    assert(fileLineCountRange(".cimple/messages",5,5));
}

// test option where there is defined max log size but
// zero backup log files.  Log file just deleted at max.
void test07()
{
    startTestMsg("test07 - test 0 backup log file option");

    // start test by cleaning out all log files
    assert(CimpleConfig::removeLogFiles());
    assert(!FileSystem::exists(".cimple/messages"));

    const char * cimplerc =
    "LOG_LEVEL=DBG\n"
    "MAX_LOG_FILE_SIZE=500\n"
    "MAX_LOG_BACKUP_FILES=0\n"
    "ENABLE_LOGGING=true\n";

    set_cimplerc(cimplerc);
    CimpleConfig::readConfig();

    showConfigParams();
    CIMPLE_INFO(("Start Log test07"));
    CIMPLE_INFO(("Config = %s", cimplerc));
    assert(CimpleConfig::getLogLevel() == LL_DBG);
    assert(CimpleConfig::getLogFileMaxSize() == 500);
    assert(CimpleConfig::getLogMaxBackupFiles() == 0);
  
    // generate  bunch of log entries
    for(uint32 i = 0; i < 10000 ; i++)
    {
        CIMPLE_INFO(("Generate INFO Test %u", i));
    }

    // should be about 5 files at this point
    assert(FileSystem::exists(".cimple/messages"));
    assert(fileLineCountRange(".cimple/messages", 0, 30));
    assert(!FileSystem::exists(".cimple/messages.1"));
    assert(!FileSystem::exists(".cimple/messages.2"));
    assert(!FileSystem::exists(".cimple/messages.3"));
    assert(!FileSystem::exists(".cimple/messages.4"));
    assert(!FileSystem::exists(".cimple/messages.5"));

    assert(fileSizeRange(".cimple/messages", 0, 500));
}

// Following conditional compile tests the adapter trace functions
#ifdef CIMPLE_ENABLE_ADAPTER_TRACE

// Function recurses itself number of times defined by data
// used to generate a number of trace log entries and confirm
// that the trace function macros work.
bool recurse(uint32 data)
{
    PENTRY("recurse");
    uint32 loop = data;
    if(data != 0)
    {
        recurse(--loop);
    }
    PEXITBOOL(loop);
    return loop;
}

uint32 testAdapterTraceUint32(uint32 data)
{
    PENTRY("testAdapterTraceUint32");
    PEXITBOOL(data);
    return data;
}

// test the adapter trace macros.
bool testAdapterTrace(bool returnValue)
{
    PENTRY("testAdapterTrace");

    testAdapterTraceUint32(1);

    uint32 recurseCounter = 32;
    recurse(recurseCounter);

    PEXITBOOL(returnValue);
    return true;
}

// test adapter trace function.
void test08()
{
    startTestMsg("test08 - Test adapter trace functions");

    const char * cimplerc =
    "LOG_LEVEL=DBG\n"
    "MAX_LOG_FILE_SIZE=5000\n"
    "MAX_LOG_BACKUP_FILES=5\n";

    set_cimplerc(cimplerc);

    CimpleConfig::readConfig();
    CIMPLE_INFO(("Start Log test04 - Test Adapter Trace"));
    testAdapterTrace(true);

    CIMPLE_INFO(("Success ++++Log test04 - Test Adapter Trace"));
}
#endif   // CIMPLE_ENABLE_ADAPTER_TRACE

int main(int argc, char** argv)
{
    verbose = getenv("CIMPLE_TEST_VERBOSE") ? true : false;

    // tests are executed with location determined by variable from
    // Makefile.  Normally this is the directory in which the test pgm
    // exists. This sets that location and is also a test of the
    // functions to set and get that value.
    assert(getenv("CIMPLE_HOME_TEST")? true : false);
    assert(CimpleConfig::setHomeEnv("CIMPLE_HOME_TEST"));
    assert(strcmp(CimpleConfig::getHomeEnv(), "CIMPLE_HOME_TEST") == 0);

    // test setting the env var from an API and basic log output
    test01();

    // test loading of config file file parameters.
    test02();

    // test capability to prune log file
    test03();

    // test capability to dynamically remove log files
    test04();

    // test the enable_logging function to see if we completely turn
    // off logging and then turn it back on
    test05();
    
    // test the enable log config param
    test06();

    // test the 0 backup log files option
    test07();

    // test the Adapter_Tracer functions
#ifdef CIMPLE_ENABLE_ADAPTER_TRACE
    test08();
#endif
    

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}
