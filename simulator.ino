#include "constants.h"
#include "prototypes.h"

#define STATE_COUNT 3

state_func_t states[STATE_COUNT];

void set_state(state_func_t func, int no) {
  states[no] = func;
}

void delayed_set_state(state_func_t func, int no, long ms) {
  long start = millis();
  set_state(
    [start, func, no, ms] () mutable {
      if (millis() - start >= ms) {
        states[no] = func;
        start = millis();
      }
    },
    no
  );
}

void wifi_set_default() {
  wifi_settings_t wifi_settings;
  wifi_settings.is_set = true;
  wifi_settings.is_ap = true;
  strcpy(wifi_settings.ssid, ANALYZER_NAME);
  wifi_settings.tcp_port = ANALYZER_TCP_PORT;
  strcpy(wifi_settings.psk, ANALYZER_DEF_PSK);
  strcpy(wifi_settings.mdns_sname, ANALYZER_MDNS_SNAME);
  set_wifi_settings(wifi_settings);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  message_init();
  param_set_defaults();
  wifi_set_default();
  wifi_connect(
    MAIN_STATE_NO,
    []() { //on_connect
      set_state(interactive_main, MAIN_STATE_NO);
    },
    []() { //on_error
      Serial.println("ERROR: Wifi connection");
    }
  );
}

void loop() {
  wifi_update();
  server_update();
  for (int idx = 0; idx < STATE_COUNT; idx++) {
    auto state = states[idx];
    if (state) {
      state();
    }
  }
  yield();
}
