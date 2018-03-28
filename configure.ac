#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([LSBSteg], [1.0], [aiden.woodruff@gmail.com])
AC_CONFIG_SRCDIR([lsb.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset strtol])

AC_CONFIG_FILES([Makefile])
AM_INIT_AUTOMAKE
AC_OUTPUT
