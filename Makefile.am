ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS	=
AM_CFLAGS	=
AM_CXXFLAGS = -std=c++0x
AM_LDFLAGS	=

lib_LTLIBRARIES = libhttpproxy.la
libhttpproxy_la_SOURCES = \
./src/@platform@/socket_handle.cpp \
./src/@platform@/inet_address.cpp \
./src/@platform@/platform_error.cpp \
./src/@platform@/socket.cpp \
./src/@platform@/socket_environment.cpp \
./src/utils.cpp

if OS_WIN32
libhttpproxy_la_SOURCES += ./src/@platform@/thread.cpp
endif

libhttpproxy_la_LDFLAGS = $(AM_LDFLAGS)
if OS_WIN32
libhttpproxy_la_LDFLAGS += -lwsock32 -lws2_32 -lmswsock
libhttpproxy_la_LDFLAGS += -no-undefined
endif

check_PROGRAMS = test1
test1_SOURCES = ./tests/test1.cpp
test1_LDADD = libhttpproxy.la
test1_LDFLAGS = -all-static

TESTS = $(check_PROGRAMS)

SUBDIRS = src
