#pragma once
#include <pebble.h>

void tg_hudfont_load();
void tg_hudfont_free();

void tg_hudfont_drawText(GContext *ctx, int x, int y, char * text, int spacing);