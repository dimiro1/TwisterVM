SUBDIRS = src

EXTRA_DIST = examples $(DIST_ALPHA)

if MAINTAINER_MODE
  CFLAGS = -g -I.
else
  CFLAGS = @CFLAGS@ -I.
endif

