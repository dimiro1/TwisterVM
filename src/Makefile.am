lib_LIBRARIES = libtwister.a
libtwister_a_SOURCES = VM.cpp instruction.cpp\
		exec_context.cpp error.cpp IO.cpp

include_HEADERS = VM.h instruction.h opcode.h\
	not_recognized_file_exception.h bad_file_exception.h\
	dispatch.h exec_context.h error.h global.h types.h IO.h Twister.h

bin_PROGRAMS = twister
twister_SOURCES = Main.cpp
noinst_HEADERS = VM.h instruction.h opcode.h\
	not_recognized_file_exception.h bad_file_exception.h\
	dispatch.h exec_context.h error.h global.h types.h IO.h

SUBDIRS = assembler
LDADD = libtwister.a
