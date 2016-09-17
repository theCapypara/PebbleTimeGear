#include <pebble.h>
#include "date.h"
#include "hudfont.h"
#include "config.h"

Layer *s_date_layer;

char current_date[8];

void tg_date_update_proc(Layer *layer, GContext *ctx) {
  graphics_context_set_compositing_mode(ctx, GCompOpSet);
  tg_hudfont_drawText(ctx, 0, 0, current_date, 0);
}

void tg_date_add(Window *window) {
  if (!tg_config.showDate) return;
  Layer *window_layer = window_get_root_layer(window);

  s_date_layer = layer_create(GRect(67, 3, 77, 16));
 
  layer_set_update_proc(s_date_layer, tg_date_update_proc);
  layer_add_child(window_layer, s_date_layer);
}

void tg_date_update() {
  // Get a tm structure
  if (s_date_layer != NULL) {
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);
    strftime(current_date, 8, tg_config.dateFormat == CONFIG_DATE_MMDD ? "%m/%d" : "%d/%m", tick_time);
    layer_mark_dirty(s_date_layer);
  }
}

void tg_date_remove() {
  // Destroy Layer
  if (s_date_layer != NULL) {
    layer_destroy(s_date_layer);
  }
}