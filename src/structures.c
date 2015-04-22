#include <pebble.h>
#include "structures.h"

// Computes the number of bus distinct bus lines present in the BusStops array.
uint16_t get_num_bus_lines(BusStop *stops, uint8_t nb_stops) {
	uint8_t i;
	uint8_t nb_sections = 0;
	char *last_line_id = NULL;

	for(i = 0; i < nb_stops; i++) {
		if(last_line_id == NULL || strcmp(stops[i].line_id, last_line_id) != 0) {
			last_line_id = stops[i].line_id;
			nb_sections++;
		}
	}

	return nb_sections;
}

// Computes the number of stops present in the line at the specified index.
// (= all stops until the line changes, starting from this section index)
uint16_t get_num_stops_in_line(BusStop *stops, uint8_t nb_stops, uint16_t line_index) {
	uint8_t i;
	uint8_t nb_sections = 0;
	uint8_t nb_stops_current_section = 0;
	
	char *last_line_id = NULL;
	
	for(i = 0; i < nb_stops; i++) {
		// If the new row has a different line than the previous
		if(last_line_id == NULL || strcmp(stops[i].line_id, last_line_id) != 0) {
			// If the last line we were counting is the one we're looking for
			if(nb_sections - 1 == line_index) {
				return nb_stops_current_section;
			}
			
			last_line_id = stops[i].line_id;
			nb_sections++;
			nb_stops_current_section = 0;
		}
		
		nb_stops_current_section++;
	}
	
	return nb_stops_current_section;
}

// Gets the name of the line at the section index.
void get_line_name(BusStop *stops, uint8_t nb_stops, uint16_t line_index, char **line_name) {
	uint8_t i;
	uint8_t nb_sections = 0;
	
	char *last_line_id = NULL;
	
	for(i = 0; i < nb_stops; i++) {
		// If the new row has a different line than the previous
		if(last_line_id == NULL || strcmp(stops[i].line_id, last_line_id) != 0) {
			last_line_id = stops[i].line_id;
			nb_sections++;
		}
		
		if(nb_sections - 1 == line_index) {
			*line_name = stops[i].line_name;
			return;
		}
	}
}

// Gets the name of the stop and the name of the direction at the specified line index and stop index. 
void get_stop_name(BusStop *stops, uint8_t nb_stops, uint16_t line_index, uint16_t stop_index, char **stop_name, char **dir_name) {
	uint8_t i;
	uint8_t nb_sections = 0;
	uint8_t bus_index = 0;
	
	char *last_line_id = NULL;
	
	for(i = 0; i < nb_stops; i++) {
		// If the new row has a different line than the previous
		if(last_line_id == NULL || strcmp(stops[i].line_id, last_line_id) != 0) {
			last_line_id = stops[i].line_id;
			nb_sections++;
			bus_index = 0;
		}
		
		if(nb_sections - 1 == line_index && bus_index == stop_index) {
				*stop_name = stops[i].stop_name;
				*dir_name = stops[i].dir_name;
				return;
		}
		
		bus_index++;
	}
}

// Gets the bus stop at the specified line index and stop index. 
BusStop* get_stop_at_indexes(BusStop *stops, uint8_t nb_stops, uint16_t line_index, uint16_t stop_index) {
	uint8_t i;
	uint8_t nb_sections = 0;
	uint8_t bus_index = 0;
	
	char *last_line_id = NULL;
	
	for(i = 0; i < nb_stops; i++) {
		// If the new row has a different line than the previous
		if(last_line_id == NULL || strcmp(stops[i].line_id, last_line_id) != 0) {
			last_line_id = stops[i].line_id;
			nb_sections++;
			bus_index = 0;
		}
		
		if(nb_sections - 1 == line_index && bus_index == stop_index) {
				return &stops[i];
		}
		
		bus_index++;
	}
	
	return NULL;
}
