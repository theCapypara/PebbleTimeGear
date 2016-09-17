// Manages the config store for js

module.exports = {
  configDefaults: {
    CfgApiKey: '',
    CfgTemperatureUnit: 0
  },
  T_FAHRENHEIT: 0,
  T_CELCIUS:    1,
  get: function(key) {
    var loEntry = JSON.parse(localStorage.getItem('clay-settings'));
    if (loEntry && typeof loEntry == 'object') {
      var data = loEntry[key];
      if (data) { return data; }
    }
    return this.configDefaults[key];
  }
};