#include <ctype.h>
#include <pebble.h>
#include "hudfont.h"

int widths[4][13] = {
  {16,12,16,16,16,16,16,14,16,16,14,12,0 },
  {16,16,16,16,16,16,16,16,10,14,14,16,16},
  {16,16,16,16,16,16,14,16,14,16,14,14,16},
  {14,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 }
};

GBitmap * font;

void tg_hudfont_load() {
  font = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SHEET_HUD);
}

void tg_hudfont_free() {
  gbitmap_destroy(font);
}

void tg_hudfont_drawSingleCharacter(GContext *ctx, int x, int y, int x_index, int y_index) {
  int off_size = 0;
  for (int i = 0; i < x_index; i++) {
    off_size += widths[y_index][i] + 2;
  }
  GBitmap *sub = gbitmap_create_as_sub_bitmap(font, GRect(
    off_size, 
    18*y_index, 
    off_size+widths[y_index][x_index], 
    16)
  );
  graphics_draw_bitmap_in_rect(ctx, sub, GRect(
    x,
    y,
    widths[y_index][x_index],
    16)
  );
  gbitmap_destroy(sub);
}

void tg_hudfont_drawText(GContext *ctx, int x, int y, char * text, int spacing) {
  int x_offset = 0;
  for(int i = 0; text[i] != '\0'; i++) {
    int x_index = 0;
    int y_index = 0;
    switch(text[i]) {
      case '0':
        x_index = 0;
        break;
      case '1':
        x_index = 1;
        break;
      case '2':
        x_index = 2;
        break;
      case '3':
        x_index = 3;
        break;
      case '4':
        x_index = 4;
        break;
      case '5':
        x_index = 5;
        break;
      case '6':
        x_index = 6;
        break;
      case '7':
        x_index = 7;
        break;
      case '8':
        x_index = 8;
        break;
      case '9':
        x_index = 9;
        break;
      case 'f':
        x_index = 10;
        break;
      case '/':
        x_index = 11;
        break;
      case 'A':
        x_index = 0;
        y_index = 1;
        break;
      case 'B':
        x_index = 1;
        y_index = 1;
        break;
      case 'C':
        x_index = 2;
        y_index = 1;
        break;
      case 'D':
        x_index = 3;
        y_index = 1;
        break;
      case 'E':
        x_index = 4;
        y_index = 1;
        break;
      case 'F':
        x_index = 5;
        y_index = 1;
        break;
      case 'G':
        x_index = 6;
        y_index = 1;
        break;
      case 'H':
        x_index = 7;
        y_index = 1;
        break;
      case 'I':
        x_index = 8;
        y_index = 1;
        break;
      case 'J':
        x_index = 9;
        y_index = 1;
        break;
      case 'K':
        x_index = 10;
        y_index = 1;
        break;
      case 'L':
        x_index = 11;
        y_index = 1;
        break;
      case 'M':
        x_index = 12;
        y_index = 1;
        break;
      case 'N':
        x_index = 0;
        y_index = 2;
        break;
      case 'O':
        x_index = 1;
        y_index = 2;
        break;
      case 'P':
        x_index = 2;
        y_index = 2;
        break;
      case 'Q':
        x_index = 3;
        y_index = 2;
        break;
      case 'R':
        x_index = 4;
        y_index = 2;
        break;
      case 'S':
        x_index = 5;
        y_index = 2;
        break;
      case 'T':
        x_index = 6;
        y_index = 2;
        break;
      case 'U':
        x_index = 7;
        y_index = 2;
        break;
      case 'V':
        x_index = 8;
        y_index = 2;
        break;
      case 'W':
        x_index = 9;
        y_index = 2;
        break;
      case 'X':
        x_index = 10;
        y_index = 2;
        break;
      case 'Y':
        x_index = 11;
        y_index = 2;
        break;
      case 'Z':
        x_index = 12;
        y_index = 2;
        break;
      case '-':
        x_index = 0;
        y_index = 3;
        break;
      default:
        continue;
    }
    
    tg_hudfont_drawSingleCharacter(ctx, x+x_offset, y, x_index, y_index);
    x_offset += spacing + widths[y_index][x_index];
  }
}