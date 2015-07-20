#!/usr/bin/ruby

require 'json'

if Dir.exist? 'resources/images/'
  json = JSON.parse(File.read('appinfo.json'))
  json['resources']['media'] = []
  formats = ['.png', '.jpg', '.jpeg', 'bmp']
  Dir.foreach('resources/images') do |filename|
    ext = File.extname(filename);
    if formats.include? ext
      json['resources']['media'] << {type: ext[1..-1], file: "images/#{filename}", name: "IMAGE_#{filename[0..-(ext.length + 1)].upcase}"}
    end
  end
  File.write('appinfo.json', JSON.pretty_generate(json))
end