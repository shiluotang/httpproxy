AC_DEFUN([AX_PLATFORM_DETECT],
[AC_MSG_CHECKING([detecting platform])
case $host in
    *cygwin*)
        platform=win32
    ;;
    *mingw*)
        platform=win32
    ;;
    *pw32*)
        platform=win32
    ;;
    *cegcc*)
        platform=win32
    ;;
    *apple*)
        platform=mac
    ;;
    *arm*)
        platform=arm
    ;;
    *gnueabi*)
        platform=arm
    ;;
    *linux*)
        platform=linux
    ;;
    *)
        platform=linux
    ;;
esac
AC_MSG_RESULT([$platform])
AC_SUBST(platform)
AM_CONDITIONAL([OS_WIN32], [test "x$platform" = "xwin32"])
])
