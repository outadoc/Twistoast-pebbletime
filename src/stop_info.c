#include <pebble.h>
#include "stop_info.h"
#include "structures.h"

static Window *s_window;
static TextLayer *lbl_line, *lbl_stop, *lbl_direction, *lbl_schedule1, *lbl_schedule2;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, true);
	
	Layer *window_layer = window_get_root_layer(s_window);
	
	//set text placement
	lbl_line = text_layer_create(GRect(5, 0, 140, 32));
	lbl_direction = text_layer_create(GRect(5, 33, 140, 30));
	lbl_stop = text_layer_create(GRect(5, 60, 140, 30));
	lbl_schedule1 = text_layer_create(GRect(5, 90, 140, 28));
	lbl_schedule2 = text_layer_create(GRect(5, 118, 140, 28));
	
	//set text font
	text_layer_set_font(lbl_line, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_font(lbl_stop, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_font(lbl_direction, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_font(lbl_schedule1, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_font(lbl_schedule2, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	
	//add text to window
	layer_add_child(window_layer, text_layer_get_layer(lbl_line));
	layer_add_child(window_layer, text_layer_get_layer(lbl_direction));
	layer_add_child(window_layer, text_layer_get_layer(lbl_stop));
	layer_add_child(window_layer, text_layer_get_layer(lbl_schedule1));
	layer_add_child(window_layer, text_layer_get_layer(lbl_schedule2));
	
	#ifdef PBL_COLOR
	text_layer_set_background_color(lbl_line, GColorClear);
	text_layer_set_background_color(lbl_direction, GColorClear);
	text_layer_set_background_color(lbl_stop, GColorClear);
	text_layer_set_background_color(lbl_schedule1, GColorClear);
	text_layer_set_background_color(lbl_schedule2, GColorClear);
	#endif
}

static void destroy_ui(void) {
  window_destroy(s_window);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_stop_info(BusStop *stop) {
  initialise_ui();
	
	#ifdef PBL_COLOR
	window_set_background_color(s_window, GColorFromHEX(stop->color));
	#endif

	text_layer_set_text(lbl_line, stop->line_name);
	text_layer_set_text(lbl_direction, stop->dir_name);
	text_layer_set_text(lbl_stop, stop->stop_name);
	
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_stop_info(void) {
  window_stack_remove(s_window, true);
}
