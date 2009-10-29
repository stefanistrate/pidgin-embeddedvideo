PLUGIN_CFLAGS = @GLIB_CFLAGS@ @PIDGIN_CFLAGS@ @WEBKIT_CFLAGS@ @LIBCURL_CFLAGS@

WEBSITES = trilulilu-video.lo trilulilu-audio.lo vimeo.lo youtube.lo
WEBSITES_CFLAGS = $(PLUGIN_CFLAGS) -I..

CLEANFILES = $(WEBSITES) libwebsites.la

.c.lo:
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -c $< -o $@ $(WEBSITES_CFLAGS)

all: $(WEBSITES)
	$(LIBTOOL) --mode=link $(CC) $(CFLAGS) -o libwebsites.la $(LIBS) $(LDFLAGS) $(WEBSITES)

