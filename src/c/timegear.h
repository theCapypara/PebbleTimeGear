#pragma once
#include <pebble.h>

void tg_timegear_add(Window *window);
void tg_timegear_update_battery(BatteryChargeState charge);
void tg_timegear_update_connection(bool connected);
void tg_timegear_remove();