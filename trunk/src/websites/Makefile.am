PLUGIN_CFLAGS = @GLIB_CFLAGS@ @PIDGIN_CFLAGS@ @WEBKIT_CFLAGS@ @LIBCURL_CFLAGS@

WEBSITES =  collegehumor.lo \
            dailymotion.lo \
            trilulilu-audio.lo \
            trilulilu-image.lo \
            trilulilu-video.lo \
            vimeo.lo \
            youtube.lo
WEBSITES_CFLAGS = $(PLUGIN_CFLAGS) -I..

CLEANFILES = $(WEBSITES) libwebsites.la

.c.lo:
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -c $< -o $@ $(WEBSITES_CFLAGS)

all: $(WEBSITES)
	$(LIBTOOL) --mode=link $(CC) $(CFLAGS) -o libwebsites.la $(LIBS) $(LDFLAGS) $(WEBSITES)

