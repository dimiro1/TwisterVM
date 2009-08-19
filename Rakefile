require 'rake/clean'
require "rakepp"

directory "obj/src"
directory "obj/src/assembler"

task :clean => [] do
  sh "rm -rf obj"
  sh "rm -f bin/*"
end

VMSRC = FileList[ 'src/*.cpp' ]
VMOBJ = VMSRC.sub( /\.cpp$/, '.o' ).sub( /^src\//, 'obj/src/' )
VMSRC.freeze
VMOBJ.freeze
VMSRC_DIR = 'src'

ASMSRC = FileList[ 'src/assembler/*.cpp', "src/instruction.cpp", "src/exec_context.cpp" ]
ASMOBJ = ASMSRC.sub( /\.cpp$/, '.o' )\
  .sub( /^src\/assembler\//, 'obj/src/assembler/' )\
  .sub( /^src\//, 'obj/src/' )
ASMSRC.freeze
ASMOBJ.freeze
ASMSRC_DIR = 'src/assembler'

# Return dependencies for an object file.
def obj_dep(o)
  deps = []
  inc_dirs = [ VMSRC_DIR, ASMSRC_DIR ]
  cpp = o.sub(/\.o$/,'.cpp') \
    .sub(/^obj\/src\//, 'src/')\
    .sub(/^obj\/src\/assembler\//, 'src/assembler/')
  headers = cpp_headers( cpp, inc_dirs )
  deps << cpp
  deps << headers
  return deps
end

file "bin/twister" => [ :compile ] do |t|
  sh "g++ -o bin/twister #{VMOBJ}"
end

file "bin/twisterc" => [ :compile ] do |t|
  sh "g++ -o bin/twisterc #{ASMOBJ}"
end

rule '.o' => [ proc { |o| obj_dep( o ) } ] do |t|
  sh %{g++ -c -g -o #{t.name} #{t.source}}
end

task :default => [ :build ]

desc "Compile all source files into objects"
task :compile => [ "obj/src" ] + VMOBJ + ASMOBJ

desc "Build the main executable"
task :build => [ "bin/twister", "bin/twisterc" ]
