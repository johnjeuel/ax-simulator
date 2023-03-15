#include "constants.h"
#include "prototypes.h"

void param_edit_ope_mode();
void param_edit_device_name();
void param_edit_serial_no();
void param_edit_led_r();
void param_edit_led_g();
void param_edit_led_b();
void param_edit_end();

state_func_t pe_sequence[] = {
  param_edit_ope_mode,
  param_edit_device_name,
  param_edit_serial_no,
  param_edit_led_r,
  param_edit_led_g,
  param_edit_led_b,
  param_edit_end
};
int pe_cur_sequence = 0;

#define PE_NEXT_STATE() set_state(pe_sequence[++pe_cur_sequence], MAIN_STATE_NO)
#define PE_SAME_STATE() set_state(pe_sequence[pe_cur_sequence], MAIN_STATE_NO)

void param_edit_init() {
  Serial.println("=== Edit Params ===");
  pe_cur_sequence = 0;
  set_state(pe_sequence[pe_cur_sequence], MAIN_STATE_NO);
}

void param_edit_ope_mode() {
  Serial.print("Operation mode?(");
  Serial.print(param_get_ope_mode());
  Serial.print(") ");
  read_input(
  MAIN_STATE_NO,
  [] (const char *buffer, int len) { //on_input
    if (strcmp(buffer, "EL") == 0 || 
        strcmp(buffer, "el") == 0) {
      Serial.println("EL");
      param_set_ope_mode(ANALYZER_OPE_MODE_EL);
    } else if (strcmp(buffer, "CF") == 0 || 
               strcmp(buffer, "cf") == 0) {
      Serial.println("CF");
      param_set_ope_mode(ANALYZER_OPE_MODE_CF);
    } else if (len < 0 || len > 0) {
      Serial.println("Enter valid option"); 
      PE_SAME_STATE();
      return;
    } else {
      Serial.println();
    }
    PE_NEXT_STATE();
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    PE_SAME_STATE();
  });
}

void param_edit_device_name() {
  Serial.print("Device name?(");
  Serial.print(param_get_device_name());
  Serial.print(") ");
  read_input(
  MAIN_STATE_NO,
  [] (const char *buffer, int len) { //on_input
    if (len != 0) {
      Serial.println(buffer);
      param_set_device_name(buffer);
    } else {
      Serial.println();
    }
    PE_NEXT_STATE();
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    PE_SAME_STATE();
  });
}

void param_edit_serial_no() {
  Serial.print("Serial Number?(");
  Serial.print(param_get_serial_no());
  Serial.print(") ");
  read_input(
  MAIN_STATE_NO,
  [] (const char *buffer, int len) { //on_input
    if (len != 0) {
      Serial.println(buffer);
      param_set_serial_no(buffer);
    } else {
      Serial.println();
    }
    PE_NEXT_STATE();
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    PE_SAME_STATE();
  });
}

void param_edit_led_r() {
  Serial.print("LED Red channel?(");
  Serial.print(param_get_led_r());
  Serial.print(") ");
  read_int(
  MAIN_STATE_NO,
  [] (int value) { //on_input
    if (value < 0 || value > 255) {
      Serial.println("Out of range (0-255)");
      PE_SAME_STATE();
    } else {
      Serial.println(value);
      param_set_led_r((byte)value);
      PE_NEXT_STATE();
    }
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    PE_SAME_STATE();
  },
  [] () { //on_empty
    Serial.println();
    PE_NEXT_STATE();
  });
}

void param_edit_led_g() {
  Serial.print("LED Green channel?(");
  Serial.print(param_get_led_g());
  Serial.print(") ");
  read_int(
  MAIN_STATE_NO,
  [] (int value) { //on_input
    if (value < 0 || value > 255) {
      Serial.println("Out of range (0-255)");
      PE_SAME_STATE();
    } else {
      Serial.println(value);
      param_set_led_g((byte)value);
      PE_NEXT_STATE();
    }
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    PE_SAME_STATE();
  },
  [] () { //on_empty
    Serial.println();
    PE_NEXT_STATE();
  });
}

void param_edit_led_b() {
  Serial.print("LED Blue channel?(");
  Serial.print(param_get_led_b());
  Serial.print(") ");
  read_int(
  MAIN_STATE_NO,
  [] (int value) { //on_input
    if (value < 0 || value > 255) {
      Serial.println("Out of range (0-255)");
      PE_SAME_STATE();
    } else {
      Serial.println(value);
      param_set_led_b((byte)value);
      PE_NEXT_STATE();
    }
  },
  [] () { //on_error
    Serial.println("ERROR: Invalid input");
    PE_SAME_STATE();
  },
  [] () { //on_empty
    Serial.println();
    PE_NEXT_STATE();
  });
}

void param_edit_end() {
  set_state(interactive_main, MAIN_STATE_NO);
}
