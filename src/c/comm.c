#include <pebble.h>
#include "comm.h"
#include "temperature.h"
#include "bottom.h"
#include "config.h"

// Largest expected inbox and outbox message sizes
const uint32_t inbox_size = 400;
const uint32_t outbox_size = 0;

void tg_comm_received(DictionaryIterator *iter, void *context) {
  // Temperature
  Tuple *temperature_tuple = dict_find(iter, MESSAGE_KEY_Temperature);
  if(temperature_tuple) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Rec Temp");
    tg_temperature_update(temperature_tuple->value->cstring);
  }
  // WeatherDescription
  Tuple *weather_tuple = dict_find(iter, MESSAGE_KEY_WeatherDescription);
  if(weather_tuple) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Rec WeatherDescription");
    tg_bottom_update_weather(weather_tuple->value->cstring);
  }
  tg_config_update(iter, context);
}

void tg_comm_init() {
  app_message_open(inbox_size, outbox_size);
  app_message_register_inbox_received(tg_comm_received);
};