bin_PROGRAMS = twister
twister_SOURCES = vm.cpp Twister.cpp\
	instruction.cpp exec_context.cpp\
	error.cpp
noinst_HEADERS = vm.h instruction.h opcode.h\
	not_recognized_file_exception.h bad_file_exception.h\
	dispatch.h exec_context.h error.h global.h types.h

SUBDIRS = assembler lib
LDADD = lib/io/libtio.a
