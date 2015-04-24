#pragma once
#include <pebble.h>

typedef struct {
	char *stop_id;
	char *line_id;
	char *dir_id;
	uint16_t network_code;
	char *stop_name;
	char *line_name;
	char *dir_name;
	uint32_t color;
	uint8_t is_watched;
} BusStop;

uint16_t get_num_bus_lines(BusStop *stops, uint8_t nb_stops);
uint16_t get_num_stops_in_line(BusStop *stops, uint8_t nb_stops, uint16_t line_index);
void get_line_name(BusStop *stops, uint8_t nb_stops, uint16_t line_index, char **line_name);
void get_stop_name(BusStop *stops, uint8_t nb_stops, uint16_t line_index, uint16_t stop_index, char **stop_name, char **dir_name);
BusStop* get_stop_at_indexes(BusStop *stops, uint8_t nb_stops, uint16_t line_index, uint16_t stop_index);
