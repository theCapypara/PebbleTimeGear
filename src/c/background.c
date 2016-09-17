#include <pebble.h>
#include "background.h"
#include "config.h"

BitmapLayer *s_background_layer;
GBitmap *s_background;

void tg_bg_add(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  
  GRect main_bounds = layer_get_bounds(window_layer);
  
  s_background_layer = bitmap_layer_create(main_bounds);
  
  tg_bg_update();
       
  layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));
}

void tg_bg_remove() {
  bitmap_layer_destroy(s_background_layer);
  gbitmap_destroy(s_background);
}

char *translate_error(status_t result) {
  switch (result) {
    case S_SUCCESS: return "S_SUCCESS";
    case E_ERROR: return "E_ERROR";
    case E_UNKNOWN: return "E_UNKNOWN";
    case E_INTERNAL: return "E_INTERNAL";
    case E_INVALID_ARGUMENT: return "E_INVALID_ARGUMENT";
    case E_OUT_OF_MEMORY: return "E_OUT_OF_MEMORY";
    case E_OUT_OF_STORAGE: return "E_OUT_OF_STORAGE";
    case E_OUT_OF_RESOURCES: return "E_OUT_OF_RESOURCES";
    case E_RANGE: return "E_RANGE";
    case E_DOES_NOT_EXIST: return "E_DOES_NOT_EXIST";
    case E_INVALID_OPERATION: return "E_INVALID_OPERATION";
    case E_BUSY: return "E_BUSY";
    case E_AGAIN: return "E_AGAIN";
    case S_NO_MORE_ITEMS: return "S_NO_MORE_ITEMS";
    case S_NO_ACTION_REQUIRED: return "S_NO_ACTION_REQUIRED";
    default: return "SUCCESS?";
  }
}

void tg_bg_update() {
  time_t now = time(NULL);
  time_t lastTime = (time_t)persist_read_int(PERSIST_TMP_UPDATE_BG_TIME);
  int difference = difftime(now, lastTime);
  // The watch doesn't have enough memory to load both the old and the new image, 
  // so only update if no image was set yet
  if (difference > (tg_config.backgroundCycleInterval*60)  || s_background == NULL) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, 
            "Updating background. Last time: %d, now: %d, diff is %d, max is %d", 
             (int)lastTime,
             (int)now,
             difference,
             tg_config.backgroundCycleInterval*60
            );
    int current_background = persist_read_int(PERSIST_TMP_CURRENT_BG);
    if (difference > (tg_config.backgroundCycleInterval*60))  {
      // Only cycle through selected, fall back if no selected
      if (!tg_config.background1 && !tg_config.background2 && !tg_config.background3) {
        current_background = 0;
      } else {
        bool okay = false;
        while (!okay) {
          current_background = (current_background + 1) % 3;
          if (current_background == 0 && tg_config.background1) okay = true;
          if (current_background == 1 && tg_config.background2) okay = true;
          if (current_background == 2 && tg_config.background3) okay = true;
        }
      }
      //APP_LOG(APP_LOG_LEVEL_DEBUG, "Changing background to %d, setting time to %d", current_background, (int) now);
      persist_write_int(PERSIST_TMP_UPDATE_BG_TIME, (int) now);
      //APP_LOG(APP_LOG_LEVEL_DEBUG, "Okay? %s", translate_error(status));
    }
    int resource_id = RESOURCE_ID_IMAGE_BG_1;
    switch (current_background) {
      case 1:
        resource_id = RESOURCE_ID_IMAGE_BG_2;
        break;
      case 2:
        resource_id = RESOURCE_ID_IMAGE_BG_3;
        break;
    };
    APP_LOG(APP_LOG_LEVEL_DEBUG, 
            "Background is now no. %d (res. %d)", 
            current_background,
            resource_id
           );
    if (s_background != NULL) {
      gbitmap_destroy(s_background);
    }
    GBitmap *new_image = gbitmap_create_with_resource(resource_id);
    bitmap_layer_set_bitmap(s_background_layer, new_image);
    s_background = new_image;
    persist_write_int(PERSIST_TMP_CURRENT_BG, current_background);
  }
}