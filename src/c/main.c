#include <pebble.h>
#include "hudfont.h"
#include "background.h"
#include "time.h"
#include "timegear.h"
#include "steps.h"
#include "date.h"
#include "temperature.h"
#include "bottom.h"
#include "comm.h"
#include "config.h"

Window *s_main_window;

static void app_connection_handler(bool connected) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Pebble app %sconnected", connected ? "" : "dis");
  if (!connected) {
    vibes_double_pulse();
  }
  tg_timegear_update_connection(connected);
}

/** **/
static void main_window_load(Window *window) {
  tg_hudfont_load();
  tg_bg_add(window);
  tg_timegear_add(window);
  tg_time_add(window);
  tg_date_add(window);
  tg_steps_add(window);
  tg_temperature_add(window);
  tg_bottom_add(window);
  
  tg_time_update();
  tg_date_update();
  tg_steps_update_health();
  tg_timegear_update_battery(battery_state_service_peek());
  app_connection_handler(connection_service_peek_pebble_app_connection());
  
  tg_comm_init();
}

static void main_window_unload(Window *window) {
  tg_bg_remove();
  tg_time_remove();
  tg_date_remove();
  tg_timegear_remove();
  tg_steps_remove();
  tg_temperature_remove();
  tg_bottom_remove();
  
  tg_hudfont_free();
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  tg_time_update();
  tg_steps_update_health();
  //tg_bg_update(); doesn't work right now
  if (units_changed & DAY_UNIT) {
    tg_date_update();
  }
}

static void battery_handler(BatteryChargeState charge) {
  tg_timegear_update_battery(charge);
}

static void init() {
  tg_config_init();
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