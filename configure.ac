#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([ldap-server],[0.1.0],[felix.mellmann@gmail.com])
AC_CONFIG_SRCDIR([src/LdapServer.cpp])
AC_CONFIG_HEADERS([src/Config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE

# Checks for programs.
AM_PROG_AR
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_14()

LT_INIT

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/asn-one-objects/Makefile
    src/common/Makefile
    src/ldap/Makefile
    src/network/Makefile
])
AC_OUTPUT
