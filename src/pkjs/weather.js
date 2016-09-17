// Weather and Location related functions

var config = require('./config');

module.exports = {
  watchLocation: function(callback) {
    function success(pos) {
      console.log('Location changed!');
      console.log('lat= ' + pos.coords.latitude + ' lon= ' + pos.coords.longitude);
      callback(pos);
    }
  
    function error(err) {
      console.log('location error (' + err.code + '): ' + err.message);
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
    var url = 'https://api.forecast.io/forecast/'+config.get('CfgApiKey')+'/'+pos.coords.latitude+','+pos.coords.longitude;
    console.log("Requesting with API Key "+config.get('CfgApiKey'));
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
    var temperature = weather.currently.temperature;
    var celcius = (temperature - 32) * 5/9;
    
    var weatherPMD = "Unknown";
    switch (weather.currently.icon) {
      case "clear-day":
      case "clear-night":
      case "clear":
        weatherPMD = temperature < 86 || weather.currently.icon == "clear-night" ? "Clear" : "Sunny";
        break;
      case "rain":
        weatherPMD = "Rain";
        break;
      case "snow":
      case "sleet":
        weatherPMD = "Snow";
        break;
      case "wind":
        weatherPMD = "Wind";
        break;
      case "fog":
        weatherPMD = "Fog";
        break;
      case "cloudy":
      case "partly-cloudy-day":
      case "partly-cloudy-night":
        weatherPMD = "Cloudy";
        break;
      case "hail":
        weatherPMD = "Hail";
        break;
      case "thunderstorm":
        weatherPMD = "Thunderstorm";
        break;
      case "tornado":
        weatherPMD = "Tornado";
        break;
    }
    
    var dict = {
      'Temperature': config.get('CfgTemperatureUnit') == config.T_FAHRENHEIT ? Math.round(temperature) + 'f' : Math.round(celcius) + 'C',
      'WeatherDescription': weatherPMD
    };
    
    console.log(celcius);
    console.log(weatherPMD);
    
    Pebble.sendAppMessage(dict, function() {
      console.log('Message sent successfully: ' + JSON.stringify(dict));
    }, function(e) {
      console.log('Message failed: ' + JSON.stringify(e));
    });
  }
};