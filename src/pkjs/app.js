// CONFIG
var Clay = require('pebble-clay');
var clayConfig = require('./configPage');
var messageKeys = require('build/js/message_keys.json');
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

Pebble.addEventListener('webviewclosed', function(e) {
  if (e && !e.response) {
    return;
  }

  // Get the keys and values from each config item
  var dict = clay.getSettings(e.response);
  // Convert to ints
  dict[messageKeys.CfgDateFormat] = parseInt(dict[messageKeys.CfgDateFormat]);
  dict[messageKeys.CfgBottomDisplay] = parseInt(dict[messageKeys.CfgBottomDisplay]);
  dict[messageKeys.CfgQuickView] = parseInt(dict[messageKeys.CfgQuickView]);
  console.log(JSON.stringify(dict));

  // Send settings values to watch side
  Pebble.sendAppMessage(dict, function(e) {
    console.log('Sent config data to Pebble');
  }, function(e) {
    console.log('Failed to send config data!');
    console.log(JSON.stringify(e));
  });
});