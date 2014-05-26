ACLOCAL_AMFLAGS = -I m4

AM_CXXFLAGS = -std=c++0x

lib_LTLIBRARIES = libhttpproxy.la
libhttpproxy_la_SOURCES = \
./src/win32/socket_handle.cpp \
./src/win32/inet_address.cpp \
./src/win32/platform_error.cpp \
./src/win32/socket.cpp \
./src/win32/socket_environment.cpp \
./src/win32/thread.cpp
libhttpproxy_la_LDFLAGS = -no-undefined -lwsock32 -lws2_32 -lmswsock

noinst_PROGRAMS = test1
test1_SOURCES = ./test/main.cpp
test1_LDADD = libhttpproxy.la
test1_LDFLAGS = -all-static

SUBDIRS = src
