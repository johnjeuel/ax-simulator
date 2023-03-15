#include "constants.h"
#include "prototypes.h"

void interactive_main() {
  Serial.print("Device Name: ");
  Serial.println(param_get_device_name());
  Serial.print("Serial No: ");
  Serial.println(param_get_serial_no());
  Serial.println("=== Select ===");
  Serial.println("1 Receive Mode");
  Serial.println("2 Send Mode");
  Serial.println("3 Analyzer Simulator Mode");
  Serial.println("4 Wifi Setup");
  Serial.println("5 Edit Params");
  Serial.println("6 Analyzer Simulator with Error PopUP");
  Serial.println("7 Analyzer Simulator MeasInfo Status Mode");
  Serial.println("8 Analyzer Simulator Image Mode");
  Serial.println("9 Error Display Mode");

  read_int(
  MAIN_STATE_NO,
  [] (int value) { // on_input
    switch (value) {
      case 1:
      set_state(receive_mode_init, MAIN_STATE_NO);
      break;
      case 2:
      set_state(send_mode_init, MAIN_STATE_NO);
      break;
      case 3:
      set_state(sim_init, MAIN_STATE_NO);
      break;
      case 4:
      set_state(wifi_setup_init, MAIN_STATE_NO);
      break;
      case 5:
      set_state(param_edit_init, MAIN_STATE_NO);
      break;
      case 6:
      set_state(sim_error_popUp, MAIN_STATE_NO);
      break;
      case 7:
      set_state(sim_meas_long, MAIN_STATE_NO);
      break;
      case 8:
      set_state(sim_meas_image, MAIN_STATE_NO);
      break;
	  case 9:
      set_state(sim_error_popUp_forced_init, MAIN_STATE_NO);
      break;

      default:
      Serial.println("ERROR: Enter valid option");
      set_state(interactive_main, MAIN_STATE_NO);
      break;
    }
    return false;
  }, 
  [] () { // on_error
    Serial.println("ERROR: Input error");
    set_state(interactive_main, MAIN_STATE_NO);
  });
}
