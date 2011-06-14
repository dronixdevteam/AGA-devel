bin_PROGRAMS = webcam_server
webcam_server_SOURCES = camera.c client.c filters.c \
                        grabber.c imgqueue.c jdatabuf.c \
			image.c unpalette.c \
			version.c watchdog.c webcam_server.c

noinst_HEADERS = camera.h client.h filters.h font_6x11.h \
		 grabber.h  imgqueue.h jdatabuf.h \
		 image.h unpalette.h \
		 version.h watchdog.h  webcam_server.h

webcam_server_LDFLAGS = -ljpeg -lpthread

dist-hook:
	mkdir $(distdir)/client
	cp -p $(srcdir)/client/*.java $(distdir)/client
	cp -p $(srcdir)/client/applet.jar $(distdir)/client
	cp -p $(srcdir)/client/*.jpg $(distdir)/client
	cp -p $(srcdir)/client/webcam.html $(distdir)/client
