AM_CPPFLAGS = \
    -I$(top_srcdir)/src

SUBDIRS = \
    asn-one-objects \
    common \
    ldap \
    network

bin_PROGRAMS = ldap-server

ldap_server_SOURCES = \
    LdapServer.cpp

ldap_server_LDADD = \
    $(top_builddir)/src/network/libnetwork.la \
    $(top_builddir)/src/ldap/libldap.la \
    $(top_builddir)/src/asn-one-objects/libasn-one-objects.la \
    $(top_builddir)/src/common/libcommon.la

MAINTAINERCLEANFILES = \
    Config.h.in \
    Makefile.in
