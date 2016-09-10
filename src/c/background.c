#include <pebble.h>
#include "background.h"

BitmapLayer *s_background_layer;
GBitmap *s_background;

void tg_bg_add(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  
  GRect main_bounds = layer_get_bounds(window_layer);
  
  s_background = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG_2);
  s_background_layer = bitmap_layer_create(main_bounds);
  
  bitmap_layer_set_bitmap(s_background_layer, s_background);

  layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));
}

void tg_bg_remove() {
  bitmap_layer_destroy(s_background_layer);
  gbitmap_destroy(s_background);
}