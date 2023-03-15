#include "constants.h"
#include "prototypes.h"

void wifi_setup_ask_apst();
void wifi_setup_ask_ssid();
void wifi_setup_ask_psk();
void wifi_setup_ask_tcp_port();
void wifi_setup_ask_enable_mdns();
void wifi_setup_ask_mdns_sname();
void wifi_setup_end();

int ws_cur_sequence = 0;
state_func_t ws_sequence[] = {
  wifi_setup_ask_apst,
  wifi_setup_ask_ssid,
  wifi_setup_ask_psk,
  wifi_setup_ask_tcp_port,
  wifi_setup_ask_enable_mdns,
  wifi_setup_ask_mdns_sname,
  wifi_setup_end
};

#define WS_NEXT_STATE() set_state(ws_sequence[++ws_cur_sequence], MAIN_STATE_NO)
#define WS_SAME_STATE() set_state(ws_sequence[ws_cur_sequence], MAIN_STATE_NO)

wifi_settings_t ws_wifi_settings;

void wifi_setup_init() {
  Serial.println("=== Wifi Setup ===");
  ws_wifi_settings = get_wifi_settings();
  ws_cur_sequence = 0;
  set_state(ws_sequence[ws_cur_sequence], MAIN_STATE_NO);
}

void wifi_setup_ask_apst() {
  Serial.print("AP/ST? (");
  if (ws_wifi_settings.is_ap) {
    Serial.print("AP");
  } else {
    Serial.print("ST");
  }
  Serial.print(") ");
  read_input(
  MAIN_STATE_NO,
  [] (const char *buffer, int len) { //on_input
    if (strcmp(buffer, "AP") == 0 || 
        strcmp(buffer, "ap") == 0) {
      Serial.println("AP");
      ws_wifi_settings.is_ap = true;
    } else if (strcmp(buffer, "ST") == 0 || 
               strcmp(buffer, "st") == 0) {
      Serial.println("ST");
      ws_wifi_settings.is_ap = false;
    } else if (len < 0 || len > 0) {
      Serial.println("Enter valid option"); 
      WS_SAME_STATE();
      return;
    } else {
      Serial.println();
    }
    WS_NEXT_STATE();
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    WS_SAME_STATE();
  });
}

void wifi_setup_ask_ssid() {
  Serial.print("SSID?(");
  Serial.print(ws_wifi_settings.ssid);
  Serial.print(") ");
  read_input(
  MAIN_STATE_NO,
  [] (const char *buffer, int len) { //on_input
    if (len > 0) {
      Serial.println(buffer);
      strcpy(ws_wifi_settings.ssid, buffer);
    } else {
      Serial.println();
    }
    WS_NEXT_STATE();
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    WS_SAME_STATE();
  });
}

void wifi_setup_ask_psk() {
  Serial.print("PSK? ");
  read_input(
  MAIN_STATE_NO,
  [] (const char *buffer, int len) { //on_input
    if (len == 0) {
      Serial.println();
      WS_NEXT_STATE();
      return;
    }
    if (len < 8) {
      Serial.println("Must be >= 8 characters");
      WS_SAME_STATE();
      return;
    }
    Serial.println("********");
    strcpy(ws_wifi_settings.psk, buffer);
    WS_NEXT_STATE();
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    WS_SAME_STATE();
  });
}

void wifi_setup_ask_tcp_port() {
  Serial.print("TCP Port?(");
  Serial.print(ws_wifi_settings.tcp_port);
  Serial.print(") ");
  read_int(
  MAIN_STATE_NO,
  [] (int value) { //on_input
    if (value < 0 || value > 65535) {
      Serial.println("Out of range");
      WS_SAME_STATE();
      return;
    }
    Serial.println(value);
    ws_wifi_settings.tcp_port = value;
    WS_NEXT_STATE();
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    WS_SAME_STATE();
  },
  [] () { //on_empty
    Serial.println();
    WS_NEXT_STATE();
  });
}

void wifi_setup_ask_enable_mdns() {
  Serial.print("Enable MDns? (");
  if (ws_wifi_settings.enable_mdns) {
    Serial.print("YES");
  } else {
    Serial.print("NO");
  }
  Serial.print(") ");
  read_yesno(
  MAIN_STATE_NO,
  [] (bool is_yes) { //on_input
    if (is_yes) {
      Serial.println("YES");
      ws_wifi_settings.enable_mdns = true;
      WS_NEXT_STATE();
    } else {
      Serial.println("NO");
      ws_wifi_settings.enable_mdns = false;
      WS_NEXT_STATE(); //Skip ask MDns service name
      WS_NEXT_STATE(); //Actual state
    }
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    WS_SAME_STATE();
  },
  [] () {
    Serial.println();
    if (ws_wifi_settings.enable_mdns) {
      WS_NEXT_STATE();
    } else {
      WS_NEXT_STATE(); //Skip ask MDns service name
      WS_NEXT_STATE(); //Actual state
    }
  }
  );
}

void wifi_setup_ask_mdns_sname() {
  Serial.print("MDns service name?(");
  Serial.print(ws_wifi_settings.mdns_sname);
  Serial.print(") ");
  read_input(
  MAIN_STATE_NO,
  [] (const char *buffer, int len) { //on_input
    if (len > 0) {
      Serial.println(buffer);
      strcpy(ws_wifi_settings.mdns_sname, buffer);
    } else {
      Serial.println();
    }
    WS_NEXT_STATE();
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    WS_SAME_STATE();
  });
}

void wifi_setup_end() {
  ws_wifi_settings.is_set = true;
  set_wifi_settings(ws_wifi_settings);
  wifi_disconnect();
  wifi_connect(
    MAIN_STATE_NO,
    []() { //on_connect
      set_state(interactive_main, MAIN_STATE_NO);
    },
    []() { //on_error
      Serial.println("ERROR: Wifi connection");
      set_state(interactive_main, MAIN_STATE_NO);
    }
  );
}
