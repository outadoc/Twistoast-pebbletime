#include <pebble.h>
#include "structures.h"
#include "stop_info.h"

static Window *s_main_window;
static MenuLayer *s_menu_layer;

static BusStop *bus_stops_list;
static uint8_t nb_bus_stops = 0;

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
	return get_num_bus_lines(bus_stops_list, nb_bus_stops);
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
	return get_num_stops_in_line(bus_stops_list, nb_bus_stops, section_index);
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
	return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
	char* line_name = NULL;
	
	get_line_name(bus_stops_list, nb_bus_stops, section_index, &line_name);
	menu_cell_basic_header_draw(ctx, cell_layer, line_name);
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
	char* stop_name = NULL;
	char* dir_name = NULL;
	
	get_stop_name(bus_stops_list, nb_bus_stops, cell_index->section, cell_index->row, &stop_name, &dir_name);
	menu_cell_basic_draw(ctx, cell_layer, stop_name, dir_name, NULL);
}

static void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
	show_stop_info();
}

static void main_window_load(Window *window) {
	nb_bus_stops = 3;
	bus_stops_list = calloc(nb_bus_stops, sizeof(BusStop));
	
	bus_stops_list[0] = (BusStop) {
		.stop_id = "test",
		.line_id = "TRAM",
		.dir_id = "A",
		.network_code = 147,
		.stop_name = "Academie",
		.line_name = "Tram",
		.dir_name = "Ifs Grace de Dieu",
		.color = 0,
		.is_watched = 0
	};
	
	bus_stops_list[1] = (BusStop) {
		.stop_id = "test",
		.line_id = "TRAM",
		.dir_id = "R",
		.network_code = 147,
		.stop_name = "Bernières",
		.line_name = "Tram",
		.dir_name = "Caen Campus 2",
		.color = 0,
		.is_watched = 0
	};
	
	bus_stops_list[2] = (BusStop) {
		.stop_id = "test",
		.line_id = "3",
		.dir_id = "A",
		.network_code = 147,
		.stop_name = "Anciennes Boucheries",
		.line_name = "Lianes 3",
		.dir_name = "Whatever",
		.color = 0,
		.is_watched = 0
	};
	
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_frame(window_layer);

	// Create the menu layer
	s_menu_layer = menu_layer_create(bounds);
	
	menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks){
		.get_num_sections = menu_get_num_sections_callback,
		.get_num_rows = menu_get_num_rows_callback,
		.get_header_height = menu_get_header_height_callback,
		.draw_header = menu_draw_header_callback,
		.draw_row = menu_draw_row_callback,
		.select_click = menu_select_callback,
	});

	// Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(s_menu_layer, window);
	
	layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
}

void main_window_unload(Window *window) {
	menu_layer_destroy(s_menu_layer);
	free(bus_stops_list);
}

static void init() {
	s_main_window = window_create();
	
	window_set_window_handlers(s_main_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload,
	});
	
	window_stack_push(s_main_window, true);
}

static void deinit() {
	window_destroy(s_main_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
