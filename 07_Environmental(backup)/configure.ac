#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([R_HASH_ER], [0.00], [kostya45e@mail.ru])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[
	echo "rhash is needed!"
	exit -1
	])
AC_CHECK_LIB([ncurses],[tputs],[echo "readline need nucurses"],[echo "no ncurses"])
AC_CHECK_LIB([readline -lncurses],[readline],[],[echo "no readline"])
#~ AC_CHECK_LIB([readline],[readline],[],[echo "no readline"])

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])
AC_CHECK_HEADER([rhash.h])
AC_CHECK_HEADER([readline/readline.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror])

# Optional clues
AC_ARG_WITH([readline], 
    AS_HELP_STRING([--with-readline], [Enable readline]), 
    AC_DEFINE(RDLN,[1],[with readline]), 
    AC_DEFINE(RDLN,[0],[without readline])
    )

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
