#include <pebble.h>
#include "constants.h"
#include "timegear.h"

BitmapLayer *s_timegear_layer;
BitmapLayer *s_battery_light_layer;

GBitmap *s_timegear;
GBitmap *s_timegear_charging;
GBitmap *s_no_bluetooth;
GBitmap *s_battery_light;
int old_resource = -1;
bool currently_connected = false;

void tg_timegear_add(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  
  s_timegear_layer = bitmap_layer_create(H_MID_V_MID_RECT(0,TIMEGEAR_Y_OFFS,84,88));
  s_battery_light_layer = bitmap_layer_create(H_MID_V_MID_RECT(0,TIMEGEAR_Y_OFFS,84,88));
  
  bitmap_layer_set_compositing_mode(s_timegear_layer, GCompOpSet);
  bitmap_layer_set_compositing_mode(s_battery_light_layer, GCompOpSet);
  
  s_timegear = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TIMEGEAR);
  s_timegear_charging = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TIMEGEAR_CHARGING);
  s_no_bluetooth = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NO_BLUETOOTH);

  layer_add_child(window_layer, bitmap_layer_get_layer(s_battery_light_layer));
  layer_add_child(window_layer, bitmap_layer_get_layer(s_timegear_layer));
}

void tg_timegear_update_battery(BatteryChargeState charge) {
  int new_battery = charge.charge_percent;
  GBitmap *old_image = s_battery_light;
    
  int resource_id;
  if (new_battery >= 100) {
    resource_id = RESOURCE_ID_IMAGE_BATTERY_100;
  } else if (new_battery >= 90) {
    resource_id = RESOURCE_ID_IMAGE_BATTERY_90;
  } else if (new_battery >= 80) {
    resource_id = RESOURCE_ID_IMAGE_BATTERY_80;
  } else if (new_battery >= 70) {
    resource_id = RESOURCE_ID_IMAGE_BATTERY_70;
  } else if (new_battery >= 60) {
    resource_id = RESOURCE_ID_IMAGE_BATTERY_60;
  } else if (new_battery >= 50) {
    resource_id = RESOURCE_ID_IMAGE_BATTERY_50;
  } else if (new_battery >= 40) {
    resource_id = RESOURCE_ID_IMAGE_BATTERY_40;
  } else if (new_battery >= 30) {
    resource_id = RESOURCE_ID_IMAGE_BATTERY_30;
  } else if (new_battery >= 20) {
    resource_id = RESOURCE_ID_IMAGE_BATTERY_20;
  } else if (new_battery >= 10) {
    resource_id = RESOURCE_ID_IMAGE_BATTERY_10;
  } else if (new_battery >= 0) {
    resource_id = RESOURCE_ID_IMAGE_BATTERY_0;
  } 
  
  if ((old_resource == -1) || (old_resource != resource_id)) {
    
    GBitmap *new_image = gbitmap_create_with_resource(resource_id);
    bitmap_layer_set_bitmap(s_battery_light_layer, new_image);
    
    if (old_image != NULL) {
      gbitmap_destroy(old_image);
    }
    s_battery_light = new_image;
  }
  
  if (charge.is_plugged) {
    bitmap_layer_set_bitmap(s_timegear_layer, s_timegear_charging);
  } else {
    tg_timegear_update_connection(currently_connected);
  }
  
}

void tg_timegear_update_connection(bool connected) {
  currently_connected = connected;
  if (connected) {  
    bitmap_layer_set_bitmap(s_timegear_layer, s_timegear);
  } else {
    bitmap_layer_set_bitmap(s_timegear_layer, s_no_bluetooth);
  }
}

void tg_timegear_remove() {
  bitmap_layer_destroy(s_timegear_layer);
  bitmap_layer_destroy(s_battery_light_layer);
  gbitmap_destroy(s_battery_light);
  gbitmap_destroy(s_timegear);
  gbitmap_destroy(s_no_bluetooth);
}