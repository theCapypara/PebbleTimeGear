#include <pebble.h>
#include "textbox.h"

void tg_textbox_layer_update_proc(Layer *layer, GContext *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Redrawing a textbox");
  
  Textbox *textbox = layer_get_data(layer);
  // Draw textbox
  
  // Bounds
  GRect original_bounds = layer_get_bounds(layer);
  GRect tl_bounds = gbitmap_get_bounds(textbox->img_tl);
  GRect tr_bounds = gbitmap_get_bounds(textbox->img_tr);
  GRect t_bounds = gbitmap_get_bounds(textbox->img_t);
  GRect b_bounds = gbitmap_get_bounds(textbox->img_b);
  GRect l_bounds = gbitmap_get_bounds(textbox->img_l);
  GRect r_bounds = gbitmap_get_bounds(textbox->img_r);
  GRect bl_bounds = gbitmap_get_bounds(textbox->img_bl);
  GRect br_bounds = gbitmap_get_bounds(textbox->img_br);
  
  // Fill black
  if (!textbox->transparent) {
    graphics_context_set_fill_color(ctx, GColorBlack);
    graphics_fill_rect(ctx, 
                       GRect(tr_bounds.size.w, 
                         tr_bounds.size.h, 
                         original_bounds.size.w-tr_bounds.size.w-br_bounds.size.w,
                         original_bounds.size.h-tr_bounds.size.h-br_bounds.size.h
                       ), 0, GCornersAll
    );
  }
  
  // Set the compositing mode (GCompOpSet is required for transparency)
  graphics_context_set_compositing_mode(ctx, GCompOpSet);
  
  // Draw the textbox
  graphics_draw_bitmap_in_rect(ctx, textbox->img_tl, GRect(
    0,
    0,
    tl_bounds.size.w,
    tl_bounds.size.h
  ));
  graphics_draw_bitmap_in_rect(ctx, textbox->img_tr, GRect(
    original_bounds.size.w-tl_bounds.size.w,
    0,
    tr_bounds.size.w,
    tr_bounds.size.h
  ));
  graphics_draw_bitmap_in_rect(ctx, textbox->img_bl, GRect(
    0,
    original_bounds.size.h-tl_bounds.size.h,
    bl_bounds.size.w,
    bl_bounds.size.h
  ));
  graphics_draw_bitmap_in_rect(ctx, textbox->img_br, GRect(
    original_bounds.size.w-tl_bounds.size.w,
    original_bounds.size.h-tl_bounds.size.h,
    br_bounds.size.w,
    br_bounds.size.h
  ));
  graphics_draw_bitmap_in_rect(ctx, textbox->img_t, GRect(
    tl_bounds.size.w,
    0,
    original_bounds.size.w-tl_bounds.size.w-tr_bounds.size.w,
    t_bounds.size.h
  ));
  graphics_draw_bitmap_in_rect(ctx, textbox->img_b, GRect(
    br_bounds.size.w,
    original_bounds.size.h-b_bounds.size.h,
    original_bounds.size.w-br_bounds.size.w-br_bounds.size.w,
    b_bounds.size.h
  ));
  graphics_draw_bitmap_in_rect(ctx, textbox->img_l, GRect(
    0,
    tl_bounds.size.h,
    l_bounds.size.w,
    original_bounds.size.h-tl_bounds.size.h-bl_bounds.size.h
  ));
  graphics_draw_bitmap_in_rect(ctx, textbox->img_r, GRect(
    original_bounds.size.w-r_bounds.size.w,
    tr_bounds.size.h,
    r_bounds.size.w,
    original_bounds.size.h-tr_bounds.size.h-br_bounds.size.h
  ));
}

Textbox * tg_textbox_create(GRect bounds) {
  Layer * layer = layer_create_with_data(bounds, sizeof(Textbox));
  Textbox *textbox = (Textbox *)layer_get_data(layer);
  textbox->layer = layer;
  
  textbox->img_tl = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TEXTBOX_TL);  
  textbox->img_tr = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TEXTBOX_TR);  
  textbox->img_t = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TEXTBOX_T);  
  textbox->img_b = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TEXTBOX_B);  
  textbox->img_l = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TEXTBOX_L);  
  textbox->img_r = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TEXTBOX_R);  
  textbox->img_bl = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TEXTBOX_BL);  
  textbox->img_br = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TEXTBOX_BR);
  
  textbox->transparent = false;
  
  // Set update procs
  layer_set_update_proc(textbox->layer, tg_textbox_layer_update_proc);
  return textbox;
}

Layer * tg_textbox_get_layer(Textbox * textbox) {
  return textbox->layer;
}

void tg_textbox_destroy(Textbox * textbox) {
  layer_destroy(textbox->layer);
  gbitmap_destroy(textbox->img_tl);
  gbitmap_destroy(textbox->img_tr);
  gbitmap_destroy(textbox->img_t);
  gbitmap_destroy(textbox->img_b);
  gbitmap_destroy(textbox->img_l);
  gbitmap_destroy(textbox->img_r);
  gbitmap_destroy(textbox->img_bl);
  gbitmap_destroy(textbox->img_br);
  free(textbox);
}

void tg_textbox_mark_dirty(Textbox * textbox) {
  layer_mark_dirty(textbox->layer);
}

void tg_textbox_set_transparent_bg(Textbox * textbox, bool transparent) {
  textbox->transparent = transparent;
}