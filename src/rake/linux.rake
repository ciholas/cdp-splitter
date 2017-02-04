# Ciholas, Inc. - www.ciholas.com
# Licensed under: creativecommons.org/licenses/by/4.0
def sh_runner(*cmds)
    sh cmds.to_a.join(" && ")
end

### constants
class Linux
  BINARY_NAME = 'cdp-splitter'

  OUT_DIR = 'output'
  OBJS_DIR = ".objects/"
  OUTPUT = "#{OUT_DIR}/#{BINARY_NAME}"

  SRC_FILES = FileList["src/**/*.c"]
  OBJ_FILES = SRC_FILES.ext('.o').map { |sf| File.join(".objects",sf) }

  FLAGS="-Isrc -Isrc/include -lm -pthread"
  CFLAGS= "-m32"
end

### rules
#.c to .o
rule /.*\.o/ => proc { |t| t.ext('.c').sub(Linux::OBJS_DIR, '') } do |t|
  sh_runner("/bin/echo '#{Display::BLUE}Compiling#{Display::BLANK} #{t.name} #{Display::BLUE}from#{Display::BLANK} #{t.source}'",
            "mkdir -p #{File.dirname(t.name)}",
            "gcc #{Linux::CFLAGS} -o #{t.name} -c #{t.sources.join(" ")} #{Linux::FLAGS}")
end

#.o to binary
rule Linux::OUTPUT => Linux::OBJ_FILES do |t|
  sh_runner("/bin/echo '#{Display::BLUE}Finalizing binary#{Display::BLANK}'",
            "mkdir -p #{Linux::OUT_DIR}",
            "gcc #{Linux::CFLAGS} -o #{Linux::OUTPUT} #{t.sources.join(" ")} #{Linux::FLAGS}")
end

### tasks
desc 'builds the source, disregarding if nothing has changed'
task source: Linux::OUTPUT

desc 'cleans the output folder'
task :clean do
  sh "rm -rf #{Linux::OUT_DIR} #{Linux::OBJS_DIR}"
end

task default: :source
