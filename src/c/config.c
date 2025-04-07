#include <pebble.h>
#include "config.h"

// Defaults
TgConfig tg_config = {
  .background1        = true,
  .background2        = true,
  .background3        = true,
  .backgroundCycleInterval = 60,
  .showTemperature    = true,
  .showDate           = true,
  .dateFormat         = CONFIG_DATE_MMDD,
  .showSteps          = true,
  .stepGoal           = 5000,
  .bottomDisplay      = CONFIG_BOTTOM_WEATHER,
  .quickView          = CONFIG_QV_ACTION_ROLLUP
};

// Init from Storage
void tg_config_init() {
  if (persist_exists(PERSIST_CFG_BACKGROUND_1)) {tg_config.background1 = persist_read_bool(PERSIST_CFG_BACKGROUND_1);}
  if (persist_exists(PERSIST_CFG_BACKGROUND_2)) {tg_config.background2 = persist_read_bool(PERSIST_CFG_BACKGROUND_2);}
  if (persist_exists(PERSIST_CFG_BACKGROUND_3)) {tg_config.background3 = persist_read_bool(PERSIST_CFG_BACKGROUND_3);}
  if (persist_exists(PERSIST_CFG_BG_CYCLE_INT)) {tg_config.backgroundCycleInterval = persist_read_int(PERSIST_CFG_BG_CYCLE_INT);}
  if (persist_exists(PERSIST_CFG_SHOW_TEMP)) {tg_config.showTemperature = persist_read_bool(PERSIST_CFG_SHOW_TEMP);}
  if (persist_exists(PERSIST_CFG_SHOW_DATE)) {tg_config.showDate = persist_read_bool(PERSIST_CFG_SHOW_DATE);}
  if (persist_exists(PERSIST_CFG_DATE_FORMAT)) {tg_config.dateFormat = persist_read_int(PERSIST_CFG_DATE_FORMAT);}
  if (persist_exists(PERSIST_CFG_SHOW_STEPS)) {tg_config.showSteps = persist_read_bool(PERSIST_CFG_SHOW_STEPS);}
  if (persist_exists(PERSIST_CFG_STEP_GOAL)) {tg_config.stepGoal = persist_read_int(PERSIST_CFG_STEP_GOAL);}
  if (persist_exists(PERSIST_CFG_BOTTOM_DISP)) {tg_config.bottomDisplay = persist_read_int(PERSIST_CFG_BOTTOM_DISP);}
  if (persist_exists(PERSIST_CFG_QUICK_VIEW)) {tg_config.quickView = persist_read_int(PERSIST_CFG_QUICK_VIEW);}
};

void tg_config_save_bool(DictionaryIterator *iter, const uint32_t message_key, const int config_key) {
  Tuple *tpl = dict_find(iter, message_key);
  if(tpl) {
    bool value = tpl->value->int32 > 0;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Config set bool %d to %d", (int)message_key, value);
    persist_write_bool(config_key, value);
  }
};

void tg_config_save_str_int(DictionaryIterator *iter, const uint32_t message_key, const int config_key) {
  Tuple *tpl = dict_find(iter, message_key);
  if(tpl) {
    int32_t value = atoi(tpl->value->cstring);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Config set int %d to %d (%s)", (int)message_key, (int)value, tpl->value->cstring);
    persist_write_int(config_key, value);
  }
};

void tg_config_save_int(DictionaryIterator *iter, const uint32_t message_key, const int config_key) {
  Tuple *tpl = dict_find(iter, message_key);
  if(tpl) {
    int32_t value = tpl->value->int32;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Config set int %d to %d", (int)message_key, (int)value);
    persist_write_int(config_key, value);
  }
};

void tg_config_save_string(DictionaryIterator *iter, const uint32_t message_key, const int config_key) {
  Tuple *tpl = dict_find(iter, message_key);
  if(tpl) {
    char *value = tpl->value->cstring;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Config set string %d to %s", (int)message_key, value);
    persist_write_string(config_key, value);
  }
};

// Update from Phone (+ Storage)
void tg_config_update(DictionaryIterator *iter, void *context) {
  tg_config_save_bool(iter, MESSAGE_KEY_CfgBackground, PERSIST_CFG_BACKGROUND_1);
  tg_config_save_bool(iter, MESSAGE_KEY_CfgBackground + 1, PERSIST_CFG_BACKGROUND_2);
  tg_config_save_bool(iter, MESSAGE_KEY_CfgBackground + 2, PERSIST_CFG_BACKGROUND_3);
  tg_config_save_int(iter, MESSAGE_KEY_CfgBackgroundCycleInterval, PERSIST_CFG_BG_CYCLE_INT);
  tg_config_save_bool(iter, MESSAGE_KEY_CfgShowTemperature, PERSIST_CFG_SHOW_TEMP);
  tg_config_save_bool(iter, MESSAGE_KEY_CfgShowDate, PERSIST_CFG_SHOW_DATE);
  tg_config_save_str_int(iter, MESSAGE_KEY_CfgDateFormat, PERSIST_CFG_DATE_FORMAT);
  tg_config_save_bool(iter, MESSAGE_KEY_CfgShowSteps, PERSIST_CFG_SHOW_STEPS);
  tg_config_save_int(iter, MESSAGE_KEY_CfgStepGoal, PERSIST_CFG_STEP_GOAL);
  tg_config_save_str_int(iter, MESSAGE_KEY_CfgBottomDisplay, PERSIST_CFG_BOTTOM_DISP);
  tg_config_save_str_int(iter, MESSAGE_KEY_CfgQuickView, PERSIST_CFG_QUICK_VIEW);
  // If any is set, assume config was changed.
  if (dict_find(iter, PERSIST_CFG_BACKGROUND_1)) {
    tg_config_init();
    // Reset background cycle
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Config received. Rereading. Reseting background.");
    persist_write_int(PERSIST_TMP_UPDATE_BG_TIME, 0);
    persist_write_int(PERSIST_TMP_CURRENT_BG, 2);
  }
};