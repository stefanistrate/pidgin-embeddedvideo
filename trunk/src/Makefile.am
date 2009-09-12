PLUGIN_CFLAGS = @GLIB_CFLAGS@ @LIBXML_CFLAGS@ @PIDGIN_CFLAGS@ @WEBKIT_CFLAGS@
PLUGIN_LIBS = @GLIB_LIBS@ @LIBXML_LIBS@ @PIDGIN_LIBS@ @WEBKIT_LIBS@

plugindir = @PLUGINDIR@
plugin_DATA = embeddedvideo.so

OBJECTS = videoframes.lo websites.lo
CLEANFILES = embeddedvideo.so $(OBJECTS)

.c.lo:
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -c $< -o $@ $(PLUGIN_CFLAGS)

embeddedvideo.so: embeddedvideo.c $(OBJECTS)
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -c embeddedvideo.c -o tmp$@.lo $(PLUGIN_CFLAGS)
	$(LIBTOOL) --mode=link    $(CC) $(CFLAGS) -o libtmp$@.la -rpath $(plugindir) tmp$@.lo $(LIBS) $(LDFLAGS) $(OBJECTS) -module -avoid-version $(PLUGIN_LIBS)
	@rm -f tmp$@.lo tmp$@.o libtmp$@.la
	@cp .libs/libtmp$@.so* $@
	@rm -f .libs/libtmp$@.* .libs/tmp$@.*
