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

#include <cstdio>
#include <cstring>
#include <cassert>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond;

const size_t MAX = 100000;
size_t count = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

// function that waits on condition and then 
static void* start_routine(void* arg)
{
    for (;;)
    {
    	// printf("wait %s\n", (char*)arg);
    	pthread_cond_wait(&cond, &mutex);
    
    	pthread_mutex_lock(&count_mutex);
    	count++;
    	pthread_mutex_unlock(&count_mutex);
    }

    return 0;
}

int main(int argc, char** argv)
{
    const size_t N = 10;

    pthread_cond_init(&cond, NULL);

    // Create thread attributes.

    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Create N threads.

    for (int i = 0; i < N; i++)
    {
    	pthread_t thread;
    	char buffer[32];
    	sprintf(buffer, "thread-%d", i);
    	int r = pthread_create(&thread, &attr, start_routine, strdup(buffer));
    	assert(r == 0);
    }

    sleep(1);

    // Signal threads until count reaches MAX.

    printf("Test Signal\n");
    for (;;)
    {
    	pthread_mutex_lock(&count_mutex);
    
    	if (count >= MAX)
    	{
    	    pthread_mutex_unlock(&count_mutex);
    	    break;
    	}
    
    	pthread_mutex_unlock(&count_mutex);
    
    	pthread_cond_signal(&cond);
    }
    assert(count == MAX);

    // Broadcast to threads until count reaches Max

    printf("Test Broaadcast\n");
    for (;;)
    {
    	pthread_mutex_lock(&count_mutex);
    
    	if (count >= MAX)
    	{
    	    pthread_mutex_unlock(&count_mutex);
    	    break;
    	}
    
    	pthread_mutex_unlock(&count_mutex);
    
    	pthread_cond_broadcast(&cond);
    }
    //assert(count == MAX);
    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}
