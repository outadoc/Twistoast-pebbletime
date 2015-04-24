#pragma once
#include "structures.h"
	
// Message types
#define MSG_ERROR 0x00
#define MSG_GET_STOPS 0x01
#define MSG_STOP_INFO 0x02
#define MSG_WATCH_STATUS_CHANGED 0x04
#define MSG_WATCH 0x05
#define MSG_UNWATCH 0x06
#define MSG_GET_SCHEDULE 0x07
#define MSG_SCHEDULE 0x08


// Data key identifiers
#define KEY_MESSAGE_TYPE 0x00
#define KEY_LIST_SIZE 0x01
#define KEY_STOP_ID 0x02
#define KEY_LINE_ID 0x03
#define KEY_DIR_ID 0x04
#define KEY_NETWORK_CODE 0x05
#define KEY_STOP_NAME 0x06
#define KEY_LINE_NAME 0x07
#define KEY_DIR_NAME 0x08
#define KEY_COLOR 0x09
#define KEY_IS_WATCHED 0x0A
#define KEY_ERROR_CODE 0x0B
#define KEY_NEXT_DEPARTURE_1 0x0C
#define KEY_NEXT_DEPARTURE_2 0x0D
#define KEY_INDEX 0x0E
	
typedef uint8_t msgkey_t;
	
void send_get_stops_message();
void send_watch_message(BusStop *stop);
void send_unwatch_message(BusStop *stop);
void send_get_schedule_message(BusStop *stop);
