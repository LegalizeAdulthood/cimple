This directory contains a partial implementations of several POSIX headers
used to port CIMPLE to Windows. PLEASE DO NOT DIRECTLY CALL THESE FUNCTIONS
SINCE THEY ARE NOT PART OF THE SUPPORTED CIMPLE INTERFACE.

The following functions are implemented.

    pthread.h
	pthread_mutex_init()
	pthread_mutex_lock()
	pthread_mutex_unlock()
	pthread_mutex_destroy()
	pthread_mutexattr_init()
	pthread_mutexattr_destroy()
	pthread_mutexattr_settype()
	pthread_once()
	pthread_key_create()
	pthread_key_delete()
	pthread_setspecific()
	pthread_getspecific()
	pthread_create()
	pthread_self()
	pthread_attr_init()
	pthread_attr_destroy()
	pthread_attr_setdetachstate()
	pthread_exit()
	pthread_join()
	pthread_equal()
	pthread_cond_init()
	pthread_cond_destroy()
	pthread_cond_wait()
	pthread_cond_signal()
    pthread_cond_broadcast()

    dirent.h
	opendir()
	readdir()
	closedir()

    dlfcn.h
	dlopen()
	dlsym()
	dlclose()
	dlerror()

    getopt.h
	getopt()

    libgen.h
	dirname()

    unistd.h
	sleep()
