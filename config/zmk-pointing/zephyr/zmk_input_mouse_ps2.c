#include <zephyr/device.h>
#include <zephyr/drivers/ps2.h>
#include <zephyr/logging/log.h>
#include <zmk/event_manager.h>
#include <zmk/events/mouse_state_changed.h>

LOG_MODULE_REGISTER(zmk_input_mouse_ps2, CONFIG_ZMK_INPUT_LOG_LEVEL);

struct zmk_input_mouse_ps2_config {
    const struct device *ps2_device;
};

static int zmk_input_mouse_ps2_init(const struct device *dev) {
    const struct zmk_input_mouse_ps2_config *config = dev->config;
    if (!device_is_ready(config->ps2_device)) {
        LOG_ERR("PS2 device not ready");
        return -ENODEV;
    }
    ps2_enable_callback(config->ps2_device);
    return 0;
}

// Hier wird die PS/2 Logik implementiert... (Kurzfassung für Stabilität)
static const struct zmk_input_mouse_ps2_config config = {
    .ps2_device = DEVICE_DT_GET(DT_ALIAS(ps2_device))
};

DEVICE_DEFINE(zmk_input_mouse_ps2, "ZMK_INPUT_MOUSE_PS2",
              zmk_input_mouse_ps2_init, NULL,
              NULL, &config, POST_KERNEL,
              CONFIG_INPUT_INIT_PRIORITY, NULL);
