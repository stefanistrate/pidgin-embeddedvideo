PLUGIN_CFLAGS = @GLIB_CFLAGS@ @PIDGIN_CFLAGS@ @WEBKIT_CFLAGS@ @LIBCURL_CFLAGS@

noinst_LTLIBRARIES = libwebsites.la
libwebsites_la_SOURCES =    \
    collegehumor.c          \
    dailymotion.c           \
    metacafe.c              \
    myspace-video.c         \
    trilulilu-audio.c       \
    trilulilu-image.c       \
    trilulilu-video.c       \
    vimeo.c                 \
    youtube.c               \
    youtube-short.c
libwebsites_la_CFLAGS = $(PLUGIN_CFLAGS) -I..

