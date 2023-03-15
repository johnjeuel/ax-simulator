#include "constants.h"
#include "prototypes.h"

#define EOC_1 '\n'
#define EOC_2 ';'

void read_input_proc();

int ri_num_read = 0;
char ri_buffer[1024];
input_cb_t on_input_cb;
error_cb_t on_error_cb;

void read_input(int state_no, input_cb_t on_input, error_cb_t on_error) {
  on_input_cb = on_input;
  on_error_cb = on_error;
  ri_num_read = 0;
  set_state(read_input_proc, state_no);
}

void read_int(int state_no, input_int_cb_t on_input, error_cb_t on_error, empty_cb_t on_empty) {
  read_input(
  state_no,
  [on_input, on_error, on_empty] (const char* buffer, int len) {
    if (len == 0) {
      if (on_empty) {
        on_empty();
      } else {
        on_error();
      }
      return;
    }
    int value = 0;
    int result = sscanf(buffer, "%d", &value);
    if (result != 1) {
      on_error();
      return;
    }
    on_input(value);
  }, on_error);
}

void read_yesno(int state_no, input_yesno_cb_t on_input, error_cb_t on_error, empty_cb_t on_empty) {
  read_input(
  state_no,
  [on_input, on_error, on_empty] (const char* buffer, int len) {
    if (len == 0) {
      if (on_empty) {
        on_empty();
      } else {
        on_error();
      }
      return;
    }
    if (strcmp(buffer, "YES") == 0 ||
        strcmp(buffer, "Yes") == 0 ||
        strcmp(buffer, "yes") == 0 ||
        strcmp(buffer, "1") == 0) {
      on_input(true);
    } else if (strcmp(buffer, "NO") == 0 ||
               strcmp(buffer, "No") == 0 ||
               strcmp(buffer, "no") == 0 ||
               strcmp(buffer, "0") == 0) {
      on_input(false);
    } else {
      on_error();
    }
  }, on_error);
}

void read_input_proc() {
  if (Serial.available()) {
    byte c = Serial.read();
    if (c == EOC_1 || c == EOC_2) {
      ri_buffer[ri_num_read] = 0;
      on_input_cb(ri_buffer, ri_num_read);
      ri_num_read = 0;
      ri_buffer[0] = 0;
    } else {
      ri_buffer[ri_num_read++] = (char)c;
    }
  }
}
