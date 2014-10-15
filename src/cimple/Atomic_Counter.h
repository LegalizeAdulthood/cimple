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

#ifndef _cimple_Atomic_Counter_h
#define _cimple_Atomic_Counter_h

#include "config.h"
#include "Atomic.h"

CIMPLE_NAMESPACE_BEGIN

/** Atomic_Counter is an integer counter whose methods can be invoked safely
*   by multiple threads while insuring the atomicity of the
*   operations on the Atomic Counter. The Atomic_Counter
*   represents an integer.
*/
class Atomic_Counter
{
public:

    /** Default constructor.
    */
    Atomic_Counter();

    /** Initializing constructor.
    */
    Atomic_Counter(int x);

    /** Copy constructor.
    */
    Atomic_Counter(Atomic_Counter& x);

    /** Destructor.
    */
    ~Atomic_Counter();

    /** Assignment operator.
    */
    Atomic_Counter& operator=(Atomic_Counter& x);

    /** Get the counter.
    */
    int get() const;

    /** Increment the counter.
    */
    void inc();

    /** Decrement the counter.
    */
    void dec();

    /** Decrement the counter. Return true if it is zero afterwards.
    */
    bool dec_and_test();

private:

    Atomic _rep;
};

inline Atomic_Counter::Atomic_Counter()
{
    Atomic_create(&_rep, 0);
}

inline Atomic_Counter::Atomic_Counter(int x)
{
    Atomic_create(&_rep, x);
}

inline Atomic_Counter::Atomic_Counter(Atomic_Counter& x)
{
    Atomic_create(&_rep, x._rep.n);
}

inline Atomic_Counter::~Atomic_Counter()
{
    Atomic_destroy(&_rep);
}


inline Atomic_Counter& Atomic_Counter::operator=(Atomic_Counter& x)
{
    if (this != &x)
        Atomic_set(&_rep, x._rep.n);

    return *this;
}

inline int Atomic_Counter::get() const
{
    return Atomic_get(&_rep);
}

inline void Atomic_Counter::inc()
{
    Atomic_inc(&_rep);
}


inline void Atomic_Counter::dec()
{
    Atomic_dec(&_rep);
}

inline bool Atomic_Counter::dec_and_test()
{
    return Atomic_dec_and_test(&_rep);
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Atomic_Counter_h */
