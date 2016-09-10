var weather = require('./weather.js');

Pebble.addEventListener('ready', function() {
  weather.watchLocation(function(pos) {
    weather.updateWeather(pos, function(weatherData) {
      weather.sendWeather(weatherData);
    });
  });
});