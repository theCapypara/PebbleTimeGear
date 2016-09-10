// CONFIG
var Clay = require('pebble-clay');
var clayConfig = require('./config');
var clay = new Clay(clayConfig);
clay.registerComponent(require('./clay-image-gallery'));

// WEATHER
var weather = require('./weather.js');

Pebble.addEventListener('ready', function() {
  weather.watchLocation(function(pos) {
    weather.updateWeather(pos, function(weatherData) {
      weather.sendWeather(weatherData);
    });
  });
});