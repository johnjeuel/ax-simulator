#include "constants.h"
#include "prototypes.h"


void receive_mode_ask_acknak();
void receive_mode_ask_data();
void receive_mode_pre_update();
void receive_mode_update();
void receive_mode_post_update();

int rm_cur_sequence = 0;
state_func_t rm_sequence[] = {
  receive_mode_ask_acknak,
  receive_mode_ask_data,
  receive_mode_pre_update,
  receive_mode_update,
  receive_mode_post_update
};

#define RM_NEXT_STATE() set_state(rm_sequence[++rm_cur_sequence], MAIN_STATE_NO)
#define RM_SAME_STATE() set_state(rm_sequence[rm_cur_sequence], MAIN_STATE_NO)

bool rm_update_running = false;
int rm_empty_lines = 0;

void receive_mode_init() {
  wifi_connect(
    MAIN_STATE_NO,
    []() { //on_connect
      Serial.println("=== Receive mode ===");
      rm_cur_sequence = 0;
      set_state(rm_sequence[rm_cur_sequence], MAIN_STATE_NO);
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

void receive_mode_ask_acknak() {
  Serial.print("Ack/Nak? ");
  read_input(
  MAIN_STATE_NO,
  [] (const char *buffer, int len) { //on_input
    if (strcmp(buffer, "ACK") == 0 || 
        strcmp(buffer, "Ack") == 0 || 
        strcmp(buffer, "ack") == 0) {
      Serial.println("ACK");
      message_set_ctrl(RM_MSG_NO_SEND, MESSAGE_ACK);
    } else if (strcmp(buffer, "NAK") == 0 || 
               strcmp(buffer, "Nak") == 0 || 
               strcmp(buffer, "nak") == 0) {
      Serial.println("NAK");
      message_set_ctrl(RM_MSG_NO_SEND, MESSAGE_NAK);
    } else {
      Serial.println("Enter valid option"); 
      RM_SAME_STATE();
      return;
    }
    RM_NEXT_STATE();
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    RM_SAME_STATE();
  });
}

void receive_mode_ask_data() {
  Serial.print("Has Data (yes/no)? ");
  read_yesno(
  MAIN_STATE_NO,
  [] (bool is_yes) { //on_input
    if (is_yes) {
      Serial.println("YES"); 
      message_clear_data(RM_MSG_NO_SEND);
      data_input(
      MAIN_STATE_NO,
      RM_MSG_NO_SEND,
      [] () { //on_complete
        RM_NEXT_STATE();
      },
      [] () { //on_error
        RM_SAME_STATE();
      });
    } else {
      Serial.println("NO"); 
      RM_NEXT_STATE();
    }
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    RM_SAME_STATE();
  });
}

void receive_mode_pre_update() {
  rm_empty_lines = 0;
  read_input(
  BG_PROC_STATE_NO,
  [] (const char *buffer, int len) { //on_input
    if (len == 0) {
      rm_empty_lines++;
      if (rm_empty_lines == 2) {
        set_state(EMPTY_STATE_FUNC, BG_PROC_STATE_NO);
        rm_update_running = false;
      }
      return;
    }
    rm_empty_lines = 0;
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    rm_empty_lines = 0;
  });
  rm_update_running = true;
  RM_NEXT_STATE();
  Serial.println("Receive mode running");
  Serial.println("Enter an empty line twice to exit");
}

void receive_mode_update() {
  if (!rm_update_running) {
    RM_NEXT_STATE();
    return;
  }
  if (message_recv(RM_MSG_NO_RECV)) {
    message_set_opcode(RM_MSG_NO_SEND, message_get_opcode(RM_MSG_NO_RECV));
    message_send(RM_MSG_NO_SEND);
  }
}

void receive_mode_post_update() {
  set_state(interactive_main, MAIN_STATE_NO);
}
