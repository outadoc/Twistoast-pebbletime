#include <pebble.h>
#include "stop_info.h"
#include "structures.h"
	
#define DISPLAY_WIDTH 144
#define DISPLAY_HEIGHT 168
	
static Window *s_window;
static TextLayer *lbl_line, *lbl_stop, *lbl_direction, *lbl_schedule1, *lbl_schedule2;
static Layer *header;

static BusStop *bus_stop;

static void initialise_ui(void) {
  s_window = window_create();
	window_set_fullscreen(s_window, true);
	
	Layer *window_layer = window_get_root_layer(s_window);
	
	header = layer_create(GRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT));
	layer_add_child(window_layer, header);
	layer_set_update_proc(header, header_update_callback);
	
	//set text placement
	lbl_line = text_layer_create(GRect(7, 3, DISPLAY_WIDTH - 13, 32));
	lbl_stop = text_layer_create(GRect(7, 33, DISPLAY_WIDTH - 13, 30));
	lbl_direction = text_layer_create(GRect(7, 55, DISPLAY_WIDTH - 15, 30));
	lbl_schedule1 = text_layer_create(GRect(10, 97, DISPLAY_WIDTH - 15, 28));
	lbl_schedule2 = text_layer_create(GRect(10, 125, DISPLAY_WIDTH - 15, 28));
	
	//set text font
	text_layer_set_font(lbl_line, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_font(lbl_stop, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_font(lbl_direction, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_font(lbl_schedule1, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_font(lbl_schedule2, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	
	//add text to window
	layer_add_child(window_layer, text_layer_get_layer(lbl_line));
	layer_add_child(window_layer, text_layer_get_layer(lbl_stop));
	layer_add_child(window_layer, text_layer_get_layer(lbl_direction));
	layer_add_child(window_layer, text_layer_get_layer(lbl_schedule1));
	layer_add_child(window_layer, text_layer_get_layer(lbl_schedule2));
	
	text_layer_set_background_color(lbl_line, GColorClear);
	text_layer_set_background_color(lbl_stop, GColorClear);
	text_layer_set_background_color(lbl_direction, GColorClear);
	
	#ifndef PBL_COLOR
		text_layer_set_text_color(lbl_line, GColorWhite);
		text_layer_set_text_color(lbl_stop, GColorWhite);
		text_layer_set_text_color(lbl_direction, GColorWhite);
	#endif
}

static void destroy_ui(void) {
  window_destroy(s_window);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void header_update_callback(Layer *layer, GContext *ctx) {
	#ifdef PBL_COLOR
  	graphics_context_set_fill_color(ctx, GColorFromHEX(bus_stop->color));
	#else
		graphics_context_set_fill_color(ctx, GColorBlack);
	#endif
	
	graphics_fill_rect(ctx, GRect(2, 2, DISPLAY_WIDTH - 6, 88), 5, GCornersAll);
}


void show_stop_info(BusStop *stop) {
	bus_stop = stop;
  initialise_ui();

	text_layer_set_text(lbl_line, stop->line_name);
	text_layer_set_text(lbl_direction, stop->dir_name);
	text_layer_set_text(lbl_stop, stop->stop_name);
	
	text_layer_set_text(lbl_schedule1, "Dans 3 minutes");
	text_layer_set_text(lbl_schedule2, "Dans 10 minutes");
	
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
	
  window_stack_push(s_window, true);
}

void hide_stop_info(void) {
  window_stack_remove(s_window, true);
}
