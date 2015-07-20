#include <pebble.h>

Window* window;
BitmapLayer* bitmap_layer;
GBitmap* bitmap;
uint32_t resource;

static void switch_bitmap(int8_t value) {
    resource += value;
    gbitmap_destroy(bitmap);
    bitmap = gbitmap_create_with_resource(resource);
    if (bitmap == NULL) {
        switch_bitmap(-value);
    }
    else {
        bitmap_layer_set_bitmap(bitmap_layer, bitmap);
        layer_mark_dirty(bitmap_layer_get_layer(bitmap_layer));
    }
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    switch_bitmap(-1);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    switch_bitmap(+1);
}

static void click_handlers(void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
    bitmap_layer = bitmap_layer_create(bounds);
    resource = 1;
    bitmap = gbitmap_create_with_resource(resource);
    bitmap_layer_set_bitmap(bitmap_layer, bitmap);
    bitmap_layer_set_alignment(bitmap_layer, GAlignCenter);
    layer_add_child(window_layer, bitmap_layer_get_layer(bitmap_layer));
    bitmap_layer_set_compositing_mode(bitmap_layer, GCompOpSet);
}

static void window_unload(Window *window) {
    bitmap_layer_destroy(bitmap_layer);
    gbitmap_destroy(bitmap);
}

static void init() {
    window = window_create();
    window_set_click_config_provider(window, click_handlers);
    window_set_window_handlers(window, (WindowHandlers) {
            .load = window_load,
            .unload = window_unload,
    });
    window_stack_push(window, true);
}

static void deinit(void) {
    window_destroy(window);
}

int main(void) {
    init();
    app_event_loop();
    deinit();
    return 0;
}
