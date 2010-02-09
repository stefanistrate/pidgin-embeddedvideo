SUBDIRS = websites

PLUGIN_CFLAGS = @GLIB_CFLAGS@ @PIDGIN_CFLAGS@ @WEBKIT_CFLAGS@ @LIBCURL_CFLAGS@
PLUGIN_LIBS = @GLIB_LIBS@ @PIDGIN_LIBS@ @WEBKIT_LIBS@ @LIBCURL_LIBS@

plugindir = @PLUGINDIR@
plugin_LTLIBRARIES = embeddedvideo.la
embeddedvideo_la_SOURCES =  \
    embeddedvideo.c         \
    videoframes.c           \
    websites.c
embeddedvideo_la_CFLAGS = $(PLUGIN_CFLAGS)
embeddedvideo_la_LIBADD = websites/libwebsites.la
embeddedvideo_la_LDFLAGS = $(PLUGIN_LIBS) -module -avoid-version -shared

