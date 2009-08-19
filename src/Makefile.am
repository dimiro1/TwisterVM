lib_LIBRARIES = libtwister.a
libtwister_a_SOURCES = VM.cpp instruction.cpp\
		exec_context.cpp error.cpp IO.cpp core.cpp

include_HEADERS = VM.h instruction.h\
	not_recognized_file_exception.h bad_file_exception.h\
	exec_context.h error.h global.h types.h IO.h Twister.h

core.h core.cpp: instructions.rb
	ruby ${top_srcdir}/tools/opcode_gen.rb -c goto instructions.rb

SUBDIRS = interpreter assembler