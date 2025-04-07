#include <pebble.h>
#include "constants.h"
#include "date.h"
#include "hudfont.h"
#include "config.h"

Layer *s_date_layer;

#if defined(PBL_RECT)
char current_date[8];
#elif defined(PBL_ROUND)
char current_date_m[3];
char current_date_d[3];
#endif

void tg_date_update_proc(Layer *layer, GContext *ctx) {
  graphics_context_set_compositing_mode(ctx, GCompOpSet);
#if defined(PBL_RECT)
  tg_hudfont_drawText(ctx, 0, 0, current_date, 0);
#elif defined(PBL_ROUND)
  tg_hudfont_drawText(ctx, 0, 0, current_date_m, 0);
  tg_hudfont_drawText(ctx, 10, 17, "/\0", 0);
  tg_hudfont_drawText(ctx, 0, 34, current_date_d, 0);
#endif
}

void tg_date_add(Window *window) {
  if (!tg_config.showDate) return;
  Layer *window_layer = window_get_root_layer(window);

#if defined(PBL_RECT)
  s_date_layer = layer_create(H_RIG_V_TOP_RECT(0, 3, 77, 16));
#elif defined(PBL_ROUND)
  s_date_layer = layer_create(H_RIG_V_MID_RECT(-6, 1, 32, 54));
#endif
 
  layer_set_update_proc(s_date_layer, tg_date_update_proc);
  layer_add_child(window_layer, s_date_layer);
}

void tg_date_update() {
  // Get a tm structure
  if (s_date_layer != NULL) {
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);
#if defined(PBL_RECT)
  strftime(current_date, 8, tg_config.dateFormat == CONFIG_DATE_MMDD ? "%m/%d" : "%d/%m", tick_time);
#elif defined(PBL_ROUND)
  strftime(current_date_m, 3, tg_config.dateFormat == CONFIG_DATE_MMDD ? "%m" : "%d", tick_time);
  strftime(current_date_d, 3, tg_config.dateFormat == CONFIG_DATE_MMDD ? "%d" : "%m", tick_time);
#endif
    layer_mark_dirty(s_date_layer);
  }
}

void tg_date_remove() {
  // Destroy Layer
  if (s_date_layer != NULL) {
    layer_destroy(s_date_layer);
  }
}