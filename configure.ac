# Process this file with autoconf to produce a configure script.

dnl ========== initialization ==========

AC_INIT([mona],[1.4],[amoeller@cs.au.dk],[mona],[http://www.brics.dk/mona/])
RELEASE=18
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR(Front/mona.cpp)
AM_INIT_AUTOMAKE()
AC_CONFIG_HEADERS([config.h])

AC_SUBST(VERSION)
AC_SUBST(RELEASE)
AC_DEFINE_UNQUOTED(RELEASE, "$RELEASE", Release number of package)

AC_USE_SYSTEM_EXTENSIONS
AC_SYS_LARGEFILE
AC_CONFIG_MACRO_DIR([m4])

dnl ========== checks for programs ==========

AC_PROG_CC
AC_PROG_CXX
AM_PROG_AR
AC_PROG_INSTALL
AC_PROG_YACC
AM_PROG_LEX
LT_INIT

AC_LANG_PUSH([C++])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
  [[#ifndef __cplusplus
    #error "broken C++"
    #endif]])],,
  [AC_MSG_ERROR(C++ compiler not found)])
AC_LANG_POP([C++])

if test "x$LEX" != xflex; then
  AC_MSG_ERROR(flex not found)
fi

dnl ========== special configure parameters ==========

CFG=

AC_ARG_ENABLE(debug,
[  --enable-debug          development mode],
[ case "${enableval}" in
     yes) CXXFLAGS="$CXXFLAGS -g -ansi -pedantic" ;;
     no) CXXFLAGS="$CXXFLAGS -O3 -DNDEBUG" ;;
     *) AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;;
  esac],
[ CXXFLAGS="$CXXFLAGS -O3 -DNDEBUG" ])

if test "x$GCC" = "xyes"; then
  if test -z "`echo "$CXXFLAGS" | grep "\-Wall -Wno-unused-function -Wno-unused-label -Wno-sign-compare" 2> /dev/null`" ; then
    CXXFLAGS="$CXXFLAGS -Wall -Wno-unused-function -Wno-unused-label -Wno-sign-compare"
  fi
fi

AC_ARG_ENABLE(profiling,
[  --enable-profiling      compile with profiling],
[ case "${enableval}" in
     yes) CXXFLAGS="$CXXFLAGS -pg" ;;
     no) ;;
     *) AC_MSG_ERROR(bad value ${enableval} for --enable-profiling) ;;
  esac])

AC_ARG_ENABLE(dlmalloc,
[  --enable-dlmalloc       use dlmalloc instead of built-in malloc],
[ case "${enableval}" in
     yes) CXXFLAGS="$CXXFLAGS -DUSE_DLMALLOC" ;;
     no) ;;
     *) AC_MSG_ERROR(bad value ${enableval} for --enable-dlmalloc) ;;
  esac
  CFG="$CFG --enable-dlmalloc=$enableval"])

AC_ARG_ENABLE(memdebug,
[  --enable-memdebug       enable debug info for dlmalloc],
[ case "${enableval}" in
     yes) CXXFLAGS="$CXXFLAGS -DDEBUG" ;;
     no) ;;
     *) AC_MSG_ERROR(bad value ${enableval} for --enable-memdebug) ;;
  esac])

AC_ARG_ENABLE(maxalloc,
[  --enable-maxalloc       measure max allocated memory for dlmalloc],
[ case "${enableval}" in
     yes) CXXFLAGS="$CXXFLAGS -DMAXALLOCATED" ;;
     no) ;;
     *) AC_MSG_ERROR(bad value ${enableval} for --enable-maxalloc) ;;
  esac])

AC_SUBST(CFG)

dnl ========== checks for operating system ==========

AC_MSG_CHECKING(Win32 compiler)
have_win32_gcc=no
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[ #include <windows.h> ]], [[]])],[have_win32_gcc=yes],[])
AC_MSG_RESULT($have_win32_gcc)

if test x$have_win32_gcc = xyes; then
  CXXFLAGS="$CXXFLAGS -DWIN32"
fi

CFLAGS=$CXXFLAGS
AC_SUBST(CFLAGS)

dnl ========== checks for header files ==========

AC_HEADER_STDC
AC_CHECK_HEADERS(stdlib.h string.h sys/time.h unistd.h
                 ,,AC_MSG_ERROR(required header file not found))

dnl ========== checks for typedefs, structures, and compiler characteristics ==========

AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

dnl ========== checks for library functions ==========

AC_DEFUN([FUNCTION_MISSING], [AC_MSG_ERROR(required library function not found)])

AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MMAP
AC_CHECK_FUNCS(alarm memset mkdir,,FUNCTION_MISSING)

dnl ========== output files ==========

AC_CONFIG_FILES([mona.spec
          makefile
          config/makefile
          Mem/makefile
          BDD/makefile
          DFA/makefile
          GTA/makefile
          Front/makefile
          Lib/makefile
          Examples/makefile])
AC_OUTPUT
