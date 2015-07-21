#!/usr/bin/ruby

require 'json'

if Dir.exist? 'resources/images/' and File.file? 'appinfo.json'
  json = JSON.parse(File.read('appinfo.json'))
  if !(json.respond_to? :resources)
    json[:resources] = {media: []}
  else
    json[:resources][:media] = []
  end
  formats = ['.png', '.jpg', '.jpeg', 'bmp']
  platformFiles = [];
  Dir.foreach('resources/images') do |filename|
    ext = File.extname(filename);
    if filename.include? '~'
      filename = filename.sub(/(\w)~.+/, '\1') + ext
    end
    if platformFiles.include? filename
      next
    end
    platformFiles << filename
    if formats.include? ext
      json['resources']['media'] << {
          type: ext[1..-1],
          file: "images/#{filename}",
          name: "IMAGE_#{filename[0..-(ext.length + 1)].gsub(/\W/i, '_').upcase}"
      }
    end
  end
  File.write('appinfo.json', JSON.pretty_generate(json))
end