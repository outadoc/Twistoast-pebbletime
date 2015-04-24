#include <pebble.h>
#include "protocol.h"

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
