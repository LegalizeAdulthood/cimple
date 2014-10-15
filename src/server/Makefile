TOP = ../..
include $(TOP)/mak/config.mak

BINARY = cimpled

EXTRA_INCLUDES = -I.

LIBRARIES = -lpthread

SOURCES = \
    main.cpp \
    OS_accept.cpp \
    OS_close.cpp \
    OS_close_on_exec.cpp \
    OS_init_server_addr.cpp \
    OS_listener_socket.cpp \
    OS_recv.cpp \
    OS_recv_n.cpp \
    OS_send.cpp \
    OS_send_n.cpp \
    OS_set_blocking.cpp \
    OS_socket.cpp \
    Server_accept_thread.cpp \
    Server_run.cpp \

include $(TOP)/mak/rules.mak

tests:
