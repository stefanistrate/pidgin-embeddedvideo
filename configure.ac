# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.50])

AC_INIT([pidgin-embeddedvideo], [1.2])
AC_CANONICAL_SYSTEM
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([src/embeddedvideo.c])

# Additional argument for configure.
AC_ARG_VAR(PLUGINDIR, [the installation directory for the plugin])

# Check for programs.
AC_PROG_CC
AM_PROG_CC_C_O
CFLAGS="-g -Wall -O2"
AC_DISABLE_STATIC
AC_PROG_LIBTOOL
LIBTOOL="$LIBTOOL --silent"
AC_PROG_INSTALL
PKG_PROG_PKG_CONFIG

# Check for GLib 2.0.
PKG_CHECK_MODULES(GLIB, glib-2.0)
AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)

# Check for Pidgin.
PKG_CHECK_MODULES(PIDGIN, pidgin purple)

if test "$PLUGINDIR" = ""
then
    if test "$prefix" = "NONE"
    then
        PLUGINDIR="`pkg-config --variable=libdir pidgin`/pidgin"
    else
        PLUGINDIR="$prefix/lib/pidgin"
    fi
fi

AC_SUBST(PIDGIN_CFLAGS)
AC_SUBST(PIDGIN_LIBS)

# Check for WebKit.
PKG_CHECK_MODULES(WEBKIT, [webkit-1.0 >= 1.1.12])
AC_SUBST(WEBKIT_CFLAGS)
AC_SUBST(WEBKIT_LIBS)

# Check for libcurl.
PKG_CHECK_MODULES(LIBCURL, libcurl)
AC_SUBST(LIBCURL_CFLAGS)
AC_SUBST(LIBCURL_LIBS)

# Finish up.
AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/websites/Makefile])
AC_OUTPUT
