#pragma once
#include <pebble.h>
#include "constants.h"

typedef struct {
  bool background1;
  bool background2;
  bool background3;
  int  backgroundCycleInterval;
  //char apiKey[33]; - is not used/saved by watch
  bool showTemperature;
  //int  temperaturUnit; - is not used/saved by watch
  bool showDate;
  int  dateFormat;
  bool showSteps;
  int  stepGoal;
  int  bottomDisplay;
  int  quickView;
} TgConfig;

TgConfig tg_config;

void tg_config_init();
void tg_config_update(DictionaryIterator *iter, void *context);