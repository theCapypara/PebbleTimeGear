#pragma once

#define PERSIST_TMP_TEMPERATURE  0
#define PERSIST_TMP_LAST_BOTTOM  1
#define PERSIST_CFG_BACKGROUND_1 2
#define PERSIST_CFG_BACKGROUND_2 3
#define PERSIST_CFG_BACKGROUND_3 4
#define PERSIST_CFG_SHOW_TEMP    5
#define PERSIST_CFG_SHOW_DATE    6
#define PERSIST_CFG_DATE_FORMAT  7
#define PERSIST_CFG_SHOW_STEPS   8
#define PERSIST_CFG_STEP_GOAL    9
#define PERSIST_CFG_BOTTOM_DISP  10
#define PERSIST_CFG_QUICK_VIEW   11
#define PERSIST_CFG_BG_CYCLE_INT 12
#define PERSIST_TMP_UPDATE_BG_TIME  13
#define PERSIST_TMP_CURRENT_BG   14

#define CONFIG_DATE_MMDD  0
#define CONFIG_DATE_DDMM  1

#define CONFIG_BOTTOM_NONE     0
#define CONFIG_BOTTOM_WEATHER  1

#define CONFIG_QV_ACTION_NOTHING  0
#define CONFIG_QV_ACTION_ROLLUP   1

#define SCREEN_W PBL_PLATFORM_SWITCH(PBL_PLATFORM_TYPE_CURRENT, \
  /*aplite*/ 144, \
  /*basalt*/ 144, \
  /*chalk*/ 180, \
  /*diorite*/ 144, \
  /*emery*/ 200)

#define SCREEN_H PBL_PLATFORM_SWITCH(PBL_PLATFORM_TYPE_CURRENT, \
  /*aplite*/ 168, \
  /*basalt*/ 168, \
  /*chalk*/ 180, \
  /*diorite*/ 168, \
  /*emery*/ 228)

#define TIMEGEAR_Y_OFFS PBL_PLATFORM_SWITCH(PBL_PLATFORM_TYPE_CURRENT, \
  /*aplite*/ 12, \
  /*basalt*/ 12, \
  /*chalk*/ 12, \
  /*diorite*/ 12, \
  /*emery*/ 2)

#define H_LEF_V_TOP_RECT(h_off, v_off, h_siz, v_siz) \
  GRect(h_off,                                  v_off,                                  h_siz, v_siz)
#define H_MID_V_TOP_RECT(h_off, v_off, h_siz, v_siz) \
  GRect((SCREEN_W / 2 - h_siz / 2) + h_off,     v_off,                                  h_siz, v_siz)
#define H_RIG_V_TOP_RECT(h_off, v_off, h_siz, v_siz) \
  GRect((SCREEN_W - h_siz) + h_off,             v_off,                                  h_siz, v_siz)

#define H_LEF_V_MID_RECT(h_off, v_off, h_siz, v_siz) \
  GRect(h_off,                                  (SCREEN_H / 2 - v_siz / 2) + v_off,     h_siz, v_siz)
#define H_MID_V_MID_RECT(h_off, v_off, h_siz, v_siz) \
  GRect((SCREEN_W / 2 - h_siz / 2) + h_off,     (SCREEN_H / 2 - v_siz / 2) + v_off,     h_siz, v_siz)
#define H_RIG_V_MID_RECT(h_off, v_off, h_siz, v_siz) \
  GRect((SCREEN_W - h_siz) + h_off,             (SCREEN_H / 2 - v_siz / 2) + v_off,     h_siz, v_siz)

#define H_LEF_V_BOT_RECT(h_off, v_off, h_siz, v_siz) \
  GRect(h_off,                                  (SCREEN_H - v_siz) + v_off, h_siz, v_siz)
#define H_MID_V_BOT_RECT(h_off, v_off, h_siz, v_siz) \
  GRect((SCREEN_W / 2 - h_siz / 2) + h_off,     (SCREEN_H - v_siz) + v_off, h_siz, v_siz)
#define H_RIG_V_BOT_RECT(h_off, v_off, h_siz, v_siz) \
  GRect((SCREEN_W - h_siz) + h_off,             (SCREEN_H - v_siz) + v_off, h_siz, v_siz)
