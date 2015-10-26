require 'rake/clean'
require "rakepp"

directory "obj/src"
directory "obj/src/assembler"

task :clean => [] do
  sh "rm -rf obj"
  sh "rm -f bin/*"
  sh "rm -f examples/*.twc"
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

desc "Generate core files."
task :generate_core do
  sh "ruby tools/opcode_gen.rb -c goto src/instructions.rb"
  sh "mv core.h core.cpp src/"
end

desc "Compile all example files."
task :examples do
  sources = FileList["examples/*.tw"]
  sources.each do |s|
    puts "COMPILING: #{s}"
    sh "bin/twisterc #{s} -o #{s.slice 0...s.index(".tw")}.twc"
    puts
  end
end

rule '.o' => [ proc { |o| obj_dep( o ) } ] do |t|
  sh %{g++ -c -g -o #{t.name} #{t.source}}
end

task :default => [ :build ]

desc "Compile all source files into objects"
task :compile => [ "obj/src" ] + VMOBJ + ASMOBJ

desc "Build the main executable"
task :build => [ :generate_core, "bin/twister", "bin/twisterc" ]
