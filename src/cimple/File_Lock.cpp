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
    Implements a cooperative lock file mechanism that can be used to
    lock files between processes (not threads).  This creates a lock
    file and provides for lock and unlock functions that the user must
    use to define file lock regions for other files.
    Thus log.cpp locks the log file with a lock file and
    places lock(), unlock() around all modifications to that file.
    However a that does not use this lock mechanism could access "locked"
    file at any time.
    
*/
#include <cassert>
#include "File_Lock.h"

#ifdef CIMPLE_UNIX
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
#endif

#ifdef CIMPLE_WINDOWS_MSVC
# include <windows.h>
#endif

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// POSIX implementation
//
//==============================================================================

#ifdef CIMPLE_UNIX

struct File_Lock_Rep
{
    struct flock lock;
    struct flock unlock;
    int fd;
};

File_Lock::File_Lock(const char* path)
{
    _rep = new File_Lock_Rep;

    _rep->lock.l_type = F_WRLCK;
    _rep->lock.l_whence = SEEK_SET;
    _rep->lock.l_start = 0;
    _rep->lock.l_len = 0; /* lock whole file */

    _rep->unlock.l_type = F_UNLCK;
    _rep->unlock.l_whence = SEEK_SET;
    _rep->unlock.l_start = 0;
    _rep->unlock.l_len = 0; /* lock whole file */

    _rep->fd = open(path, O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR);
}

File_Lock::~File_Lock()
{
    if (_rep->fd != -1)
        close(_rep->fd);

    delete _rep;
}

bool File_Lock::okay() const
{
    return _rep->fd != -1;
}

int File_Lock::lock()
{
    int r;

    if (_rep->fd == -1)
        return -1;

    CIMPLE_RESTART(fcntl(_rep->fd, F_SETLKW, &_rep->lock), r) ;

    if (r != 0)
        return -1;

    return 0;
}

int File_Lock::unlock()
{
    if (_rep->fd == -1)
        return -1;

    int r;
    CIMPLE_RESTART(fcntl(_rep->fd, F_SETLKW, &_rep->unlock), r) ;

    return r;
}

#endif /* CIMPLE_UNIX */

//==============================================================================
//
// Windows implementation
//
//==============================================================================

#ifdef CIMPLE_WINDOWS_MSVC

struct File_Lock_Rep
{
    OVERLAPPED lock;
    OVERLAPPED unlock;
    HANDLE handle;
};

File_Lock::File_Lock(const char* path)
{
    _rep = new File_Lock_Rep;
    memset(_rep, 0, sizeof(File_Lock_Rep));

    do
    {
        _rep->handle = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, 
            OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    }
    while ((GetLastError() == ERROR_SHARING_VIOLATION));
}

File_Lock::~File_Lock()
{
    if (_rep->handle != INVALID_HANDLE_VALUE)
        CloseHandle(_rep->handle);

    delete _rep;
}

bool File_Lock::okay() const
{
    return _rep->handle != INVALID_HANDLE_VALUE;
}

int File_Lock::lock()
{
    if (_rep->handle == INVALID_HANDLE_VALUE)
        return -1;
 

    if (LockFileEx(
        _rep->handle, LOCKFILE_EXCLUSIVE_LOCK, 0, 0, 0, &_rep->lock) == 0)
        return -1;

    return 0;
}

int File_Lock::unlock()
{
    if (_rep->handle == INVALID_HANDLE_VALUE)
        return -1;

    if (UnlockFileEx(_rep->handle, 0, 0, 0, &_rep->unlock) == 0)
        return -1;

    return 0;
}

#endif /* CIMPLE_WINDOWS_MSVC */

CIMPLE_NAMESPACE_END
