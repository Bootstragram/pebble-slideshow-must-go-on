# Pebble Slideshow Must Go On

![Slideshow Must Go On Live At Wembley 86](https://raw.githubusercontent.com/wiki/Bootstragram/pebble-slideshow-must-go-on/assets/logo.jpg)

Test your designs on the watch to have a glimpse of how they look like on your wrist.

## Usage

Just put your images into the `resources/images` and build the watchapp with the pebble tool.
Do not forget to rebuild the watchapp each time you modify the `resources/images` folder.

## Dependencies

Pebble Image Viewer use a ruby script to scan your resources folder and update your appinfo.json.
If `pebble build` doesn't work properly, tap this following lines in a terminal :

```
# For mac users
brew install ruby; gem install json
# For unix users
sudo apt-get install ruby; gem install json
     
```

## License
Copyright (c) 2015 Bootstragram  
Licensed under the MIT license.