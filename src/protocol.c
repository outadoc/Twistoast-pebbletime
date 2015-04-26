#include <pebble.h>
	
#include "protocol.h"
#include "main.h"

void inbox_received_callback(DictionaryIterator *iterator, void *context) {
	// Get the first pair
  Tuple *t = dict_read_first(iterator);
	
	// The first pair should contain the message ID
	if(t->key != KEY_MESSAGE_TYPE) return;
	
	// Change behaviour depending on message type
	switch (t->value->uint8) {
		case MSG_GET_STOPS:
			process_stop_info(iterator);
			break;
		default:
			return;
	}
}

void inbox_dropped_callback(AppMessageResult reason, void *context) {
}

void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
}

void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
}

void process_stop_info(DictionaryIterator *iterator) {
  Tuple *t = dict_read_next(iterator);
	BusStop** bus_stops_list = get_bus_stops_list();
	
	uint8_t i;
	uint8_t is_complete = 1;
	uint8_t list_size = 0;
	BusStop stop;

  // Process all pairs present
  while(t != NULL) {
    // Process this pair's key
    switch (t->key) {
      case KEY_LIST_SIZE: {
				if(bus_stops_list == NULL) {
					bus_stops_list = calloc((int) t->value->uint8, sizeof(BusStop));
				}
				
				list_size = t->value->uint8;
        break;
			}
			case KEY_INDEX: {
				bus_stops_list[(int) t->value->uint8] = &stop;
				break;
			}
			case KEY_STOP_ID: {
				stop.stop_id = t->value->cstring;
				break;
			}
			case KEY_LINE_ID: {
				stop.line_id = t->value->cstring;
				break;
			}
			case KEY_DIR_ID: {
				stop.dir_id = t->value->cstring;
				break;
			}
			case KEY_NETWORK_CODE: {
				stop.network_code = t->value->uint16;
				break;
			}
			case KEY_STOP_NAME: {
				stop.stop_name = t->value->cstring;
				break;
			}
			case KEY_LINE_NAME: {
				stop.line_name = t->value->cstring;
				break;
			}
			case KEY_DIR_NAME: {
				stop.dir_name = t->value->cstring;
				break;
			}
			case KEY_COLOR: {
				stop.color = t->value->uint32;
				break;
			}
			case KEY_IS_WATCHED: {
				stop.is_watched = t->value->uint8;
				break;
			}
    }

    // Get next pair, if any
    t = dict_read_next(iterator);
  }
	
	for(i = 0; i < list_size; i++) {
		if(bus_stops_list[(int) t->value->uint8] == NULL) {
			is_complete = 0;
		}
	}
	
	if(is_complete) {
		reload_menu_data();
	}
}

void send_get_stops_message() {
	const uint32_t size = dict_calc_buffer_size(1, sizeof(msgkey_t));
	
	uint8_t buffer[size];
	msgkey_t msg_type = MSG_GET_STOPS;
	
	DictionaryIterator *iter;
	app_message_outbox_begin(&iter);
	
	dict_write_begin(iter, buffer, sizeof(buffer));
	dict_write_data(iter, KEY_MESSAGE_TYPE, &msg_type, sizeof(msgkey_t));
	dict_write_end(iter);
	
	app_message_outbox_send();
}
