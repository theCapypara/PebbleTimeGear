#include <pebble.h>
#include "constants.h"
#include "steps.h"
#include "config.h"

Layer *s_bar_layer;

GBitmap *s_bar_empty;
GBitmap *s_bar_full;
GBitmap *s_bar_full2;

int steps = 0;

void tg_steps_update_proc(Layer *layer, GContext *ctx) {
  int step_goal = tg_config.stepGoal;
  APP_LOG(APP_LOG_LEVEL_DEBUG, 
            "Step goal: %d/%d", 
            steps,
            step_goal
           );
  // Set the compositing mode (GCompOpSet is required for transparency)
  graphics_context_set_compositing_mode(ctx, GCompOpSet);
  
  // Empty bar
  if (steps < step_goal) {
    graphics_draw_bitmap_in_rect(ctx, s_bar_empty, GRect(
      0,
      0,
      77,
      7
    ));
  }
  // Full bar
  if (steps > 0) {
    graphics_draw_bitmap_in_rect(ctx, s_bar_full, GRect(
      0,
      0,
      steps > step_goal ? 77 : (int)((double)(steps)/step_goal * 77) ,
      7
    ));
  }
  // Full bar 2
  if (steps > step_goal) {
    graphics_draw_bitmap_in_rect(ctx, s_bar_full2, GRect(
      0,
      0,
      steps > step_goal*2 ? 77 : (int)(((double)(steps-step_goal))/step_goal * 77) ,
      7
    ));
  }
}

void tg_steps_add(Window * window) {
  if (!tg_config.showSteps) return;
  Layer *window_layer = window_get_root_layer(window);
  
  s_bar_layer = layer_create(H_MID_V_TOP_RECT(0, 57, 77, 7));
  layer_set_update_proc(s_bar_layer, tg_steps_update_proc);
  
  s_bar_empty = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAR_EMPTY);
  s_bar_full = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAR_FULL);
  s_bar_full2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAR_FULL2);

  layer_add_child(window_layer, s_bar_layer);
}

void tg_steps_update_health() {
  #if defined(PBL_HEALTH)
  if (s_bar_layer != NULL) {
    HealthMetric metric = HealthMetricStepCount;
    time_t start = time_start_of_today();
    time_t end = time(NULL);
    
    HealthServiceAccessibilityMask mask = health_service_metric_accessible(metric, 
      start, end);
    
    steps = 0;
    if(mask & HealthServiceAccessibilityMaskAvailable) {
      steps = (int)health_service_sum_today(metric);
    }
  }
  #endif
}

void tg_steps_remove() {
  if (s_bar_layer != NULL) {
    layer_destroy(s_bar_layer);
    gbitmap_destroy(s_bar_empty);
    gbitmap_destroy(s_bar_full);
    gbitmap_destroy(s_bar_full2);
  }
}

