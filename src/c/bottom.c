#include <pebble.h>
#include "bottom.h"
#include "textbox.h"
#include "constants.h"
#include "config.h"

TextLayer *s_bottom_layer;
Textbox *s_textbox_bottom;

int mode = 0;
char bottom_text[128] = " ";

void tg_bottom_add(Window *window) {
  if (tg_config.bottomDisplay == CONFIG_BOTTOM_NONE) return;
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);

  // Create the TextLayer with specific bounds
  s_bottom_layer = text_layer_create(GRect(19, 153, 106, 27));
  
  // Init last temperature
  if (persist_exists(PERSIST_TMP_LAST_BOTTOM)) {
    persist_read_string(PERSIST_TMP_LAST_BOTTOM, bottom_text, sizeof bottom_text);
  }

  // Improve the layout to be more like a watchface  
  text_layer_set_text(s_bottom_layer, bottom_text);
  text_layer_set_font(s_bottom_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PMD_11)));
  text_layer_set_text_color(s_bottom_layer, GColorWhite);
  text_layer_set_background_color(s_bottom_layer, GColorBlack);
  text_layer_set_overflow_mode(s_bottom_layer, GTextOverflowModeWordWrap);
  text_layer_set_text_alignment(s_bottom_layer, GTextAlignmentCenter);
  
  // TEXTBOX
  s_textbox_bottom = tg_textbox_create(GRect(12, 148, 120, 27));
  tg_textbox_set_transparent_bg(s_textbox_bottom, false);
  tg_textbox_set_no_bottom_decoration(s_textbox_bottom, true);
  
  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, tg_textbox_get_layer(s_textbox_bottom));
  layer_add_child(window_layer, text_layer_get_layer(s_bottom_layer));
};

void tg_bottom_update_weather(char* weather) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Update Weather %s", weather);
  if (tg_config.bottomDisplay != CONFIG_BOTTOM_WEATHER) return;
  
  char buffer[128]; // TODO: Is this safety buffer actually needed?
  
  snprintf(bottom_text, sizeof bottom_text, "Weather: %s", weather);
  snprintf(buffer, sizeof buffer, "Weather: %s", weather);

  // Display this time on the TextLayer
  text_layer_set_text(s_bottom_layer, bottom_text);
  persist_write_string(PERSIST_TMP_LAST_BOTTOM, buffer);
};

void tg_bottom_remove() {
  // Destroy Layer
  if (s_bottom_layer != NULL) {
    text_layer_destroy(s_bottom_layer);
    tg_textbox_destroy(s_textbox_bottom);
  }
};