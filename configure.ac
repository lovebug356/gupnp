AC_PREREQ(2.53)
AC_INIT(gupnp, 0.13.1, http://www.gupnp.org/)
AM_INIT_AUTOMAKE()
AC_CONFIG_SRCDIR(libgupnp/gupnp.h)
AM_CONFIG_HEADER(config.h)
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CC
AC_STDC_HEADERS
AC_PROG_LIBTOOL
AC_FUNC_MMAP
AC_SYS_LARGEFILE

PKG_CHECK_MODULES(LIBGUPNP, glib-2.0 >= 2.18 \
                            gobject-2.0 >= 2.18 \
                            gmodule-2.0 \
                            gssdp-1.0 >= 0.7 \
                            libsoup-2.4 >= 2.4.1 \
                            libxml-2.0 \
                            uuid)

PKG_CHECK_MODULES(GTHREAD, gthread-2.0)

AC_ARG_WITH([context_manager],
            AS_HELP_STRING(
                        [--with-context-manager=@<:@network-manager/unix@:>@],
                        [Context Manager backend to use]),,
            [with_context_manager="unix"])

AC_MSG_CHECKING([Context Manager backend to use])
AC_MSG_RESULT([${with_context_manager}])
if test "x$with_context_manager" = "xnetwork-manager"; then
        PKG_CHECK_MODULES(DBUS_GLIB, dbus-glib-1 >= 0.76)
fi

AM_CONDITIONAL([USE_NETWORK_MANAGER],
               [test "x$with_context_manager" = "xnetwork-manager"])

# glib-genmarshal
GLIB_GENMARSHAL=`pkg-config --variable=glib_genmarshal glib-2.0`
AC_SUBST(GLIB_GENMARSHAL)

# Debugging
AC_ARG_ENABLE(debug,
	[  --enable-debug          enable debugging],,
        enable_debug=no)
if test "x$enable_debug" = "xyes"; then
        CFLAGS="$CFLAGS -g -Wall -Werror"
fi

# Gtk-doc
GTK_DOC_CHECK([1.0])

AC_OUTPUT([
Makefile
libgupnp/Makefile
examples/Makefile
tools/Makefile
tests/Makefile
doc/Makefile
doc/version.xml
gupnp-1.0.pc
gupnp-1.0-uninstalled.pc
])
