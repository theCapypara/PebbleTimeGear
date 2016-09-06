#include <pebble.h>
#include "background.h"
#include "time.h"
#include "timegear.h"
#include "steps.h"

Window *s_main_window;

/** **/
static void main_window_load(Window *window) {
  tg_bg_add(window);
  tg_timegear_add(window);
  tg_time_add(window);
  tg_steps_add(window);
  
  tg_time_update();
  tg_steps_update_health();
  tg_timegear_update_battery(battery_state_service_peek());
  tg_timegear_update_connection(connection_service_peek_pebble_app_connection());
}

static void main_window_unload(Window *window) {
  tg_bg_remove();
  tg_time_remove();
  tg_timegear_remove();
  tg_steps_remove();
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  tg_time_update();
  tg_steps_update_health();
}

static void battery_handler(BatteryChargeState charge) {
  tg_timegear_update_battery(charge);
}

static void app_connection_handler(bool connected) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Pebble app %sconnected", connected ? "" : "dis");
  if (!connected) {
    vibes_double_pulse();
  }
  tg_timegear_update_connection(connected);
}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  // Register Battery
  battery_state_service_subscribe(battery_handler);
  
  // Register connection
  connection_service_subscribe((ConnectionHandlers) {
    .pebble_app_connection_handler = app_connection_handler
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}

/** **/

/*
static void layer_update_proc(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorRed);
  graphics_fill_rect(ctx, GRect(28,25,2,16),0,0);
}

void handle_init(void) {
  my_window = window_create();
  GRect main_bounds = layer_get_bounds(window_get_root_layer(my_window));
  
  s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG_1);
  s_bitmap_layer = bitmap_layer_create(main_bounds);
  
  bitmap_layer_set_compositing_mode(s_bitmap_layer, GCompOpSet);
  bitmap_layer_set_bitmap(s_bitmap_layer, s_bitmap);
  
  s_text_layer = text_layer_create(GRect(28, 21, 89, 23));
  font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PMD_21));
  
  text_layer_set_text(s_text_layer, text);
  text_layer_set_font(s_text_layer, font);
  text_layer_set_text_color(s_text_layer, GColorWhite);
  text_layer_set_background_color(s_text_layer, GColorBlack);
  text_layer_set_overflow_mode(s_text_layer, GTextOverflowModeWordWrap);
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
  
  debug_layer = layer_create(main_bounds);
  layer_set_update_proc(debug_layer, layer_update_proc);

  
  layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(s_bitmap_layer));
  layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(s_text_layer));
  layer_add_child(window_get_root_layer(my_window), debug_layer);
  
  window_stack_push(my_window, true);
}

void handle_deinit(void) {
  gbitmap_destroy(s_bitmap);
  bitmap_layer_destroy(s_bitmap_layer);
  text_layer_destroy(s_text_layer);
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
*/