#include <pebble.h>
#include "constants.h"
#include "time.h"
#include "textbox.h"

TextLayer *s_time_layer;
Textbox *s_textbox_time;

void tg_time_add(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);

  // Create the TextLayer with specific bounds
  s_time_layer = text_layer_create(H_MID_V_TOP_RECT(0, 25, 89, 25));

  // Improve the layout to be more like a watchface  
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_font(s_time_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PMD_21)));
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_background_color(s_time_layer, GColorBlack);
  text_layer_set_overflow_mode(s_time_layer, GTextOverflowModeWordWrap);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  
  // TEXTBOX
  s_textbox_time = tg_textbox_create(H_MID_V_TOP_RECT(0, 23, 105, 31));
  tg_textbox_set_transparent_bg(s_textbox_time, true);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  layer_add_child(window_layer, tg_textbox_get_layer(s_textbox_time));
}

void tg_time_update() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M", tick_time);

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, s_buffer);
}

void tg_time_remove() {
  // Destroy TextLayer
  text_layer_destroy(s_time_layer);
  tg_textbox_destroy(s_textbox_time);
}