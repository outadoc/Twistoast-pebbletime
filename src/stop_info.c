#include <pebble.h>
#include "stop_info.h"

static Window *s_window;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, true);
}

static void destroy_ui(void) {
  window_destroy(s_window);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_stop_info(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_stop_info(void) {
  window_stack_remove(s_window, true);
}
