// Weather and Location related functions

var config = require('./config');

function buildUri(url, params) {
  var char = '?';
  for (var prop in params) {
    if (Object.prototype.hasOwnProperty.call(params, prop)) {
      url += char + prop + '=' + encodeURIComponent(params[prop]);
      char = '&';
    }
  }
  return url;
}

module.exports = {
  watchLocation: function(callback) {
    function success(pos) {
      console.log('Location changed!');
      console.log('lat= ' + pos.coords.latitude + ' lon= ' + pos.coords.longitude);
      callback(pos);
    }
  
    function error(err) {
      if (err != null) {
        console.log('location error (' + err.code + '): ' + err.message);
      } else {
        console.log('location error (unknown - emulator?)');
      }
    }
    
    // Instead of watching position using watchPosition, we pull every 10 minutes to reduces api calls
    // TODO: Configurable
    var options = {
      enableHighAccuracy: false,
      maximumAge: 0,
      timeout: 5000
    };
    // Request current position
    navigator.geolocation.getCurrentPosition(success, error, options);
    setTimeout(function(){this.watchLocation(callback);}, 600000);
  },
  
  updateWeather: function(pos, callback) {
    var params = {
      latitude: pos.coords.latitude.toString(),
      longitude: pos.coords.longitude.toString(),
      current: "temperature_2m,weather_code,is_day",
      timezone: "auto",
    };

    if (config.get('CfgTemperatureUnit') === config.T_FAHRENHEIT) {
      params.temperature_unit = "fahrenheit";
    }

    var url = buildUri('http://api.open-meteo.com/v1/forecast', params);
    console.log("Requesting: " + url);
    var request = new XMLHttpRequest();
    
    request.onload = function() {
      var data = JSON.parse(this.responseText);
      callback(data);
    };
    
    // Send the request
    request.open('GET', url);
    request.send();
  },
  
  sendWeather: function(weather, callback) {
    var temperature = weather.current.temperature_2m;
    var temperatureUnit = weather.current_units.temperature_2m.slice(-1);
    var isCelsius = temperatureUnit.toUpperCase() === "C";
    var temperatureAsFahrenheit = isCelsius ? (temperature - 32) * 5/9 : temperature;
    
    var weatherPMD = "Unknown";
    switch (weather.current.weather_code) {
      case 0:
      case 1:
        weatherPMD = temperatureAsFahrenheit < 86 || !weather.current.is_day ? "Clear" : "Sunny";
        break;
      case 2:
      case 3:
        weatherPMD = "Cloudy";
        break;
      case 45:
      case 48:
        weatherPMD = "Fog";
        break;
      case 51:
      case 53:
      case 55:
        weatherPMD = "Drizzle";
        break;
      case 56:
      case 57:
        weatherPMD = "Freezing Drizzle";
        break;
      case 61:
      case 63:
      case 80:
      case 81:
        weatherPMD = "Rain";
        break;
      case 65:
      case 82:
        weatherPMD = "Heavy Rain";
        break;
      case 66:
      case 67:
        weatherPMD = "Freezing Rain";
        break;
      case 71:
      case 73:
      case 77:
      case 85:
        weatherPMD = "Snow";
        break;
      case 75:
      case 86:
        weatherPMD = "Heavy Snow";
        break;
      case 95:
      case 96:
      case 99:
        weatherPMD = "Thunderstorm";
        break;
    }
    
    var dict = {
      'Temperature': Math.round(temperature) + temperatureUnit,
      'WeatherDescription': weatherPMD
    };

    console.log("updating weather");
    console.log(dict);
    
    Pebble.sendAppMessage(dict, function() {
      console.log('Message sent successfully: ' + JSON.stringify(dict));
    }, function(e) {
      console.log('Message failed: ' + JSON.stringify(e));
    });
  }
};