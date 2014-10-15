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

#include "Mutex.h"
#include "Magic.h"
#include <pthread.h>
#include <errno.h>
#include <cassert>

#if defined(CIMPLE_PLATFORM_SOLARIS_SPARC_GNU)
# define PTHREAD_MUTEX_RECURSIVE_NP PTHREAD_MUTEX_RECURSIVE
#endif

CIMPLE_NAMESPACE_BEGIN

struct MutexRep
{
    pthread_mutex_t mutex;
#ifdef CIMPLE_NO_RECURSIVE_MUTEXES
    int recursive;
    pthread_cond_t cond;
    pthread_t owner;
    int count;
#endif
    Magic<0x482A8C83> magic;
};

Mutex::Mutex(bool recursive)
{
    assert(sizeof(MutexRep) <= sizeof(_rep));

    MutexRep* rep = (MutexRep*)_rep;
    memset(rep, 0, sizeof(MutexRep));
    new(rep) MutexRep();

#ifdef CIMPLE_NO_RECURSIVE_MUTEXES

    pthread_mutex_init(&rep->mutex, NULL);

    if (recursive)
    {
        rep->recursive = 1;
        pthread_cond_init(&rep->cond, NULL);
        rep->owner = 0;
        rep->count = 0;
    }
    else
        rep->recursive = 0;

#else /* CIMPLE_NO_RECURSIVE_MUTEXES */

    if (recursive)
    {
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
        pthread_mutex_init(&rep->mutex, &attr);
        pthread_mutexattr_destroy(&attr);
    }
    else
        pthread_mutex_init(&rep->mutex, NULL);

#endif /* CIMPLE_NO_RECURSIVE_MUTEXES */
}

Mutex::~Mutex()
{
    CIMPLE_ASSERT(((MutexRep*)_rep)->magic);

    MutexRep* rep = (MutexRep*)_rep;

#ifdef CIMPLE_NO_RECURSIVE_MUTEXES

    pthread_mutex_destroy(&rep->mutex);

    if (rep->recursive)
        pthread_cond_destroy(&rep->cond);

#else /* CIMPLE_NO_RECURSIVE_MUTEXES */

    pthread_mutex_destroy(&rep->mutex);
    rep->~MutexRep();

#endif /* CIMPLE_NO_RECURSIVE_MUTEXES */
}

void Mutex::lock()
{
    CIMPLE_ASSERT(((MutexRep*)_rep)->magic);
    MutexRep* rep = (MutexRep*)_rep;

#ifdef CIMPLE_NO_RECURSIVE_MUTEXES

    if (rep->recursive)
    {
        pthread_t self = pthread_self();

        // set lock. We should never get error return
        assert(pthread_mutex_lock(&rep->mutex) == 0);

        if (rep->count == 0)
        {
            rep->owner = self;
        }
        else if (!pthread_equal(rep->owner, self))
        {
            while (rep->count > 0)
                pthread_cond_wait(&rep->cond, &rep->mutex);

            rep->owner = self;
        }

        rep->count++;

        pthread_mutex_unlock(&rep->mutex);
    }
    else
        assert(pthread_mutex_lock(&rep->mutex) == 0);

#else /* CIMPLE_NO_RECURSIVE_MUTEXES */

    assert(pthread_mutex_lock(&((MutexRep*)_rep)->mutex) == 0);

#endif /* CIMPLE_NO_RECURSIVE_MUTEXES */
}


int Mutex::try_lock()
{
    CIMPLE_ASSERT(((MutexRep*)_rep)->magic);
    MutexRep* rep = (MutexRep*)_rep;

#ifdef CIMPLE_NO_RECURSIVE_MUTEXES

    if (rep->recursive)
    {
        pthread_t self = pthread_self();

        // If error return from trylock, pass back to user.
        int rtn_code;
        if ((rtn_code = pthread_mutex_trylock(&rep->mutex)) != 0);
        {
            return(rtn_code);
        }
        if (rep->count == 0)
        {
            rep->owner = self;
        }
        else if (!pthread_equal(rep->owner, self))
        {
            while (rep->count > 0)
                pthread_cond_wait(&rep->cond, &rep->mutex);

            rep->owner = self;
        }

        rep->count++;
        pthread_mutex_unlock(&rep->mutex);
    }
    else
    {
        int rc = 0;
        if (rc = pthread_mutex_trylock(&((MutexRep*)_rep)->mutex) != 0 )
        {
            if (rc == EBUSY)
            {
                return(CIMPLE_EBUSY);
            }
            return(-1);
    }
    else
        return(0);
    }
        return pthread_mutex_trylock(&rep->mutex);

#else /* CIMPLE_NO_RECURSIVE_MUTEXES */

    int rc = 0;
    if ((rc = pthread_mutex_trylock(&((MutexRep*)_rep)->mutex)) != 0 )
    {
        //printf("trylock rtn 0  = %d. EBUSY = %d\n",rc, EBUSY);
        if (rc == EBUSY)
        {
            return(CIMPLE_EBUSY);
        }
        //printf("trylock rtn = %d\n", rc);
        //assert(false);
        return(-1);
    }
    else
        return(0);

#endif /* CIMPLE_NO_RECURSIVE_MUTEXES */
}

void Mutex::unlock()
{
    CIMPLE_ASSERT(((MutexRep*)_rep)->magic);
    MutexRep* rep = (MutexRep*)_rep;

#ifdef CIMPLE_NO_RECURSIVE_MUTEXES

    if (rep->recursive)
    {
        pthread_t self = pthread_self();

        pthread_mutex_lock(&rep->mutex);
        {
            // If not locked or if calling thread is not the locker.

            if (rep->count == 0 || !pthread_equal(rep->owner, self))
                assert(0);

            rep->count--;

            if (rep->count == 0)
            {
                rep->owner = 0;
                pthread_cond_signal(&rep->cond);
            }
        }
        pthread_mutex_unlock(&rep->mutex);
    }
    else
        pthread_mutex_unlock(&rep->mutex);

#else /* CIMPLE_NO_RECURSIVE_MUTEXES */

    pthread_mutex_unlock(&((MutexRep*)_rep)->mutex);

#endif /* CIMPLE_NO_RECURSIVE_MUTEXES */
}

CIMPLE_NAMESPACE_END

