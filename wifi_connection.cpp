#include "constants.h"
#include "prototypes.h"

void wifi_conn_pre();
void wifi_conn_wifi_ap();
void wifi_conn_wifi_st();
void wifi_conn_mdns();
void wifi_conn_server();

wifi_settings_t wc_wifi_settings;

int wifi_state_no;
connect_cb_t wifi_on_connect_cb;
error_cb_t wifi_on_error_cb;
unset_cb_t wifi_on_unset_cb;

bool wifi_is_connected = false;

void set_wifi_settings(wifi_settings_t &wifi_settings) {
  wc_wifi_settings = wifi_settings;
}

wifi_settings_t& get_wifi_settings() {
  return wc_wifi_settings;
}

void wifi_connect(int state_no, connect_cb_t on_connect, error_cb_t on_error, unset_cb_t on_unset) {
  if (wifi_is_connected) {
    on_connect();
    return;
  }
  wifi_state_no = state_no;
  wifi_on_connect_cb = on_connect;
  wifi_on_error_cb = on_error;
  wifi_on_unset_cb = on_unset;
  set_state(wifi_conn_pre, wifi_state_no);
}

void wifi_disconnect() {
  if (!wifi_is_connected) return;
  server_close();
  MDNS.end();
  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  wifi_is_connected = false;
}

void wifi_conn_pre() {
  if (!wc_wifi_settings.is_set) {
    if (wifi_on_unset_cb) {
      wifi_on_unset_cb();
    } else {
      set_state(EMPTY_STATE_FUNC, wifi_state_no);
    }
    return;
  }
  wifi_disconnect();
  if (wc_wifi_settings.is_ap) {
    set_state(wifi_conn_wifi_ap, wifi_state_no);
  } else {
    set_state(wifi_conn_wifi_st, wifi_state_no);
  }
}

void wifi_conn_wifi_ap() {
  Serial.println("Starting in AP Mode");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(wc_wifi_settings.ssid, wc_wifi_settings.psk);
  Serial.println("WiFi hotspot activated");
  Serial.println(WiFi.softAPIP());
  set_state(wifi_conn_mdns, wifi_state_no);
}

void wifi_conn_wifi_st() {
  Serial.println("Starting in ST Mode");
  WiFi.mode(WIFI_STA);
  WiFi.begin(wc_wifi_settings.ssid, wc_wifi_settings.psk);
  set_state([]() {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("WiFi connected");
      Serial.println(WiFi.localIP());
      set_state(wifi_conn_mdns, wifi_state_no);
    }
  }, wifi_state_no);
}

void wifi_conn_mdns() {
  if (wc_wifi_settings.enable_mdns) {
    Serial.println("Initializing MDns...");
    MDNS.begin(WiFi.getHostname());
    MDNS.addService((const char*)&wc_wifi_settings.mdns_sname, "tcp", wc_wifi_settings.tcp_port);
    Serial.println("MDns responder running");
  }
  set_state(wifi_conn_server, wifi_state_no);
}

void wifi_conn_server() {
  Serial.println("Initializing Server...");
  server_initialize(wc_wifi_settings.tcp_port);
  set_state(EMPTY_STATE_FUNC, wifi_state_no);
  wifi_is_connected = true;
  wifi_on_connect_cb();
}

void wifi_update() {
  //TODO: poll for Wifi status then update wifi_is_connected accordingly
}
