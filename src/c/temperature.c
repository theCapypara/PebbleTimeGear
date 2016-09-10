#include <pebble.h>
#include <stdio.h>
#include "temperature.h"
#include "hudfont.h"
#include "constants.h"

Layer *s_temperature_layer;

char current_temperature[20];

void tg_temperature_update_proc(Layer *layer, GContext *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Redraw Temp %s", current_temperature);
  if (current_temperature == NULL) return;
  graphics_context_set_compositing_mode(ctx, GCompOpSet);
  tg_hudfont_drawText(ctx, 0, 0, current_temperature, 0);
}


void tg_temperature_add(Window *window) {
  // Init last temperature
  if (persist_exists(PERSIST_TMP_TEMPERATURE)) {
    persist_read_string(PERSIST_TMP_TEMPERATURE, current_temperature, sizeof current_temperature);
  }
  
  Layer *window_layer = window_get_root_layer(window);

  s_temperature_layer = layer_create(GRect(2, 3, 66, 16));
 
  layer_set_update_proc(s_temperature_layer, tg_temperature_update_proc);
  layer_add_child(window_layer, s_temperature_layer);
}

void tg_temperature_update(char *temperature) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Update Temp %s", temperature);
  if (current_temperature == NULL || strcmp(temperature, current_temperature) != 0) {
    
    strncpy(current_temperature, temperature, sizeof current_temperature - 1);
    persist_write_string(PERSIST_TMP_TEMPERATURE, current_temperature);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Set Temp %s", current_temperature);
    layer_mark_dirty(s_temperature_layer);
  }
}

void tg_temperature_remove() {
  layer_destroy(s_temperature_layer);
}