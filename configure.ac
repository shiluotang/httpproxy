#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([httpproxy], [0.1], [shengquangang2008@gmail.com])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_SRCDIR([test/main.cpp])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
m4_pattern_allow([AM_PROG_AR])

# Checks for programs.
AC_PROG_CXX
AM_PROG_AR
LT_INIT

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lws2_32':
AC_CHECK_LIB([ws2_32], [WSAStartup])
# FIXME: Replace `main' with a function in `-lmswsock':
AC_CHECK_LIB([mswsock], [EnumProtocols])
# FIXME: Replace `main' with a function in `-lwsock32':
AC_CHECK_LIB([wsock32], [WSAStartup])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([memset socket])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
