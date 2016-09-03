#include <pebble.h>

Window *my_window;
static GBitmap *s_bitmap;
static BitmapLayer *s_bitmap_layer;

void handle_init(void) {
  my_window = window_create();
  s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TEST);
  s_bitmap_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_compositing_mode(s_bitmap_layer, GCompOpSet);
  bitmap_layer_set_bitmap(s_bitmap_layer, s_bitmap);
  layer_add_child(window_get_root_layer(my_window), 
                                      bitmap_layer_get_layer(s_bitmap_layer));
  window_stack_push(my_window, true);
}

void handle_deinit(void) {
  gbitmap_destroy(s_bitmap);
  bitmap_layer_destroy(s_bitmap_layer);
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
