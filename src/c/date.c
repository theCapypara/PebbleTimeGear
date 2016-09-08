#include <pebble.h>
#include "date.h"
#include "hudfont.h"

Layer *s_date_layer;

char current_date[8];

void tg_date_update_proc(Layer *layer, GContext *ctx) {
  graphics_context_set_compositing_mode(ctx, GCompOpSet);
  tg_hudfont_drawText(ctx, 0, 0, current_date, 0);
}

void tg_date_add(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  s_date_layer = layer_create(GRect(67, 4, 77, 16));
 
  layer_set_update_proc(s_date_layer, tg_date_update_proc);
  layer_add_child(window_layer, s_date_layer);
}

void tg_date_update() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  strftime(current_date, 8, "%d/%m", tick_time);
  layer_mark_dirty(s_date_layer);
}

void tg_date_remove() {
  // Destroy TextLayer
  layer_destroy(s_date_layer);
}