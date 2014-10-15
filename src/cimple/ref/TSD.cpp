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

#include "TSD.h"

CIMPLE_NAMESPACE_BEGIN

struct TSD_Entry
{
    pthread_t self;
    void* data;
};

TSD::TSD() : _entries(0), _num_entries(0)
{
    pthread_mutex_init(&_mutex, NULL);
}

TSD::~TSD()
{
    pthread_mutex_destroy(&_mutex);
    free(_entries);
}

void TSD::set(void* data)
{
    pthread_mutex_lock(&_mutex);
    {
        pthread_t self = pthread_self();

        for (size_t i = 0; i < _num_entries; i++)
        {
            if (pthread_equal(self, _entries[i].self))
            {
                _entries[i].data = data;
                pthread_mutex_unlock(&_mutex);
                return;
            }
        }

        _entries = (TSD_Entry*)realloc(
            _entries, (_num_entries + 1) * sizeof(TSD_Entry));
        _entries[_num_entries].self = self;
        _entries[_num_entries].data = data;
        _num_entries++;
    }
    pthread_mutex_unlock(&_mutex);
}

void* TSD::get()
{
    pthread_mutex_lock(&_mutex);
    {
        pthread_t self = pthread_self();

        for (size_t i = 0; i < _num_entries; i++)
        {
            if (pthread_equal(self, _entries[i].self))
            {
                void* data = _entries[i].data;
                pthread_mutex_unlock(&_mutex);
                return data;
            }
        }
    }
    pthread_mutex_unlock(&_mutex);

    return 0;
}

CIMPLE_NAMESPACE_END

