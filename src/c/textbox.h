#pragma once
#include <pebble.h>

typedef struct {
  Layer * layer;
  GBitmap * img_tl;
  GBitmap * img_tr;
  GBitmap * img_t;
  GBitmap * img_b;
  GBitmap * img_l;
  GBitmap * img_r;
  GBitmap * img_bl;
  GBitmap * img_br;
  bool transparent;
  bool hide_bottom_decoration;
} Textbox;

Textbox * tg_textbox_create(GRect bounds);
Layer * tg_textbox_get_layer(Textbox * textbox);
void tg_textbox_destroy(Textbox * textbox);
void tg_textbox_mark_dirty(Textbox * textbox);
void tg_textbox_set_transparent_bg(Textbox * textbox, bool transparent);
void tg_textbox_set_no_bottom_decoration(Textbox * textbox, bool hide_bottom_decoration);