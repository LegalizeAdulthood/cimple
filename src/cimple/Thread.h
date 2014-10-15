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
/*******************************************************************************
    The Threads.h header file defines a portable interface for creating and
    managing threads in a CIMPLE provider environment
*******************************************************************************/

#ifndef _cimple_Thread_h
#define _cimple_Thread_h

#include "config.h"

CIMPLE_NAMESPACE_BEGIN


typedef void* (*Thread_Proc)(void* arg);


/**
*   The Thread class defines a portable API for creating and
*   managing threads within CIMPLE. It includes functions for
*   creating threads (joinable and detached), exiting threads,
*   joining threads, and for testing the equality of two threads
*   identifiers.
*/
class CIMPLE_CIMPLE_LINKAGE Thread
{
public:

    /** 
     * Thread object constructor
     */
    Thread();

    /** 
     * Thread constructor.
     * 
     * @param x
     */
    Thread(const Thread& x);

    /** 
     * Thread Destructor
     * 
     */
    ~Thread();

    /** 
     * Thread assignment
     * 
     * @param x
     * 
     * @return Thread&
     */
    Thread& operator=(const Thread& x);

    /** 
     * Static method to create a joinable thread. This method 
     * creates the thread running the \a proc function proc with the
     * argument \a arg.  This function was kept simple by allowing 
     * only a single void* argument, \a arg, to be passed to the new
     * thread. The thread may be terminated with the join or exit 
     * methods. 
     * 
     * @param thread The thread object that defines the thread
     * @param proc The function to execute.  This function must have 
     *             a single argument of the form void* arg.
     * @param arg  void The single void argument that will be 
     *             supplied to the function defined by the proc
     *             variable.
     * 
     * @return int return indicating if the thread was created. if 
     *         the return == 0 the thread was successfully created.
     *         If nonzero, there was an error increation and the
     *         error code is the return from the create. Since on
     *         many systems this is pthread, these codes often
     *         correspond the the pthread_create error return codes.
     * EXAMPLE: 
     * \code 
     *     static void* _thread_proc(void* arg)
     *     {
     *         ... code that will execute on thread
     *     }
     *  
     *     // Thread creation
     *     Thread _thread;
     *     Thread::create_joinable(_thread,
     *         (Thread_Proc)_thread_proc, this);
     * \endcode
     */
    static int create_joinable(Thread& thread, Thread_Proc proc, void* arg);

    /** 
     * method to create a detatched thread using exactly the same 
     * parameter definitions as create_joinable(...) above 
     * 
     * @param thread The thread object that defines the thread.
     * @param proc The function to execute.  This function must have 
     *             a single argument of the form void* arg.
     * @param arg  The argument that will be supplied to the proc.
     * 
     * @return int return indicating if the thread was created. if 
     *         the return == 0 the thread was successfully created.
     *         If nonzero, there was an error increation and the
     *         error code is the return from the create. Since on
     *         many systems this is pthread, these codes often
     *         correspond the the pthread_create error return codes.
     */
    static int create_detached(Thread& thread, Thread_Proc proc, void* arg);

    /** 
     * Static method terminates the calling thread, returning the 
     * value return_value to joining thread. 
     * 
     * @param return_value void* that is returned to the calling 
     *     thread
     *  
     * EXAMPLE: 
     * \code 
     * // Thread processor that performs a simple function, sleeps 
     * // and then exits returning the argument from the creation. 
     *  static void* _proc(void* arg)
     *  {
     *      char* str = (char*)arg;
     *      printf("[%s]\n", str);
     *      Time::sleep(Time::SEC);
     *      Thread::exit(arg);
     *      return arg;
     *  } 
     * \endcode 
     */
    static void exit(void* return_value);

    /** 
     * Static method suspends the execution of the calling thread 
     * until the target thread terminates. The calling thread 
     * receives the target thread's exit val. 
     * 
     * @param thread thread to be joined
     * @param value_ptr void*& value_pointer to be returned
     * 
     * @return int zero if the join was successful.  If non-zero 
     *         there was an error.
     *  
     * EXAMPLE: 
     * \code 
     *   static void* _proc(void* arg)
     *  {
     *      char* str = (char*)arg;
     *      printf("[%s]\n", str);
     *      Time::sleep(Time::SEC);
     *      Thread::exit(arg);
     *      return arg;
     *  }
     *  
     *     // Calling code function
     *     Thread _thread;
     *     char * msg = "Hello";
     *     Thread::create_joinable(_thread, _proc, msg);
     *     void* value_ptr;
     *     int r = Thread::join(_thread, value_ptr);
     *     assert(r == 0);
     * \endcode
     */
    static int join(Thread& thread, void*& value_ptr);

    /** 
     * Static method equal compares two thread identifiers for 
     * equality. 
     * 
     * @param thread1 the first thread identity
     * @param thread2 The second thread identity
     * 
     * @return true if the identies are equal, otherwise false.
     */
    static bool equal(const Thread& thread1, const Thread& thread2);

    /** 
     * get the calling thread's identity
     * 
     * 
     * @return Thread the identity of the calling thread.
     */
    static Thread self();

private:

    char _rep[16];
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Thread_h */
