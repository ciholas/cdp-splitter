# Ciholas, Inc. - www.ciholas.com
# Licensed under: creativecommons.org/licenses/by/4.0
Dir.glob('**/*.rake').each{|r| import r}

# rake depends on rubygem rake
require 'rubygems'

SRC_ROOT_DIR = 'src'
RAKE_CONFIG_FILES = [ '.rakerc', 'rake.conf' ]

#rake setup
verbose(false)

#helper methods
def dirfor(file)
  mkdir_p file.pathmap("%d")
end
def src_config_option(name,options={})
  if options[:file_list]
    rv = []
    options[:concat] = true
  elsif options[:concat]
    rv = ""
  end
  RAKE_CONFIG_FILES.each do |rcf|
    if File.exist?(rcf)
      File.open(rcf, 'r').each_line do |line|
        if line =~ /^#{name}:.+/
          config = line.sub(/^[^:]*:/,'').strip.chomp+" "
          if options[:increment]
            config = config.to_i
            if options[:increment].include?(config)
              config += 1
              if config > options[:increment].end
                config = options[:increment].begin
              end
              `sed -i 's/^#{name}:.*$/#{name}:#{config.to_s}/g' #{rcf}`
            end
          elsif options[:file_list]
            fl = FileList[]
            config.split(';').each{ |rs| fl << Regexp.new(rs.strip) }
            config = fl
          end
          if options[:concat]
            rv += config
          else
            config.strip! if config.kind_of?(String)
            return config
          end
        end
      end
    end
  end
  if options[:concat] and rv != ""
    rv.strip! if rv.kind_of?(String)
    return rv
  elsif options[:force]
    `echo #{name}:#{options[:force]} >> #{RAKE_CONFIG_FILES.first}`
    return options[:force]
  end
  return options[:default]
end

#overwrite display options
class Display
  if ENV["TERM"] == "dumb"
    RED=""
    GREEN=""
    BLANK=""
    YELLOW=""
    BLUE=""
  else
    RED="\033[1;31m"
    GREEN="\033[1;32m"
    BLANK="\033[0m"
    YELLOW="\033[1;33m"
    BLUE="\033[1;34m"
  end
  @@output = []
  def initialize(string, dont_display=false)
    display(string) unless dont_display
    @@output << string
  end
  def self.summarize
    if @@output.empty?
      puts "#{GREEN}Nothing to summarize#{BLANK}"
    else
      print "#{BLUE}Output summary - #{BLANK}"
      puts "#{YELLOW}#{(@@output.to_s.split(/warning/i).size - 1).to_s} warnings#{BLANK}"
      @@output.each { |o| puts o.to_s }
      @@output = []
    end
  end
  private
  def display(s)
    s.gsub!(/(warning)/i, "#{YELLOW}\\1#{BLANK}")
    s.gsub!(/(error)/i, "#{RED}\\1#{BLANK}")
    s.gsub!(/(ld returned.*exit status)/i, "#{RED}\\1#{BLANK}")
    puts s
  end
end
require 'open4'
$super_verbose = false
module FileUtils
  def rake_system(*cmd)
    pid, stdin, stdout, stderr = Open4::popen4(*cmd)
    sto = ""
    [stdout,stderr].each do |io|
      ns = ''
      until ns.nil?
        begin
          sto += ns
          ns = io.read_nonblock(1)
          if $super_verbose
            print ns
            STDOUT.flush
          end
        rescue Errno::EAGAIN
          ns = ''
        rescue EOFError
          ns = nil
        end
      end
    end
    Display.new(sto, $super_verbose) if sto != ""
    if Process::waitpid2(pid)[1].to_i != 0
      false
    else
      true
    end
  end
end
