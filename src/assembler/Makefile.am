bin_PROGRAMS = twisterc
twisterc_SOURCES = AsmGen.cpp Parser.cpp Scanner.cpp Twisterc.cpp $(top_srcdir)/src/instruction.cpp
noinst_HEADERS = AsmGen.h Scanner.h Parser.h

INCLUDES = -I$(top_srcdir)/src

twisterc_atg = Twisterc.atg
frames_dir = /usr/share/coco-cpp

EXTRA_DIST = $(twisterc_atg)

CLEANFILES = Scanner.cpp Parser.cpp Scanner.cpp.old \
			 Parser.cpp.old Scanner.h Parser.h \
			 Scanner.h.old Parser.h.old

Scanner.cpp Parser.cpp: $(twisterc_atg)
	$(COCOCPP_BIN) -frames $(frames_dir) $(twisterc_atg)
