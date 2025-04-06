// CONFIG
var Clay = require('pebble-clay');
var clayConfig = require('./configPage');
var clay = new Clay(clayConfig);

// WEATHER
var weather = require('./weather.js');

Pebble.addEventListener('ready', function() {
  weather.watchLocation(function(pos) {
    weather.updateWeather(pos, function(weatherData) {
      weather.sendWeather(weatherData);
    });
  });
});

// Override events
Pebble.addEventListener('showConfiguration', function(e) {
  Pebble.openURL(clay.generateUrl());
});
