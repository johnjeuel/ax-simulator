#include "constants.h"
#include "prototypes.h"

#define SM_MSG_NO_SEND 0
#define SM_MSG_NO_RECV 1

void send_mode_ask_opcode();
void send_mode_ask_data();
void send_mode_ask_repeat();
void send_mode_ask_repeat_interval();
void send_mode_pre_update();
void send_mode_update();
void send_mode_post_update();

int sm_cur_sequence = 0;
state_func_t sm_sequence[] = {
  send_mode_ask_opcode,
  send_mode_ask_data,
  send_mode_ask_repeat,
  send_mode_ask_repeat_interval,
  send_mode_pre_update,
  send_mode_update,
  send_mode_post_update
};

#define SM_NEXT_STATE() set_state(sm_sequence[++sm_cur_sequence], MAIN_STATE_NO)
#define SM_SAME_STATE() set_state(sm_sequence[sm_cur_sequence], MAIN_STATE_NO)

bool sm_update_running = false;
int sm_empty_lines = 0;

bool sm_is_repeat = false;
int sm_repeat_interval = 500;
long sm_repeat_start = 0;

void send_mode_init() {
  wifi_connect(
    MAIN_STATE_NO,
    []() { //on_connect
      Serial.println("=== Send mode ===");
      sm_cur_sequence = 0;
      sm_is_repeat = false;
      sm_repeat_interval = 500;
      message_set_ctrl(SM_MSG_NO_SEND, MESSAGE_ENQ);
      set_state(sm_sequence[sm_cur_sequence], MAIN_STATE_NO);
    },
    []() { //on_error
      Serial.println("Error in starting Wifi");
      set_state(interactive_main, MAIN_STATE_NO);
    },
    []() { //on_unset
      Serial.println("Wifi settings is not configured");
      set_state(interactive_main, MAIN_STATE_NO);
    }
  );
}

void send_mode_ask_opcode() {
  Serial.print("Opcode? ");
  read_int(
  MAIN_STATE_NO,
  [] (int value) { //on_input
    Serial.println(value);
    message_set_opcode(SM_MSG_NO_SEND, value);
    SM_NEXT_STATE();
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    SM_SAME_STATE();
  });
}

void send_mode_ask_data() {
  Serial.print("Has Data (yes/no)? ");
  message_clear_data(SM_MSG_NO_SEND);
  read_yesno(
  MAIN_STATE_NO,
  [] (bool is_yes) { //on_input
    if (is_yes) {
      Serial.println("YES"); 
      data_input(
      MAIN_STATE_NO,
      SM_MSG_NO_SEND,
      [] () { //on_complete
        SM_NEXT_STATE();
      },
      [] () { //on_error
        SM_SAME_STATE();
      });
    } else {
      Serial.println("NO"); 
      SM_NEXT_STATE();
    }
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    SM_SAME_STATE();
  });
}

void send_mode_ask_repeat() {
  Serial.print("Repeat (yes/no)? ");
  read_yesno(
  MAIN_STATE_NO,
  [] (bool is_yes) { //on_input
    if (is_yes) {
      sm_is_repeat = true;
      Serial.println("YES");
      SM_NEXT_STATE();
    } else {
      sm_is_repeat = false;
      Serial.println("NO");
      SM_NEXT_STATE(); //Skip ask interval
      SM_NEXT_STATE(); //Actual state
    }
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    SM_SAME_STATE();
  });
}

void send_mode_ask_repeat_interval() {
  Serial.print("Repeat interval (ms)? ");
  read_int(
  MAIN_STATE_NO,
  [] (int value) { //on_input
    if (value < 500) {
      Serial.println("Too fast (>= 500ms)");
      SM_SAME_STATE();
    } else {
      Serial.print(value);
      Serial.println("ms");
      sm_repeat_interval = value;
      SM_NEXT_STATE();
    }
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    SM_SAME_STATE();
  });
}

void send_mode_pre_update() {
  sm_empty_lines = 0;
  read_input(
  BG_PROC_STATE_NO,
  [] (const char *buffer, int len) { //on_input
    if (len == 0) {
      sm_empty_lines++;
      if (sm_empty_lines == 2) {
        set_state(EMPTY_STATE_FUNC, BG_PROC_STATE_NO);
        sm_update_running = false;
      }
      return;
    }
    sm_empty_lines = 0;
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    sm_empty_lines = 0;
  });
  sm_update_running = true;
  Serial.println("Send mode running");
  Serial.println("Enter an empty line twice to exit");
  Serial.println("Waiting for client to initiate...");
  set_state([]() {
    if (message_recv(SM_MSG_NO_RECV)) {
      message_set_ctrl(SM_MSG_NO_RECV, MESSAGE_ACK);
      message_clear_data(SM_MSG_NO_RECV);
      message_send(SM_MSG_NO_RECV); //Response
      SM_NEXT_STATE();
    }
  }, MAIN_STATE_NO);
}

void send_mode_update() {
  message_send(SM_MSG_NO_SEND);
  set_state([]() {
    if (message_recv(SM_MSG_NO_RECV)) { //Read response
      if (sm_is_repeat) {
        sm_repeat_start = millis();
        set_state([]() { //Wait for next sending
          if (!sm_update_running) {
            SM_NEXT_STATE();
            return;
          }
          if (millis() - sm_repeat_start >= sm_repeat_interval) {
            SM_SAME_STATE();
          }
        }, MAIN_STATE_NO);
      } else {
        SM_NEXT_STATE();
      }
    }
  }, MAIN_STATE_NO);
}

void send_mode_post_update() {
  set_state(interactive_main, MAIN_STATE_NO);
}
