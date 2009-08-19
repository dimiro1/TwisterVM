require "optparse"

class Generator
  @@opcodes = Array.new
  @@options = Hash.new
  @@using_block = String.new

  def self.declare_options(options = {})
    @@options[:core] = options[:core].to_sym || :switch
  end
  
  def self.declare_opcode(opcode)
    opcode.code += next_intruction
    @@opcodes << opcode
  end

  def self.declare_using_block(using)
    @@using_block = using
  end
  
  def self.generate_header
    File.open("core.h", "w") do |file|
      file.puts <<-END
     // Gerado por tools/opcode_gen.rb
     // modifique instructions.rb
    #ifndef _OPCODE_H_
    #define _OPCODE_H_
    #{ @@options[:core] == :goto ? "#define HAVE_COMPUTED_GOTO" : ""}
    enum Opcode { #{@@opcodes.collect {|o| "OP_#{o.name.to_s.upcase}," }} };

    static const char *
    mneumonic[] = {
      #{@@opcodes.collect {|o| "\"#{o.name.to_s}\"," }}
    };
    #endif
    END
    end
  end
  

  def self.generate(file_name)
    generate_header
    File.open(file_name, "w") do |file|
    file.puts <<-END
     // Gerado por tools/opcode_gen.rb
     // modifique instructions.rb
     #include "VM.h"
       void TwisterVM::dispatch ()
       {
         #{@@using_block}
     END

    file.puts begin_dispatch
    @@opcodes.each do |o|
      if @@options[:core] == :goto
        file.puts "LOP_#{o.name.to_s.upcase}: {"
        file.puts o.code
      elsif @@options[:core] == :switch
        file.puts "case OP_#{o.name.to_s.upcase}: {"
        file.puts o.code
        file.puts "break;"
      end
      file.puts "}"
    end
    file.puts end_dispatch
    file.puts "}"
    end
  end

  def self.begin_dispatch
    if @@options[:core] == :goto
      <<-CODE
      static const void
      *label_targets[] = {
	     #{@@opcodes.collect {|o| "\"#{o.name}\"," }}
      };
      #{next_intruction}
      CODE
    elsif @@options[:core] == :switch
      <<-CODE
      while (true)	{
        executing = current_context->code_section[current_context->pc];
        switch (executing.opcode)
	     {
      CODE
    end
  end

  def self.end_dispatch
    if @@options[:core] == :goto
      ""
    elsif @@options[:core] == :switch
      "}}"
    end
  end
  

  def self.next_intruction
    if @@options[:core] == :goto
      <<-CODE
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
      CODE
    elsif @@options[:core] == :switch
      ""
    end
  end

end

class Opcode
  attr_accessor :code, :name
  def initialize(name, code)
    @name = name
    @code = code
  end
end

def using
  Generator.declare_using_block(yield)
end

def opcode(name)
  opcode = Opcode.new(name, yield)
  Generator.declare_opcode(opcode)
end

if __FILE__ == $PROGRAM_NAME
  opts = OptionParser.new
  opts.on("-c", "--core CORE", String) { |core| Generator.declare_options :core => core }
  file = opts.parse(ARGV)
  load file.to_s
  Generator.generate("core.cpp")
end
