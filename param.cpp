#include "constants.h"
#include "prototypes.h"

char param_ope_mode[3];
char param_device_name[32];
char param_serial_no[32];
byte param_led_r;
byte param_led_g;
byte param_led_b;

void param_set_defaults() {
  strcpy(param_ope_mode, ANALYZER_OPE_MODE_EL);
  strcpy(param_device_name, ANALYZER_NAME);
  strcpy(param_serial_no, ANALYZER_SERIAL_NO);
  param_led_r = DUMMY_LED_R;
  param_led_g = DUMMY_LED_G;
  param_led_b = DUMMY_LED_B;
}

const char* param_get_ope_mode() {
  return param_ope_mode;
}

void param_set_ope_mode(const char *value) {
  strcpy(param_ope_mode, value);
}

const char* param_get_device_name() {
  return param_device_name;
}

void param_set_device_name(const char *value) {
  strcpy(param_device_name, value);
}

const char* param_get_serial_no() {
  return param_serial_no;
}

void param_set_serial_no(const char *value) {
  strcpy(param_serial_no, value);
}

byte param_get_led_r() {
  return param_led_r;
}

void param_set_led_r(byte value) {
  param_led_r = value;
}

byte param_get_led_g() {
  return param_led_g;
}

void param_set_led_g(byte value) {
  param_led_g = value;
}

byte param_get_led_b() {
  return param_led_b;
}

void param_set_led_b(byte value) {
  param_led_b = value;
}
