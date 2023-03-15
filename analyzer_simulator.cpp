#include "constants.h"
#include "prototypes.h"

#define SIM_STATE_CHANGE_MSG_NO 0
#define SIM_COMPLETION_MSG_NO 0
#define SIM_BARCODE_MSG_NO 0
#define SIM_MEASINFO_MSG_NO 0
#define SIM_MENU_MSG_NO 0
#define SIM_MEAS_TIME_MSG_NO 0
#define SIM_TIP_CASE_MSG_NO 0
#define SIM_MEAS_RESULT_MSG_NO 0
#define SIM_MEAS_IMAGE_MSG_NO 0
#define SIM_SYSTEMLOG_MSG_NO 0
#define SIM_ERRORCODE_MSG_NO 0
#define SIM_EXT_REQUEST_MSG_NO 1

#define SIM_SINGLE_DEFAULT_TIME 30
#define SIM_MULTI_DEFAULT_TIME 30
#define SIM_EL_DEFAULT_TIME 30

#define SIM_INITIALIZING_DELAY 3000
#define SIM_WARMING_UP_DELAY 3000
#define SIM_COVER_OPEN_DELAY 5000
#define SIM_COVER_CLOSE_DELAY 5000
#define SIM_MENU_STANDBY_TIMEOUT 5000
#define SIM_MEAS_STANDBY_TIMEOUT 5 * 60 * 1000
#define SIM_MEAS_RESULT_INTERVAL 2000

void sim_wait_for_client();
void sim_wait_for_initial_get_status();
void sim_warming_up();
void sim_standby();
void sim_measurement_standby_update();
void sim_measurement_standby();
void sim_measuring();
void sim_meas_cover_open();
void sim_meas_cover_close();
void sim_send_barcode();
void sim_send_measinfo();
void sim_send_menurep();
void sim_send_meas_time();
void sim_send_tip_case();
void sim_measuring_pre_update();
void sim_measuring_update();
void sim_update_meas_time();
void sim_result(int, int);
void sim_image_mode();
void sim_image(int, int, int, int);
void sim_send_errorCode();
void sim_send_errorCode_forced();
void sim_on_system_version();


void sim_ext_request_proc();

void sim_wait_response(cb_func_t on_ack, cb_func_t on_nak = cb_func_t());
void sim_change_state(int,int, cb_func_t);


//Status Change parameters
char serialnumber[255] = "12345678^123";
int sim_state = STATE_INITIALIZING;
int message_state = MESSAGE_WAITING;
int calib_state = CALB_STATE_INIT;

int icon_remote_maintenance = ICON_NO_SETTINGS;
int icon_waste_tray = ICON_NO_SETTINGS;
int icon_disposal = ICON_NO_SETTINGS;
int icon_washing_liquid = ICON_NO_SETTINGS;
int icon_host_connection = ICON_NO_SETTINGS;
int icon_printer_connection = ICON_NO_SETTINGS;
int icon_printer_paper = ICON_NO_SETTINGS;
int icon_feeder_paper = ICON_NO_SETTINGS;
int icon_remaining_test_strip = ICON_NO_SETTINGS;
int icon_stat_reservation = ICON_NO_SETTINGS;

int measNUmber_Normal = 0;
int measNUmber_PortCup = 0;
int measNUmber_RackStat = 0;
int measNUmber_Control = 0;


bool sim_has_response = false;

int sim_single_remain = 0;
int sim_multi_remain = 0;
int sim_el_remain = 0;

int sim_meas_cur_channel = 1;

long sim_meas_time_snap = 0;
long sim_meas_time_drift = 0;
long sim_meas_start = 0;

bool sim_setup_measurement_call = false;
bool sim_start_measurement_call = false;
bool sim_stat_start_measurement_call = false;
bool sim_stop_measurement_call = false;
bool sim_stop_measurement_menu_call = false;
bool sim_shutdown_menu_call = false;
bool sim_end_measurement_call = false;
bool sim_meas_cover_open_call = false;
bool sim_meas_errorpopUp_call = false;
bool sim_error_popUp_call = false;
bool sim_start_measlong_call = false;
bool sim_start_measimage_call = false;
bool sim_req_measimage_call = false;

int sim_start_cond_meas_no = 0;
char sim_start_cond_sample_id[18 + 1];
char sim_start_cond_operator_id[18 + 1];
int sim_start_cond_sample_type = 1;
int sim_start_cond_patient_type = 1;

int sim_stat_cond_mode = 0;
int sim_stat_cond_meas_no = 0;
char sim_stat_cond_meas_id[16 + 1];
int sim_stat_cond_meas_feeder = 0;

long sim_meas_standby_start = 0;
long menu_standby_start = 0;
long menu_stop_standby_start = 0;
long shutdown_standby_start = 0;
long menu_resume_timer = 5000;

long sim_start_wait_response;
int statuscnt = 0;
int imagecounter = 0;
int imagenumber = 0;
int vercounter = 0;
int rm_empty_lines2 = 0;
int priority_stat = 0;
int meas_id = 1;

error_code_t wc_error_code;

void set_error_code(error_code_t& error_code) {
    wc_error_code = error_code;
}

error_code_t& get_error_code() {
    return wc_error_code;
}

menu_mode_t wc_menu_mode;
void set_menu_mode(menu_mode_t& menu_mode) {
    wc_menu_mode = menu_mode;
}

menu_mode_t& get_menu_mode() {
    return wc_menu_mode;
}

common_adj_t wc_adj_common;
void set_adj_common(common_adj_t& adj_common) {
    wc_adj_common = adj_common;
}

common_adj_t& get_adj_common() {
    return wc_adj_common;
}

all_adj_t wc_adj_all;
void set_adj_all(all_adj_t& adj_all) {
    wc_adj_all = adj_all;
}

all_adj_t& get_adj_all() {
    return wc_adj_all;
}

void sim_init() {
  // initialize buffers 
	all_adj_t local_adj;

	strcpy(local_adj.pulse_adj.read_defaultpls, "999");
	strcpy(local_adj.pulse_adj.read_currentpls, "999");
	strcpy(local_adj.intro_adj.read_defaultpls, "888");
	strcpy(local_adj.intro_adj.read_currentpls, "888");
	strcpy(local_adj.intro_adj.read_front_defaultpls, "777");
	strcpy(local_adj.intro_adj.read_front_currentpls, "777");
	strcpy(local_adj.intro_adj.read_delvry_defaultpls, "555");
	strcpy(local_adj.intro_adj.read_delvry_currentpls, "555");
	set_adj_all(local_adj);


  wifi_connect(
    MAIN_STATE_NO,
    []() { //on_connect
      Serial.println("=== Analyzer Simulator ===");
      set_state(sim_ext_request_proc, BG_PROC_STATE_NO);
      sim_change_state(STATE_INITIALIZING, MESSAGE_WAITING, []() {
        delayed_set_state(sim_wait_for_client, MAIN_STATE_NO, SIM_INITIALIZING_DELAY);
      });
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

void sim_error_popUp() {
    Serial.println("=== Error PopUp ===");
    Serial.print("Enter Error Number (ex. W100...");
    sim_meas_errorpopUp_call  = true;
    read_input(
        MAIN_STATE_NO,
        [](const char* buffer, int len) { //on_input
            if (len > 0) {
                Serial.println(buffer);
                strcpy(wc_error_code.error_PopUp_number, buffer);
            }
            else {
                Serial.println();
            }
            set_error_code(wc_error_code);
            set_state(sim_init, MAIN_STATE_NO);
        },
        []() { //on_error
            Serial.println("ERROR: Invalid input");
            set_state(sim_error_popUp, MAIN_STATE_NO);
        });
}

void sim_error_popUp_forced_init() {
	sim_error_popUp_call  = true;
	Serial.println("=== Error PopUp Mode ===");
	Serial.println("Press Feed then OK on the first connect..");
	set_state(sim_init, MAIN_STATE_NO);
}

void sim_waitingForRack() {
    Serial.println("=== WAITING FOR RACK ===");
	Serial.println("Enter an empty line to continue...");
    read_input(
        MAIN_STATE_NO,
        [](const char* buffer, int len) { //on_input
                Serial.println("OK");
				set_state(sim_waitingForRack_cont, MAIN_STATE_NO);
        },
        []() { //on_error
            Serial.println("ERROR: Invalid input");
            set_state(sim_waitingForRack, MAIN_STATE_NO);
        });
}

void sim_waitingForRack_cont() {
       set_state(sim_measurement_standby_update, MAIN_STATE_NO);
}



void sim_error_popUp_forced() {
    Serial.println("=== Error PopUp FORCED ===");
	Serial.println("Enter an empty line twice to exit");
    Serial.print("Enter Error Number (ex. W100...");
    read_input(
        MAIN_STATE_NO,
        [](const char* buffer, int len) { //on_input
            if (len > 0) {
                Serial.println(buffer);
                strcpy(wc_error_code.error_PopUp_number, buffer);
				set_error_code(wc_error_code);
				set_state(sim_send_errorCode_forced, MAIN_STATE_NO);
            }
            else {
                Serial.println();
				rm_empty_lines2++;
				if (rm_empty_lines2 == 2) {
					set_state(interactive_main, MAIN_STATE_NO);
					rm_empty_lines2 = 0;
					return;
				}
            }

        },
        []() { //on_error
            Serial.println("ERROR: Invalid input");
            set_state(sim_error_popUp_forced, MAIN_STATE_NO);
        });
}



void sim_meas_long() {
    sim_start_measlong_call = true;
    set_state(sim_init, MAIN_STATE_NO);
}
void sim_meas_image() {
    sim_start_measimage_call = true;
    set_state(sim_init, MAIN_STATE_NO);
}

void sim_wait_for_client() {
  Serial.println("Waiting for client to connect...");
  set_state([]() {
    if (server_get_client() != 0) {
      set_state(sim_warming_up, MAIN_STATE_NO);
    }
  }, MAIN_STATE_NO);
}

void sim_warming_up() {
  sim_change_state(STATE_WARMING_UP, MESSAGE_WAITING, [] () {
    delayed_set_state(sim_standby, MAIN_STATE_NO, SIM_WARMING_UP_DELAY);
  });
}

void sim_standby_update() {
  if (sim_meas_cover_open_call) {
    set_state(sim_meas_cover_open, MAIN_STATE_NO);
    return;
  }
}

void sim_standby() {
  sim_setup_measurement_call = false;
  sim_start_measurement_call = false;
  sim_stat_start_measurement_call = false;
  sim_end_measurement_call = false;
  sim_meas_cover_open_call = false;
  sim_stop_measurement_call = false;

  sim_change_state(STATE_STANDBY, MESSAGE_WAITING, []() {
    //set_state(sim_standby_update, MAIN_STATE_NO);
  });
}

void sim_meas_cover_open_compl() {
  sim_meas_standby_start = 0;
  Serial.println("Cover open for measurement complete");
  message_set_opcode(SIM_COMPLETION_MSG_NO, MESSAGE_OPCODE_COMPL_NTC);
  message_set_ctrl(SIM_COMPLETION_MSG_NO, MESSAGE_ENQ);
  message_clear_data(SIM_COMPLETION_MSG_NO);
  message_put_int(SIM_COMPLETION_MSG_NO, MESSAGE_OPCODE_COVER_OP);
  message_put_int(SIM_COMPLETION_MSG_NO, COMPLETION_NORMAL);
  message_send(SIM_COMPLETION_MSG_NO);

  /*
  sim_wait_response([](){
    set_state(sim_measurement_standby, MAIN_STATE_NO);
  });
  */


}

void sim_meas_cover_open() {
  Serial.println("Cover open for measurement in progress...");
  delayed_set_state(sim_meas_cover_open_compl, MAIN_STATE_NO, SIM_COVER_OPEN_DELAY);
}

void sim_meas_cover_close_compl() {
  Serial.println("Cover close for measurement complete");
  message_set_opcode(SIM_COMPLETION_MSG_NO, MESSAGE_OPCODE_COMPL_NTC);
  message_set_ctrl(SIM_COMPLETION_MSG_NO, MESSAGE_ENQ);
  message_clear_data(SIM_COMPLETION_MSG_NO);
  message_put_int(SIM_COMPLETION_MSG_NO, MESSAGE_OPCODE_COVER_OP);
  message_put_int(SIM_COMPLETION_MSG_NO, COMPLETION_NORMAL);
  message_send(SIM_COMPLETION_MSG_NO);

  if (sim_state == STATE_STOPPING){
	  delay(1500);
	  sim_wait_response([]() {
		  sim_change_state(STATE_MEAS_STOPPED, MESSAGE_MEASUREFINISH, []() {
		  delayed_set_state(sim_standby, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY);
	  });
		//set_state(sim_standby, MAIN_STATE_NO);
	});
  }else{
	  sim_wait_response([]() {
	  sim_change_state(STATE_END_PROCESSING, MESSAGE_MEASUREFINISH, []() {
		  delayed_set_state(sim_standby, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY);
	  });
		//set_state(sim_standby, MAIN_STATE_NO);
	});
  }


}

void sim_meas_cover_close() {
  Serial.println("Cover close for measurement in progress...");
  delayed_set_state(sim_meas_cover_close_compl, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY);
}

void sim_measurement_standby_update() {
  if (sim_stop_measurement_call) {
		sim_change_state(STATE_STOPPING, MESSAGE_WAITING, []() {
			delayed_set_state(sim_meas_cover_close_compl, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY );
        });
    return;
  }
  if (sim_start_measurement_call) {
    //set_state(sim_measuring, MAIN_STATE_NO);
    //delayed_set_state(sim_measuring, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY);
      delayed_set_state(sim_send_measinfo, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY);
    return;
  }
  if (sim_end_measurement_call) {
    set_state(sim_standby, MAIN_STATE_NO);
    return;
  }

  if (sim_meas_standby_start == 0) {
    sim_meas_standby_start = millis();
  } else if (millis() - sim_meas_standby_start >= SIM_MEAS_STANDBY_TIMEOUT) {
    set_state(sim_meas_cover_close, MAIN_STATE_NO);
    return;
  }
}

void sim_measurement_standby() {
  sim_start_measurement_call = true;
  if (sim_state == STATE_STANDBY){
	  if (sim_stat_start_measurement_call){
		  sim_change_state(STATE_WAITING_FOR_RACK, MESSAGE_STATRESERVED, []() {
		  });
		  delay(1500);
	  }

	  sim_change_state(STATE_WAITING_FOR_RACK, MESSAGE_WAITING, []() {
	    //set_state(sim_measurement_standby_update, MAIN_STATE_NO);
		 //delayed_set_state(sim_waitingForRack, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY);
		 delayed_set_state(sim_waitingForRack_cont, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY);
	  });
	}
}

void sim_measuring() {
  sim_single_remain = SIM_SINGLE_DEFAULT_TIME;
  sim_multi_remain = SIM_MULTI_DEFAULT_TIME;
  sim_el_remain = SIM_EL_DEFAULT_TIME;
  sim_change_state(STATE_MEASURING, MESSAGE_WAITING, []() {
    //set_state(sim_send_barcode, MAIN_STATE_NO);
    delayed_set_state(sim_send_meas_time, MAIN_STATE_NO,SIM_COVER_CLOSE_DELAY);
  });
}

void sim_send_measinfo() {

	dummy_measinfo(SIM_MEASINFO_MSG_NO, statuscnt, priority_stat );
	message_send(SIM_MEASINFO_MSG_NO);
    //dummy_systemlog(SIM_SYSTEMLOG_MSG_NO);
    //message_send(SIM_MEASINFO_MSG_NO);

    if (sim_meas_errorpopUp_call) {
            sim_meas_errorpopUp_call = false;
            sim_wait_response([]() {
                Serial.println("Error Notice Prepare");
                //set_state(sim_send_meas_time, MAIN_STATE_NO);
                set_state(sim_send_errorCode, MAIN_STATE_NO);
                });
    }else if(sim_start_measlong_call){
            statuscnt++;
			if (priority_stat == 0){
				measNUmber_Normal++;
			}else if(priority_stat == 1){
				// reset priority
				measNUmber_PortCup++;
				priority_stat = 0;
				sim_stat_start_measurement_call = false;
			}else if(priority_stat == 2){		
				measNUmber_RackStat++;
			}

            sim_wait_response([]() {
                delayed_set_state(sim_send_measinfo, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY);
            });

            if (statuscnt >= 8){
				if (sim_stat_start_measurement_call){
					sim_stat_start_measurement_call = false;
					sim_start_measlong_call = false;
					priority_stat = 0;
				}else{
					sim_start_measlong_call = false;
					priority_stat = 0;
				}
			}
    }else{
			statuscnt = 0;
			if (priority_stat == 0){
				measNUmber_Normal += 8;
			}else if(priority_stat == 1){
				// reset priority
				measNUmber_PortCup++;
				priority_stat = 0;
				sim_stat_start_measurement_call = false;
			}else if(priority_stat == 2){		
				measNUmber_RackStat += 8;
			}
            sim_wait_response([]() {
                //set_state(sim_send_meas_time, MAIN_STATE_NO);
                set_state(sim_measuring, MAIN_STATE_NO);
                });
    }
}

void sim_send_errorCode() {
	int randomo;
    Serial.println("Error Notice Prepare02");
    message_set_opcode(SIM_ERRORCODE_MSG_NO, MESSAGE_OPCODE_ERROR_NTC);
    message_set_ctrl(0, MESSAGE_ENQ);
    message_clear_data(SIM_ERRORCODE_MSG_NO);
    message_put_string(SIM_ERRORCODE_MSG_NO, wc_error_code.error_PopUp_number); //Reference
    for (int idx = 1; idx <= 4; idx++) {
        randomo = (rand() % 801);
		message_put_int(SIM_ERRORCODE_MSG_NO, randomo);                  //status
    }
    message_send(SIM_ERRORCODE_MSG_NO);

    sim_wait_response([]() {
        //set_state(sim_send_meas_time, MAIN_STATE_NO);
        set_state(sim_measuring, MAIN_STATE_NO);
        });
}
void sim_send_errorCode_forced() {
	int randomo;
    Serial.println("Error Notice Prepared");
    message_set_opcode(1, MESSAGE_OPCODE_ERROR_NTC);
    message_set_ctrl(1, MESSAGE_ENQ);
    message_clear_data(1);
    message_put_string(1, wc_error_code.error_PopUp_number); //Reference
    for (int idx = 1; idx <= 4; idx++) {
        randomo = (rand() % 801);
		message_put_int(1, randomo);                  //status
    }
    message_send(1);
	set_state(sim_error_popUp_forced, MAIN_STATE_NO);

}

void sim_send_meas_time() {
//  message_set_opcode(SIM_MEAS_TIME_MSG_NO, MESSAGE_OPCODE_MEAS_TIME_NTC);
//  message_set_ctrl(SIM_MEAS_TIME_MSG_NO, MESSAGE_ENQ);
//  message_clear_data(SIM_MEAS_TIME_MSG_NO);
//  message_put_int(SIM_MEAS_TIME_MSG_NO, sim_single_remain);
//  message_put_int(SIM_MEAS_TIME_MSG_NO, sim_multi_remain);
//  message_put_int(SIM_MEAS_TIME_MSG_NO, sim_el_remain);
//  message_send(SIM_MEAS_TIME_MSG_NO);
//  sim_wait_response([]() {
    set_state(sim_send_tip_case, MAIN_STATE_NO);
//  });
}

void sim_send_tip_case() {
  dummy_tip_case(SIM_TIP_CASE_MSG_NO);
  message_send(SIM_TIP_CASE_MSG_NO);
  sim_wait_response([]() {
    set_state(sim_measuring_pre_update, MAIN_STATE_NO);
  });
}

void sim_measuring_pre_update() {
  sim_meas_time_snap = millis();
  sim_meas_start = millis();
  sim_meas_time_drift = 0;
  sim_meas_cur_channel = 1;
  //sim_stop_measurement_call = false;
  set_state(sim_update_meas_time, TICK_STATE_NO);
  set_state(sim_measuring_update, MAIN_STATE_NO);
}

void sim_measuring_update() {
  if (sim_stop_measurement_call) {
    //set_state(EMPTY_STATE_FUNC, TICK_STATE_NO);
    //set_state(sim_meas_cover_open, MAIN_STATE_NO);
	sim_change_state(STATE_STOPPING, MESSAGE_WAITING, []() {
		message_send(SIM_MEAS_RESULT_MSG_NO);
        //delayed_set_state(sim_meas_cover_open, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY);
        delayed_set_state(sim_meas_cover_close_compl, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY );
        });
    return;
  }
  if (millis() - sim_meas_start >= SIM_MEAS_RESULT_INTERVAL) { 
        sim_result(SIM_MEAS_RESULT_MSG_NO, sim_meas_cur_channel);
        message_send(SIM_MEAS_RESULT_MSG_NO);
        
        if (sim_start_measimage_call) {
            set_state(sim_image_mode, MAIN_STATE_NO);
        }else{
            sim_wait_response(
                []() {
					sim_image(SIM_MEAS_IMAGE_MSG_NO,meas_id, 1, 1);
                    message_send(SIM_MEAS_IMAGE_MSG_NO);
                    sim_wait_response(
                        []() {
                            delayed_set_state(sim_meas_cover_close_compl, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY);
                            sim_meas_start = millis();
                            //sim_meas_cur_channel++;
                            //if (sim_meas_cur_channel > 15) {
                            //  set_state(EMPTY_STATE_FUNC, TICK_STATE_NO);
                            //  set_state(sim_meas_cover_open, MAIN_STATE_NO);
                            //} else {
                            //  set_state(sim_measuring_update, MAIN_STATE_NO);
                            //}
                        }
                    );
                }
            );
        }
  }
}

void _sim_decrement_time_counter() {
  if (sim_single_remain > 0) {
    sim_single_remain--;
  } else if (sim_multi_remain > 0) {
    sim_multi_remain--;
  } else if (sim_el_remain > 0) {
    sim_el_remain--;
  } else {
    set_state(EMPTY_STATE_FUNC, TICK_STATE_NO);
    return;
  }
}

void sim_update_meas_time() {
  if (millis() - sim_meas_time_snap >= 1000) {
    _sim_decrement_time_counter();
    sim_meas_time_drift += ((millis() - sim_meas_time_snap) - 1000);
    if (sim_meas_time_drift >= 1000) {
      sim_meas_time_drift -= 1000;
      if (sim_single_remain > 0) {
        sim_single_remain--;
      } else if (sim_multi_remain > 0) {
        sim_multi_remain--;
      } else if (sim_el_remain > 0) {
        sim_el_remain--;
      } else {
        set_state(EMPTY_STATE_FUNC, TICK_STATE_NO);
        return;
      }
    }
    sim_meas_time_snap = millis();
  }
}

void sim_image_mode() {
    if (sim_start_measimage_call) {
		sim_image(SIM_MEAS_IMAGE_MSG_NO, meas_id, imagecounter, imagenumber);
		message_send(SIM_MEAS_IMAGE_MSG_NO);
		imagecounter++;
         sim_wait_response([]() {
             delayed_set_state(sim_image_mode, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY);
             });

         if (imagecounter >= 12) {
			 imagenumber++;
			 imagecounter = 0;
			if (imagenumber >= 10)sim_start_measimage_call = false;
         }
    }
     else {
		sim_image(SIM_MEAS_IMAGE_MSG_NO, meas_id, imagecounter, imagenumber);
		message_send(SIM_MEAS_IMAGE_MSG_NO);
        imagecounter = 0;
		imagenumber = 0;
         sim_wait_response([]() {
             //set_state(sim_send_meas_time, MAIN_STATE_NO);
             delayed_set_state(sim_meas_cover_close_compl, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY);
         });
     }
}

void sim_on_system_version() {
	 //Serial.println("started vers");
	 vercounter++;
     dummy_system_version(1, vercounter);
     if (vercounter <= 8) {
         sim_wait_response([]() {
             delayed_set_state(sim_on_system_version, MAIN_STATE_NO, 500);
             });
     }else{
		 if (sim_error_popUp_call)
			 set_state(sim_error_popUp_forced, MAIN_STATE_NO);
		 else
			 set_state(EMPTY_STATE_FUNC, MAIN_STATE_NO);
		  //set_state(sim_ext_request_proc, BG_PROC_STATE_NO);
	 }
}

void sim_put_time_course(int msg_no,int idx) {

    message_put_string(msg_no, "1$2");                       //measId
    message_put_string(msg_no, "1");                  // analyzerSerialNum,
    message_put_string(msg_no, "1");                  // analyzerSystem,
    message_put_string(msg_no, "1");                  // analyzerVersion,
    message_put_string(msg_no, "7/12/2022 07:00:00"); //measureDate : '7/12/2022 07:00:00',
    message_put_string(msg_no, "1322655845221");      //barcode : '1322655845221',
    message_put_int(msg_no, idx);                       //rackNumber
    message_put_string(msg_no, "1");                  //testTubePosition : 1,
    message_put_int(msg_no, idx);                       //rackId
    message_put_string(msg_no, "1");                  //measurementNum : 1,
    message_put_string(msg_no, "1");                  //measurementItem,
    message_put_string(msg_no, "1");                  //priority,
    message_put_string(msg_no, "02");                 //measurementType : MeasurementType.normal,
    message_put_string(msg_no, "1");                  //qcMaterialLotNum,
    message_put_string(msg_no, "902:28UB");           //testPaperName : '902:28UB',
    message_put_string(msg_no, "02");                 //testPaperLotNum : '02',
    message_put_string(msg_no, "1");                  //measurementTemp,
    message_put_string(msg_no, "1");                  //liquidLevel,
    message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,

	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //dosingInfo,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //feeder,
    message_put_string(msg_no, "1");                  //testpaperJudgeResult,
    message_put_string(msg_no, "1");                  //testpaperMarkerResult,
    message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,

	message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //dosingInfo,
    message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
	message_put_string(msg_no, "1");                  //worklistId : 1,
}



void sim_result(int msg_no, int channel) {
  message_set_opcode(msg_no, MESSAGE_OPCODE_MEAS_RESULT);
  message_set_ctrl(msg_no, MESSAGE_ENQ);
  message_clear_data(msg_no);
  /*
  message_put_string(msg_no, ANALYZER_SERIAL_NO);
  message_put_string(msg_no, "9504170000"); //Date time YYMMDDHHmm
  message_put_int(msg_no, sim_start_cond_meas_no);
  message_put_string(msg_no, sim_start_cond_sample_id);
  message_put_string(msg_no, sim_start_cond_operator_id);
  message_put_int(msg_no, sim_start_cond_sample_type);
  message_put_int(msg_no, sim_start_cond_patient_type);
  message_put_string(msg_no, "0.0"); //Result value
  if (channel >= 1 && channel <= 6) {
    message_put_string(msg_no, DUMMY_BARCODE_SINGLE);
    message_put_int(msg_no, channel);
    message_put_int(msg_no, 0);
    char name[10];
    sprintf(name, "single-%d", channel);
    message_put_string(msg_no, name);
  }
  else if (channel >= 7 && channel <= 12) {
    message_put_string(msg_no, DUMMY_BARCODE_MULTI);
    message_put_int(msg_no, channel);
    message_put_int(msg_no, 0);
    char name[10];
    sprintf(name, "multi-%d", channel - 6);
    message_put_string(msg_no, name);
  } else if (channel >= 13 && channel <= 15) {
    message_put_string(msg_no, DUMMY_BARCODE_EL);
    message_put_int(msg_no, channel);
    message_put_int(msg_no, 0);
    switch (channel) {
      case 13:
      message_put_string(msg_no, "Na");
      break;
      case 14:
      message_put_string(msg_no, "K");
      break;
      case 15:
      message_put_string(msg_no, "Cl");
      break;
    }
  }
  */
  for (int idx = 1; idx <= 9; idx++) {
    sim_put_time_course(msg_no,idx);
  }
  /*
  message_put_string(msg_no, "00000000"); //dK/s
  message_put_string(msg_no, "00000000"); //C0
  message_put_string(msg_no, "000000"); //Temperature
  message_put_string(msg_no, "000000"); //Humidity
  message_put_string(msg_no, "00000000"); //Ke
  message_put_string(msg_no, "00000000"); //C1
  message_put_string(msg_no, "00000000"); //Adev
  message_put_string(msg_no, "00000000"); //Bdev
  message_put_string(msg_no, "00000000"); //C2
  message_put_string(msg_no, "00000000"); //Adegr
  message_put_string(msg_no, "00000000"); //Bdegr
  message_put_string(msg_no, "00000000"); //C3
  message_put_string(msg_no, "00000000"); //Lot ch
  message_put_string(msg_no, "00000000"); //C4
  message_put_string(msg_no, "00000000"); //Acal
  message_put_string(msg_no, "00000000"); //Bcal
  message_put_string(msg_no, "00000000"); //C5
  message_put_string(msg_no, "00000000"); //Ktemp
  message_put_string(msg_no, "00000000"); //C6
  message_put_string(msg_no, "00000000"); //Kunit
  message_put_string(msg_no, "00000000"); //C7
  message_put_string(msg_no, "00000000"); //Acorr
  message_put_string(msg_no, "00000000"); //Bcorr
  message_put_string(msg_no, "00000000"); //C8
  message_put_string(msg_no, "000000"); //Unit
  message_put_string(msg_no, "0.0"); //Ref lower limit
  message_put_string(msg_no, "0.0"); //Ref upper limit
  message_put_string(msg_no, "0.0"); //Meas lower limit
  message_put_string(msg_no, "0.0"); //Meas upper limit
  message_put_string(msg_no, ABNORMAL_STATUS_NORMAL); //Abnormal status
  */
}

void sim_image(int msg_no, int measid, int sequence, int itemnumber) {
    message_set_opcode(msg_no, MESSAGE_OPCODE_MEAS_IMAGE);
    message_set_ctrl(msg_no, MESSAGE_ENQ);
    message_clear_data(msg_no);

    switch(sequence){
    case 0:
        message_put_string(msg_no, "1"); // fieldLabel
        message_put_int(msg_no, measid); // sequenceNumber
        message_put_int(msg_no, itemnumber); // imageNumber
        message_put_string(msg_no,"9" ); // imageTotal
        message_put_string(msg_no, "1"); // itemNumber
        message_put_string(msg_no, "1"); // itemName
        message_put_string(msg_no, "1"); // pageNumber
        message_put_string(msg_no, "12"); // pageTotal
        message_put_string(msg_no, "data:image / jpeg;base64, / 9j / 4AAQSkZJRgABAQAAAQABAAD / 4gIoSUNDX1BST0ZJTEUAAQEAAAIYAAAAAAQwAABtbnRyUkdCIFhZWiAAAAAAAAAAAAAAAABhY3NwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQAA9tYAAQAAAADTLQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAlkZXNjAAAA8AAAAHRyWFlaAAABZAAAABRnWFlaAAABeAAAABRiWFlaAAABjAAAABRyVFJDAAABoAAAAChnVFJDAAABoAAAAChiVFJDAAABoAAAACh3dHB0AAAByAAAABRjcHJ0AAAB3AAAADxtbHVjAAAAAAAAAAEAAAAMZW5VUwAAAFgAAAAcAHMAUgBHAEIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFhZWiAAAAAAAABvogAAOPUAAAOQWFlaIAAAAAAAAGKZAAC3hQAAGNpYWVogAAAAAAAAJKAAAA + EAAC2z3BhcmEAAAAAAAQAAAACZmYAAPKnAAANWQAAE9AAAApbAAAAAAAAAABYWVogAAAAAAAA9tYAAQAAAADTLW1sdWMAAAAAAAAAAQAAAAxlblVTAAAAIAAAABwARwBvAG8AZwBsAGUAIABJAG4AYwAuACAAMgAwADEANv / bAEMAAwICAgICAwICAgMDAwMEBgQEBAQECAYGBQYJCAoKCQgJCQoMDwwKCw4LCQkNEQ0ODxAQERAKDBITEhATDxAQEP / bAEMBAwMDBAMECAQECBALCQsQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEP / AABEIABIA7wMBIgACEQEDEQH / xAAcAAACAwEAAwAAAAAAAAAAAAAAAwECBAUGBwn / xAAtEAACAQQBAgMHBQEAAAAAAAAAAQIDESExEjJBQlGRBAUiYXGh8BOBgrHBwv / EABkBAAMBAQEAAAAAAAAAAAAAAAABAgMFBP / EAB8RAQEAAQQCAwAAAAAAAAAAAAABAiEyQWExUREzQv / aAAwDAQACEQMRAD8A + gFLis99D1OKV / QRHwobFJ7O64jTGpyw8IvK / mKjZWXYmcrrQHPRVR / PRnlLN46GVH6XsZ1dvCFq1xX5csW1odR931a9n2Ley0eU05PB2aPCEOMVkXabfTmS9zpRTlIRU938el3O3OXJZFSjfsHZS149W9lcW / hEypS8SO5WpwbxExVqKV + K9RaNPlzv03cNfmjTUjx / MCZq0Xb6gZfa1yrb88ku / crL7i4GqJS462EW9lbX6sdxkF4hFqmMr / 2Wb2TEpOakuKyPgUqd7OxWUrbJk / IVOTUZO + dBqiq1KnFP1MdSos68h1aa6vkYaslfL7CMqvWTvi37GKo5SuOqSw28GaUstNt5 + YK5RdSXn37FvqRaKzIjPG6d2iDEne6Ey + Lpwl22OcY8fxipcu33Au3siOv5WHxAD0Mzlol9IAKgioLj1AAl4t3sejfTbABxlVpaFgA14sc2 + WxVbpACKeWxlqbMllxTt4pf6AEZbavDaXdqE2m1aUyku4AVj9cOeckFo9KADL9FPNMekUmAGsZ8E1RFTQAHIZa//JiqdSABNIzVM3uZqmJysAEAS2g1SVgAAiX59iq6l9f8AAS//9k="); // binaryData
        break;
    case 1:
        message_put_string(msg_no, "1"); // fieldLabel
        message_put_int(msg_no, measid); // sequenceNumber
        message_put_int(msg_no, itemnumber); // imageNumber
        message_put_string(msg_no,"9" ); // imageTotal
        message_put_string(msg_no, "1"); // itemNumber
        message_put_string(msg_no, "1"); // itemName
        message_put_string(msg_no, "2"); // pageNumber
        message_put_string(msg_no, "12"); // pageTotal
        message_put_string(msg_no, "data:image/jpeg;base64,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"); // binaryData
        break;
    case 2:
        message_put_string(msg_no, "1"); // fieldLabel
        message_put_int(msg_no, measid); // sequenceNumber
        message_put_int(msg_no, itemnumber); // imageNumber
        message_put_string(msg_no,"9" ); // imageTotal
        message_put_string(msg_no, "1"); // itemNumber
        message_put_string(msg_no, "1"); // itemName
        message_put_string(msg_no, "3"); // pageNumber
        message_put_string(msg_no, "12"); // pageTotal
        message_put_string(msg_no, "data:image/jpeg;base64,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"); // binaryData
        break;
    case 3:
        message_put_string(msg_no, "1"); // fieldLabel
        message_put_int(msg_no, measid); // sequenceNumber
        message_put_int(msg_no, itemnumber); // imageNumber
        message_put_string(msg_no,"9" ); // imageTotal
        message_put_string(msg_no, "1"); // itemNumber
        message_put_string(msg_no, "1"); // itemName
        message_put_string(msg_no, "4"); // pageNumber
        message_put_string(msg_no, "12"); // pageTotal
        message_put_string(msg_no, "data:image/jpeg;base64,/9j/4AAQSkZJRgABAQAAAQABAAD/4gIoSUNDX1BST0ZJTEUAAQEAAAIYAAAAAAQwAABtbnRyUkdCIFhZWiAAAAAAAAAAAAAAAABhY3NwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQAA9tYAAQAAAADTLQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAlkZXNjAAAA8AAAAHRyWFlaAAABZAAAABRnWFlaAAABeAAAABRiWFlaAAABjAAAABRyVFJDAAABoAAAAChnVFJDAAABoAAAAChiVFJDAAABoAAAACh3dHB0AAAByAAAABRjcHJ0AAAB3AAAADxtbHVjAAAAAAAAAAEAAAAMZW5VUwAAAFgAAAAcAHMAUgBHAEIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFhZWiAAAAAAAABvogAAOPUAAAOQWFlaIAAAAAAAAGKZAAC3hQAAGNpYWVogAAAAAAAAJKAAAA+EAAC2z3BhcmEAAAAAAAQAAAACZmYAAPKnAAANWQAAE9AAAApbAAAAAAAAAABYWVogAAAAAAAA9tYAAQAAAADTLW1sdWMAAAAAAAAAAQAAAAxlblVTAAAAIAAAABwARwBvAG8AZwBsAGUAIABJAG4AYwAuACAAMgAwADEANv/bAEMAAwICAgICAwICAgMDAwMEBgQEBAQECAYGBQYJCAoKCQgJCQoMDwwKCw4LCQkNEQ0ODxAQERAKDBITEhATDxAQEP/bAEMBAwMDBAMECAQECBALCQsQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEP/AABEIABIA7wMBIgACEQEDEQH/xAAdAAABBAMBAQAAAAAAAAAAAAAAAgMEBwEFCAYJ/8QAOBAAAQMCBAMEBwcFAQAAAAAAAQACEQMEBRIhMQZBUQcTItEIMmFxkaHBFCNCUoGx8BYlM2KCkv/EABwBAAEFAQEBAAAAAAAAAAAAAAUAAQIEBgcDCP/EACYRAAIBAwMEAQUAAAAAAAAAAAABAgMEEQUhMQYHMkESIjM0QnH/2gAMAwEAAhEDEQA/AO8mkrPeHokJJdHrI03gF4HQ/ZDXbJjOcv8AAk5+Xmojon0nh27pUprmhuklamnW8W5UynW21SySwSalVlOmaryAGiS46AQNyuJe3LjerxRxDeXPfObQDiyg1xiKbTAG/wDJK6n7WeIXcP8AAuI3bH5Ktwz7NS03L9CP/Gf4Lgfj7FibyqxtQgAR7euvtKB6tcNL4o632u0tVrh3c1xsjz13e96yoHnNmMmHSDG31+JWkq49cAChb1C1h8LRJgEGZHwHxUO9xanTa5+aeR00/fotE3EGhpuGOBGbKBOu0nntqN+qzMqm6Po2DpqPxZZGDcZX+HNbUp16mvr68hy3XqcL7UrzvGNqXz5DvE0kkeEaAieRHVUTVxwhrBT8D+816EREH3FMuxgnUvAcwbzHPy+q96dzKGEihdaZb105TSydL3HbOaoqZ7rJU/CWucDvqCJ3iNgvKXXbLevzOoXtdrGuIYGvLeep369CqGvMbrCk6syu/wABaJ1mTP6bjmmrPG31awdVeSdhmjWRt81OV7NvGQTS0O1WXgt/iXtvxynYmhQNMNqtLQXmTtuB181UWI8RVrppHeOeXH1iIOx8+q1uOYpVq3T2FpZ3fhM76TovP1b5zXQh1xXc3iQWtYW1hDMI4Zs7u7rsqOpVg9rhu12+0j+e1QquKVGB7A4w8Q4E9DMfIKNiF8ytcvqtaxo/1dmGggmfadVqq1y6VVSk2VLjVfp2ZLqXpBIJTHfuqOyNOp6kAfFa6tV1mSmXVZMSrMKRm7jVJvZsl1awG1STppGiTaVIuGweYE7KDm8Sl2rGGtTyGcx1nlqfoPmrtOCWMASrcSqPcuLso4kvcA4hs69rcOp1aL2VKLmaEPBmffMfBfUXhrGqHEuA4fj1q4Cne0GVQ1pnKSBLZjcGRtyK+TvB1Ko28s67hGV5Bj2SV9I/RmxO4xTsvt6FxH9vuatqyPygNfqfe8/JaDTZb4OYdZ20XisuUWu1saDVZLYByjQ805kOXp1WS0bI0c+GGgztzS4iQncv5VnKYMpxveSM5rfjum3Mzbj6KSafkVkU4dz2TCPVu3SevuQhejEJd6qQ4nKhCYQlilUiY3QhQJorD0iXO/omk3MY+2UzE6T3blwtxkTnrGTMkfMoQs1q3md87X/gr+lc4iSaGpJ+7n9ci0tUkWlMAkDuXmP+z5lCEAn6Ovfsa57nGsGlxjLtKVdk5Rr+b9whCnHgtT8SFUJ7t7Z07xojloDCjvc5tUlpI8XL3oQoPkqw4ZEuHOdBcSSdyea11YnLM6oQvGtyUrnxItTb9VDqExud0ITw4M3c8EZ5Pi15JlCFagAK3LMtU2z/AMtNCFap+jyRaHC4H2q0EficfkvoD6JbnHgbEGlxgXbCBOg+7HkEIRiw8zC9X/YL0OgELPkhCOo5kzNTdODWnr0QhIYR5oqgIQkI/9k="); // binaryData
        break;
    case 4:
        message_put_string(msg_no, "1"); // fieldLabel
        message_put_int(msg_no, measid); // sequenceNumber
        message_put_int(msg_no, itemnumber); // imageNumber
        message_put_string(msg_no,"9" ); // imageTotal
        message_put_string(msg_no, "1"); // itemNumber
        message_put_string(msg_no, "1"); // itemName
        message_put_string(msg_no, "5"); // pageNumber
        message_put_string(msg_no, "12"); // pageTotal
        message_put_string(msg_no, "data:image/jpeg;base64,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"); // binaryData
        break;
    case 5:
        message_put_string(msg_no, "1"); // fieldLabel
        message_put_int(msg_no, measid); // sequenceNumber
        message_put_int(msg_no, itemnumber); // imageNumber
        message_put_string(msg_no,"9" ); // imageTotal
        message_put_string(msg_no, "1"); // itemNumber
        message_put_string(msg_no, "1"); // itemName
        message_put_string(msg_no, "6"); // pageNumber
        message_put_string(msg_no, "12"); // pageTotal
        message_put_string(msg_no, "data:image/jpeg;base64,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"); // binaryData
        break;
    case 6:
        message_put_string(msg_no, "1"); // fieldLabel
        message_put_int(msg_no, measid); // sequenceNumber
        message_put_int(msg_no, itemnumber); // imageNumber
        message_put_string(msg_no, "9"); // imageTotal
        message_put_string(msg_no, "1"); // itemNumber
        message_put_string(msg_no, "1"); // itemName
        message_put_string(msg_no, "7"); // pageNumber
        message_put_string(msg_no, "12"); // pageTotal
        message_put_string(msg_no, "data:image/jpeg;base64,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"); // binaryData
        break;
    case 7:
        message_put_string(msg_no, "1"); // fieldLabel
        message_put_int(msg_no, measid); // sequenceNumber
        message_put_int(msg_no, itemnumber); // imageNumber
        message_put_string(msg_no,"9" ); // imageTotal
        message_put_string(msg_no, "1"); // itemNumber
        message_put_string(msg_no, "1"); // itemName
        message_put_string(msg_no, "8"); // pageNumber
        message_put_string(msg_no, "12"); // pageTotal
        message_put_string(msg_no, "data:image/jpeg;base64,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"); // binaryData
        break;
    case 8:
        message_put_string(msg_no, "1"); // fieldLabel
        message_put_int(msg_no, measid); // sequenceNumber
        message_put_int(msg_no, itemnumber); // imageNumber
        message_put_string(msg_no,"9" ); // imageTotal
        message_put_string(msg_no, "1"); // itemNumber
        message_put_string(msg_no, "1"); // itemName
        message_put_string(msg_no, "9"); // pageNumber
        message_put_string(msg_no, "12"); // pageTotal
        message_put_string(msg_no, "data:image/jpeg;base64,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"); // binaryData
        break;
    case 9:
        message_put_string(msg_no, "1"); // fieldLabel
        message_put_int(msg_no, measid); // sequenceNumber
        message_put_int(msg_no, itemnumber); // imageNumber
        message_put_string(msg_no,"9" ); // imageTotal
        message_put_string(msg_no, "1"); // itemNumber
        message_put_string(msg_no, "1"); // itemName
        message_put_string(msg_no, "10"); // pageNumber
        message_put_string(msg_no, "12"); // pageTotal
        message_put_string(msg_no, "data:image/jpeg;base64,/9j/4AAQSkZJRgABAQAAAQABAAD/4gIoSUNDX1BST0ZJTEUAAQEAAAIYAAAAAAQwAABtbnRyUkdCIFhZWiAAAAAAAAAAAAAAAABhY3NwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQAA9tYAAQAAAADTLQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAlkZXNjAAAA8AAAAHRyWFlaAAABZAAAABRnWFlaAAABeAAAABRiWFlaAAABjAAAABRyVFJDAAABoAAAAChnVFJDAAABoAAAAChiVFJDAAABoAAAACh3dHB0AAAByAAAABRjcHJ0AAAB3AAAADxtbHVjAAAAAAAAAAEAAAAMZW5VUwAAAFgAAAAcAHMAUgBHAEIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFhZWiAAAAAAAABvogAAOPUAAAOQWFlaIAAAAAAAAGKZAAC3hQAAGNpYWVogAAAAAAAAJKAAAA+EAAC2z3BhcmEAAAAAAAQAAAACZmYAAPKnAAANWQAAE9AAAApbAAAAAAAAAABYWVogAAAAAAAA9tYAAQAAAADTLW1sdWMAAAAAAAAAAQAAAAxlblVTAAAAIAAAABwARwBvAG8AZwBsAGUAIABJAG4AYwAuACAAMgAwADEANv/bAEMAAwICAgICAwICAgMDAwMEBgQEBAQECAYGBQYJCAoKCQgJCQoMDwwKCw4LCQkNEQ0ODxAQERAKDBITEhATDxAQEP/bAEMBAwMDBAMECAQECBALCQsQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEP/AABEIABIA7wMBIgACEQEDEQH/xAAdAAACAQUBAQAAAAAAAAAAAAAABQYBAgMEBwgJ/8QAMhAAAQIFAwIDBwMFAAAAAAAAAQACAwQFESESMUEGUSIyoQcTFGFxgZEII0JSscHR8P/EABoBAAIDAQEAAAAAAAAAAAAAAAIFAQMEBgD/xAAkEQACAgICAQQDAQAAAAAAAAAAAQIDETEEEgUhMjNBBhMUcf/aAAwDAQACEQMRAD8A+k4PCqqY3Rqx2TgTlXcrHEcOf+wqucsTnXv22U4CSKF3Nsq1ztwVaTY+FWOcpCQOdssER/hOfurnOLvyteI7ufoEISI91kx0alxNzheA/wBQ1BiQOoWz2g2jN0k8XBuP7lfQury/xEm9triy8v8Atx6CNapsfRD/AHoLtbDbkJR5ah3UsbeI5X6Lsnhqp0kxDltlH5rp1r9V2ei6tOUd7Ir4UWHaI0kEW7JdGorc+FcdCt/Z239KkspnKHSFUph1SM3GhAcB9x+Fng9W1uVHu56A2YZuSMOtbb0U7naLdp1M9FHqhRmOe7wfPCicIvaNPH5llTXViOb6olZgEgOY84IeNuwH0SCfqMMXIii1u6ZVCkbt0gpNHozS6+n57L1dcVpjyv8AIb6YYxkVxp9jnFrQTfgKwGaj2DG6RvZNGUoM2btuP8Lel6ZtcY9FqXVLAv5Xm+VyXlywKpGQdqHvD88lS6lQ2QwLD8rWgSOk+XhM5WWezOVHdLQrnY7PWTySykxGNAv6KYU9zXgGwsoLTg9tsfJSylxCLNV9d5huhl5RK5aVabWF0wgybXAXFkvkI12jcj6p/Kua62Fock9i6TcWWQpDY2F900pMm4T8EgbPHKugMZbUApX0nQos9Ow4ugkcYv8AdTCClNYKbLOsW5HbvZy94k4Gr+ldkornYyFzbo2k/CwmN0eULpdKhOba66jjx6xSObtabY6uVRysMRlw2/ite3P1sqnb/S1f4Z36DVUduhCgEsirGdkIRBxMY/krd3ZQheJRgdssT/IhCBBIxRQPcuwuWddQ4ZEa7GnD+EIVN/xssp9yPGnXcKEzqWZDIbWjVwAOVEYgGrYIQuKs+Rna0+xCqeAsccKN1EDQcIQskjbWRyfa258I54Sp7GndoP2QhVRNEtGqGt1eUfhZ2AadghCsKJG9AAuMBMIAFxgIQiAiOJQAPFgnkh/FCFMfoCRIpBzsZKk0iTYIQtcdC+7Y8p+XsBzldr9njGeE6G7dkITDh7Qs5mjtVCa0QWWaNuymkihC6WrQhlpmywDe2dSq5CFcitn/2Q=="); // binaryData
        break;
    case 10:
        message_put_string(msg_no, "1"); // fieldLabel
        message_put_int(msg_no, measid); // sequenceNumber
        message_put_int(msg_no, itemnumber); // imageNumber
        message_put_string(msg_no,"9" ); // imageTotal
        message_put_string(msg_no, "1"); // itemNumber
        message_put_string(msg_no, "1"); // itemName
        message_put_string(msg_no, "11"); // pageNumber
        message_put_string(msg_no, "12"); // pageTotal
        message_put_string(msg_no, "data:image/jpeg;base64,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"); // binaryData
        break;
    case 11:
        message_put_string(msg_no, "1"); // fieldLabel
        message_put_int(msg_no, measid); // sequenceNumber
        message_put_int(msg_no, itemnumber); // imageNumber
        message_put_string(msg_no,"9" ); // imageTotal
        message_put_string(msg_no, "1"); // itemNumber
        message_put_string(msg_no, "1"); // itemName
        message_put_string(msg_no, "12"); // pageNumber
        message_put_string(msg_no, "12"); // pageTotal
        message_put_string(msg_no, "data:image/jpeg;base64,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"); // binaryData
        break;
    case 12:
        break;
    case 13:
        break;
    case 14:
        break;
    case 15:
        break;
    default:
        message_put_string(msg_no, "0"); // sequenceNumber
        message_put_string(msg_no, "0"); // fieldLabel
        message_put_string(msg_no, "0"); // imageNumber
        message_put_string(msg_no, "0"); // imageTotal
        message_put_string(msg_no, "0"); // itemNumber
        message_put_string(msg_no, "0"); // itemName
        message_put_string(msg_no, "0"); // pageNumber
        message_put_string(msg_no, "0"); // pageTotal
        message_put_string(msg_no, "0"); // binarydata
        break;
    }
}

void sim_wait_response(cb_func_t on_ack, cb_func_t on_nak) {
//  sim_start_wait_response = millis();
  set_state([on_ack, on_nak] () {
    if (server_get_client() == 0) { //Skip if no client are connected
      on_ack();
      return;
    }
    if (sim_has_response) {
      sim_has_response = false;
      switch (message_get_ctrl(SIM_EXT_REQUEST_MSG_NO)) {
        case MESSAGE_ACK:
        on_ack();
        break;
        case MESSAGE_NAK:
        if (on_nak) {
          on_nak();
        } else {
          on_ack();
        }
        break;
      }
    }
//    } else if (millis() - sim_start_wait_response >= 5000) {
//      sim_start_wait_response = millis();
//      server_client_disconnect();
//      on_ack();
//    }
  }, MAIN_STATE_NO);
}

void sim_change_state(int state, int message, cb_func_t then_func) {
  Serial.print("Change state: ");
  Serial.println(state);
  int randomo;

  sim_state = state;
  message_state = message;

  if (server_get_client()) {
    message_set_opcode(SIM_STATE_CHANGE_MSG_NO, MESSAGE_OPCODE_STATUS_CHG_NTC);
    message_set_ctrl(SIM_STATE_CHANGE_MSG_NO, MESSAGE_ENQ);
    message_clear_data(SIM_STATE_CHANGE_MSG_NO);
    message_put_string(SIM_STATE_CHANGE_MSG_NO, param_get_serial_no());
	randomo = (rand() % 801);
	message_put_int(SIM_ERRORCODE_MSG_NO, randomo);
    message_put_int(SIM_STATE_CHANGE_MSG_NO, state);
    message_put_int(SIM_STATE_CHANGE_MSG_NO, message_state);

    //ICONS
    message_put_int(SIM_STATE_CHANGE_MSG_NO, icon_remaining_test_strip);    // Remote Maintenance
    message_put_int(SIM_STATE_CHANGE_MSG_NO, icon_waste_tray);              // Test Strip waste tray not set
    message_put_int(SIM_STATE_CHANGE_MSG_NO, icon_disposal);                // Test Strip disposal full
    message_put_int(SIM_STATE_CHANGE_MSG_NO, icon_washing_liquid);          // Washing Liquid
    message_put_int(SIM_STATE_CHANGE_MSG_NO, icon_host_connection);         // Host Connection
    message_put_int(SIM_STATE_CHANGE_MSG_NO, icon_printer_connection);      // Printer Connection
    message_put_int(SIM_STATE_CHANGE_MSG_NO, icon_printer_paper);           // Out of Printer Paper
    message_put_int(SIM_STATE_CHANGE_MSG_NO, icon_feeder_paper);            // Feeder test Paper
    message_put_int(SIM_STATE_CHANGE_MSG_NO, icon_remaining_test_strip);    // Remaining Number of test strip measurements
    message_put_int(SIM_STATE_CHANGE_MSG_NO, icon_stat_reservation);        // Stat reservation

    // Measurement Number
    message_put_int(SIM_STATE_CHANGE_MSG_NO, measNUmber_Normal);
    message_put_int(SIM_STATE_CHANGE_MSG_NO, measNUmber_PortCup);
    message_put_int(SIM_STATE_CHANGE_MSG_NO, measNUmber_RackStat);
    message_put_int(SIM_STATE_CHANGE_MSG_NO, measNUmber_Control);
    message_send(SIM_STATE_CHANGE_MSG_NO); //TODO: check: fails even server_get_client()
    sim_wait_response(then_func);
  } else {
    then_func();
  }
}

void sim_on_get_status(int msg_no) {
 int randomo;
  message_set_ctrl(msg_no, MESSAGE_ACK);
  message_clear_data(msg_no);
  message_put_string(SIM_STATE_CHANGE_MSG_NO, param_get_serial_no());
  randomo = (rand() % 801);
  message_put_int(msg_no, randomo);
  message_put_int(msg_no, sim_state);
  message_put_int(msg_no, message_state);

  //ICONS
  message_put_int(msg_no, icon_remaining_test_strip);    // Remote Maintenance
  message_put_int(msg_no, icon_waste_tray);              // Test Strip waste tray not set
  message_put_int(msg_no, icon_disposal);                // Test Strip disposal full
  message_put_int(msg_no, icon_washing_liquid);          // Washing Liquid
  message_put_int(msg_no, icon_host_connection);         // Host Connection
  message_put_int(msg_no, icon_printer_connection);      // Printer Connection
  message_put_int(msg_no, icon_printer_paper);           // Out of Printer Paper
  message_put_int(msg_no, icon_feeder_paper);            // Feeder test Paper
  message_put_int(msg_no, icon_remaining_test_strip);    // Remaining Number of test strip measurements
  message_put_int(msg_no, icon_stat_reservation);        // Stat reservation

      // Measurement Number
    message_put_int(SIM_STATE_CHANGE_MSG_NO, measNUmber_Normal);
    message_put_int(SIM_STATE_CHANGE_MSG_NO, measNUmber_PortCup);
    message_put_int(SIM_STATE_CHANGE_MSG_NO, measNUmber_RackStat);
    message_put_int(SIM_STATE_CHANGE_MSG_NO, measNUmber_Control);

  message_put_string(msg_no, "message_status_ack");      //Boot program name

}

void sim_on_cover_operation(int msg_no) {
  if (sim_state == STATE_STANDBY && sim_setup_measurement_call) {
    int cover_status;
    if (MESSAGE_READ_SUCCESS(message_read_int(msg_no, &cover_status)) && cover_status == COVER_STATE_OPEN) {
      message_set_ctrl(msg_no, MESSAGE_ACK);
      message_clear_data(msg_no);
      sim_meas_cover_open_call = true;
      return;
    }
  }
  message_set_ctrl(msg_no, MESSAGE_NAK);
  message_clear_data(msg_no);
}

void sim_on_get_meas_time(int msg_no) {
  if (sim_state == STATE_MEASURING) {
    message_set_ctrl(msg_no, MESSAGE_ACK);
    message_clear_data(msg_no);
    message_put_int(msg_no, sim_single_remain);
    message_put_int(msg_no, sim_multi_remain);
    message_put_int(msg_no, sim_el_remain);
  } else {
    message_set_ctrl(msg_no, MESSAGE_NAK);
    message_clear_data(msg_no);
  }
}

void sim_on_reagent_info(int msg_no) {
  int request_item;
  char item_no[2];
  char lot_no[2];
  message_read_status_t read_stat;
  read_stat = message_read_int(msg_no, &request_item);
  if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
  read_stat = message_read_string(msg_no, item_no);
  if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
  read_stat = message_read_string(msg_no, lot_no);
  if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
  dummy_reagent_info(msg_no, request_item, item_no, lot_no);
  return;
  nak:
  message_set_ctrl(msg_no, MESSAGE_NAK);
  message_clear_data(msg_no);
}

void sim_on_setup_meas(int msg_no) {
  if (sim_state == STATE_STANDBY) {
    message_set_ctrl(msg_no, MESSAGE_ACK);
    sim_setup_measurement_call = true;
  } else {
    message_set_ctrl(msg_no, MESSAGE_NAK);
  }
  message_clear_data(msg_no);
}

void sim_on_start_meas(int msg_no, bool isStat) {
  Serial.println((int)sim_state);
  if (sim_state == STATE_STANDBY) {
    message_read_status_t read_stat;
	message_reset_data(msg_no);

	if(!isStat){
		//read_stat = message_read_int(msg_no, &sim_start_cond_meas_no);
		//if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
		//read_stat = message_read_string(msg_no, sim_start_cond_sample_id);
		//if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
		//read_stat = message_read_string(msg_no, sim_start_cond_operator_id);
		//if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
		//read_stat = message_read_int(msg_no, &sim_start_cond_sample_type);
		//if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
		//read_stat = message_read_int(msg_no, &sim_start_cond_patient_type);
		//if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
		 sim_start_measurement_call = true;
		 priority_stat = 0;
	}else{
		delay(2000);
		read_stat = message_read_int(msg_no, &sim_stat_cond_mode);
		if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
		read_stat = message_read_int(msg_no, &sim_stat_cond_meas_no);
		if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
		read_stat = message_read_string(msg_no, sim_stat_cond_meas_id);
		if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
		read_stat = message_read_int(msg_no, &sim_stat_cond_meas_feeder);
		if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
		sim_stat_start_measurement_call = true;
		sim_start_measurement_call = false;

		if(sim_stat_cond_mode == 0){
			priority_stat = 1;
		}else if( sim_stat_cond_mode == 1){
			priority_stat = 2;
		}else{
			// Do nothing
		}


	}

    message_set_ctrl(msg_no, MESSAGE_ACK);
    message_clear_data(msg_no);
    message_put_string(msg_no, "message_read_Success"); //Boot program name
	set_state(sim_measurement_standby, MAIN_STATE_NO);
    return;
  nak:
	message_set_ctrl(msg_no, MESSAGE_NAK);
	message_clear_data(msg_no);
	message_put_string(msg_no, "message_read_fail"); //Boot program name
	//set_state(sim_measurement_standby, MAIN_STATE_NO);

  }else if(sim_state == STATE_WAITING_FOR_RACK){
	if(!isStat){
		// Do nothing
	}else{
		delay(2000);
		sim_change_state(STATE_WAITING_FOR_RACK, MESSAGE_STATRESERVED, []() {
	    });
	}
  }else if(sim_state == STATE_MEASURING){
	if(!isStat){
		// Do nothing
	   sim_change_state(STATE_STANDBY, MESSAGE_WAITING, []() {
			set_state(sim_measurement_standby, MAIN_STATE_NO);
		});
	}else{
		delay(2000);
		sim_change_state(STATE_MEASURING, MESSAGE_STATRESERVED, []() {
	    });
	}
  }
}

void sim_on_stop_meas(int msg_no) {

  if((sim_state == STATE_MEASURING)||(sim_state == STATE_WAITING_FOR_RACK)) {
		message_set_ctrl(msg_no, MESSAGE_ACK);
		sim_stop_measurement_call = true;
		message_put_string(msg_no, "nag stop");
  } else if(wc_menu_mode.onProcess == MENU_PROCESS){
		//message_set_ctrl(msg_no, MESSAGE_ACK);
		//message_send(SIM_EXT_REQUEST_MSG_NO);
		sim_stop_measurement_menu_call = true;
		dummy_menumode_cont(msg_no, wc_menu_mode.menumode, wc_menu_mode.parameters, RESULT_FAIL);
		message_send(SIM_EXT_REQUEST_MSG_NO);
		menu_resume_timer = 5000;
		menu_stop_standby_start = 0;
		sim_stop_measurement_menu_call = false;
		wc_menu_mode.onProcess  = 0;
		set_menu_mode(wc_menu_mode);
  } else if(wc_menu_mode.onProcess == SHUTDOWN_PROCESS){
	  	//message_set_ctrl(msg_no, MESSAGE_ACK);
		//message_send(SIM_EXT_REQUEST_MSG_NO);
		dummy_shutdown_cont(msg_no, RESULT_FAIL);
		shutdown_standby_start = 0;
		wc_menu_mode.onProcess  = 0;
		set_menu_mode(wc_menu_mode);
  }else{
		message_set_ctrl(msg_no, MESSAGE_NAK);
  }
  message_clear_data(msg_no);
}

void sim_on_get_sysinfo(int msg_no) {
		delay(500);
        dummy_system_info(msg_no);
        delayed_set_state(sim_on_system_version, MAIN_STATE_NO, 1000);
}

void sim_on_shutdown(int msg_no) {
	wc_menu_mode.onProcess  = 2;
	set_menu_mode(wc_menu_mode);

	shutloop:
			if (shutdown_standby_start == 0){
				menu_standby_start = millis();
				Serial.println("ON STANDBY_1");
			}
			if (millis() - shutdown_standby_start >= 5000) {
					dummy_shutdown_cont(msg_no, RESULT_OK);
					shutdown_standby_start = 0;
					Serial.println("ON STANDBY_2");
					sim_shutdown_menu_call = false;
					return;
			}else{
				Serial.println("ON STANDBY_3");
				delay(500);
				goto shutloop;
			}
}

void sim_on_end_meas(int msg_no) {
  if (sim_state == STATE_WAITING_FOR_RACK) {
    message_set_ctrl(msg_no, MESSAGE_ACK);
    sim_end_measurement_call = true;
  } else {
    message_set_ctrl(msg_no, MESSAGE_NAK);
  }
  message_clear_data(msg_no);
}

void sim_on_image_req(int msg_no) {
	sim_req_measimage_call = true;
	char print_field_buffer2[10];
	int imagecounter_req = 0;
	int imagenumber_req = 1;
	
	message_read_status_t read_stat;

	read_stat = message_read_string(msg_no, print_field_buffer2);
	if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

	read_stat = message_read_int(msg_no, &meas_id);
	if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

	delay(500);
	message_set_opcode(msg_no, MESSAGE_OPCODE_MEAS_IMAGE);
	message_set_ctrl(msg_no, MESSAGE_ACK);
	message_clear_data(msg_no);

	imagecounter_req = 0;
	imagenumber_req = 1;

	delay(1000);
	while(sim_req_measimage_call){
	sim_image(SIM_MEAS_IMAGE_MSG_NO, meas_id, imagecounter_req, imagenumber_req);
    message_send(SIM_MEAS_IMAGE_MSG_NO);
    imagecounter_req++;
         sim_wait_response([]() {
             //delayed_set_state(sim_image_mode, MAIN_STATE_NO, SIM_COVER_CLOSE_DELAY);
             });

         if (imagecounter_req >= 12) {
			 imagenumber_req++;
			 imagecounter_req = 0;
			 if (imagenumber_req >= 10)sim_req_measimage_call = false;
         }
	delay(500);
	}

nak:
	message_set_ctrl(msg_no, MESSAGE_NAK);
	message_clear_data(msg_no);
	return;
		
}

void sim_on_paramread_op(int msg_no, bool isInit) {
	char motion[10];
	char range[10];
	int parameter;
	int subparameter;
	int delInit = 0; // default READ
	int isAll = 0; // default not ALL
	message_read_status_t read_stat;
	message_reset_data(msg_no);

	if (isInit){
		read_stat = message_read_string(msg_no, motion);
		if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

		if (strcmp(motion, "INIT" ) == 0)
			delInit = 1;
		else if  (strcmp(motion, "DEL" ) == 0)
			delInit = 2;

		read_stat = message_read_string(msg_no, range);
		if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

		if (strcmp(range, "ALL" ) == 0)
			isAll = 1;

		read_stat = message_read_int(msg_no, &parameter);
		if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

		read_stat = message_read_int(msg_no, &subparameter);
		if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
	}else{

		read_stat = message_read_string(msg_no, motion);
		if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

		read_stat = message_read_int(msg_no, &parameter);
		if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

		read_stat = message_read_int(msg_no, &subparameter);
		if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
	}

	//if (parameter == 21){
	//	delayed_set_state(sim_on_system_version, MAIN_STATE_NO, 500);
	//}
	delay(1500);
	dummy_param_reading(msg_no, parameter, subparameter, delInit, isAll);
	return;

	nak:
    message_set_ctrl(msg_no, MESSAGE_NAK);
    message_clear_data(msg_no);
}

//void sim_on_paramread_op_detailed() {
	 //Serial.println("started vers");
//	 vercounter++;
//    dummy_system_version(1, vercounter);
//     if (vercounter <= 8) {
//        sim_wait_response([]() {
//            delayed_set_state(sim_on_system_version, MAIN_STATE_NO, 500);
//             });
//     }else{
//		 if (sim_error_popUp_call)
//			 set_state(sim_error_popUp_forced, MAIN_STATE_NO);
//		 else
//			 set_state(EMPTY_STATE_FUNC, MAIN_STATE_NO);
//		  //set_state(sim_ext_request_proc, BG_PROC_STATE_NO);
//	 }
//}

void sim_on_menu_op(int msg_no) {
    int mode = 0;
    int msg_no2 = 0;
    int params = 0;
	int process = 0;
    char print_field_buffer2[10];
	char print_field_buffer3[30];
	char print_field_buffer4[10];

    Serial.println("menu_recieved");
    message_read_status_t read_stat;
	message_reset_data(msg_no);

    read_stat = message_read_string(msg_no, print_field_buffer2);
    if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
            msg_no2 = SIM_MENU_MSG_NO;
        if (strcmp(print_field_buffer2, MENU_MODE_0) == 0) {

			// step 
			read_stat = message_read_string(msg_no, print_field_buffer3);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
			
			// test adj
			read_stat = message_read_string(msg_no, print_field_buffer3);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

			// parameter 1
			read_stat = message_read_string(msg_no, print_field_buffer3);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
				
			// parameter 2
			read_stat = message_read_string(msg_no, wc_menu_mode.returndata.data1);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

			delay(500);
			// parameter 3
			read_stat = message_read_string(msg_no, wc_menu_mode.returndata.data2);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

            mode = 0;
            params = 10;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_1) == 0) {
            mode = 1;
            params = 3;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_2) == 0) {
            mode = 2;
            params = 3;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_3) == 0) {
            mode = 3;
            params = 5;
			// step 
			read_stat = message_read_string(msg_no, print_field_buffer3);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
			
			// test adj
			read_stat = message_read_string(msg_no, print_field_buffer3);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

			// parameter 1
			read_stat = message_read_string(msg_no, print_field_buffer3);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
				
			// parameter 2
			read_stat = message_read_string(msg_no, wc_menu_mode.returndata.data1);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_4) == 0) {
            mode = 4;
            params = 5;
						// step 
			read_stat = message_read_string(msg_no, print_field_buffer3);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
			
			// test adj
			read_stat = message_read_string(msg_no, print_field_buffer3);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

			// parameter 1
			read_stat = message_read_string(msg_no, print_field_buffer3);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
				
			// parameter 2
			read_stat = message_read_string(msg_no, wc_menu_mode.returndata.data1);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_5) == 0) {

            mode = 5;
			wc_menu_mode.menumode = mode;
			set_menu_mode(wc_menu_mode);
			read_stat = message_read_string(msg_no, print_field_buffer3);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

			 if(strcmp(print_field_buffer3, "0") == 0) {
				dummy_menuadj(msg_no);
				message_send(SIM_EXT_REQUEST_MSG_NO);
				message_reset_data(msg_no);
				delay(1000);

				dummy_menuadj_cont(msg_no, mode, 0, RESULT_FAIL);
			 }else if(strcmp(print_field_buffer3, "2") == 0){

				dummy_menuadj(msg_no);
				message_send(SIM_EXT_REQUEST_MSG_NO);
				message_reset_data(msg_no);
				delay(1000);

				dummy_menuadj_cont(msg_no, mode, 2, RESULT_FAIL);
			 }else if(strcmp(print_field_buffer3, "4") == 0){

				read_stat = message_read_string(msg_no, print_field_buffer4);
				if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

				if(strcmp(print_field_buffer4, "0") == 0) {
					dummy_menuadj(msg_no);
					message_send(SIM_EXT_REQUEST_MSG_NO);
					message_reset_data(msg_no);
					delay(1000);

					dummy_menuadj_cont(msg_no, mode, 4, RESULT_FAIL);
				}else{

					dummy_menuadj(msg_no);
					message_send(SIM_EXT_REQUEST_MSG_NO);
					message_reset_data(msg_no);
					delay(1000);
					
					dummy_menuadj_cont(msg_no, mode, 4, 1);
				}
			 }
			message_send(SIM_EXT_REQUEST_MSG_NO);
			return;
        }
		if (strcmp(print_field_buffer2, MENU_MODE_6) == 0) {

            mode = 6;
			wc_menu_mode.menumode = mode;
			set_menu_mode(wc_menu_mode);
			read_stat = message_read_string(msg_no, print_field_buffer3);

			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

			 if(strcmp(print_field_buffer3, "0") == 0) {
				dummy_menuadj(msg_no);
				message_send(SIM_EXT_REQUEST_MSG_NO);

				dummy_menuadj_cont(msg_no, mode, 0, 0);
			 }else if(strcmp(print_field_buffer3, "2") == 0){

				read_stat = message_read_string(msg_no, print_field_buffer4);
				if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

				if(strcmp(print_field_buffer4, "0") == 0) {
					dummy_menuadj(msg_no);
					message_send(SIM_EXT_REQUEST_MSG_NO);
					message_reset_data(msg_no);
					delay(1000);

					dummy_menuadj_cont(msg_no, mode, 2, 0);
				}else if(strcmp(print_field_buffer4, "1") == 0){

					dummy_menuadj(msg_no);
					message_send(SIM_EXT_REQUEST_MSG_NO);
					message_reset_data(msg_no);
					delay(1000);

					dummy_menuadj_cont(msg_no, mode, 2, 1);
				}else if(strcmp(print_field_buffer4, "2") == 0){
					dummy_menuadj(msg_no);
					message_send(SIM_EXT_REQUEST_MSG_NO);
					message_reset_data(msg_no);
					delay(1000);

					dummy_menuadj_cont(msg_no, mode, 2, 2);
				}
			 }else if(strcmp(print_field_buffer3, "4") == 0){

				read_stat = message_read_string(msg_no, print_field_buffer4);
				if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;

				if(strcmp(print_field_buffer4, "0") == 0) {

					dummy_menuadj(msg_no);
					message_send(SIM_EXT_REQUEST_MSG_NO);
					message_reset_data(msg_no);
					delay(1000);

					dummy_menuadj_cont(msg_no, mode, 4, 0);
				}else{

					dummy_menuadj(msg_no);
					message_send(SIM_EXT_REQUEST_MSG_NO);
					message_reset_data(msg_no);
					delay(1000);

					dummy_menuadj_cont(msg_no, mode, 4, 1);
				}
			 }
			message_send(SIM_EXT_REQUEST_MSG_NO);
			return;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_7) == 0) {
            mode = 7;
            params = 24;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_8) == 0) {
            mode = 8;
            params = 9;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_9) == 0) {
            mode = 9;
            params = 5;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_10) == 0) {
            mode = 10;
            params = 5;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_11) == 0) {
            mode = 11;
            params = 5;
        }
		    if (strcmp(print_field_buffer2, MENU_MODE_20) == 0) {
            mode = 20;
            params = 11;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_21) == 0) {
            mode = 21;
            params = 4;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_22) == 0) {
            mode = 22;
            params = 15;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_23) == 0) {
            mode = 23;
            params = 6;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_24) == 0) {
            mode = 24;
            params = 15;
        }
        if (strcmp(print_field_buffer2, MENU_MODE_25) == 0) {
            mode = 25;
        }
		if (strcmp(print_field_buffer2, MENU_MODE_26) == 0) {
            mode = 26;
			read_stat = message_read_string(msg_no, print_field_buffer3);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
			read_stat = message_read_string(msg_no, print_field_buffer4);
			if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
			set_menu_mode(wc_menu_mode);
			 if(strcmp(print_field_buffer4, "0") == 0) {
				 wc_menu_mode.testno = 0;
			  }else if(strcmp(print_field_buffer4, "1") == 0){
				 wc_menu_mode.testno = 1;
			 }
        }
		process = 1;
		wc_menu_mode.menumode = mode;
		wc_menu_mode.parameters = params;
		wc_menu_mode.onProcess = process;
		set_menu_mode(wc_menu_mode);

		dummy_menumode(msg_no);
		message_send(SIM_EXT_REQUEST_MSG_NO);
		if (strcmp(print_field_buffer3, "0") && (mode == 26))
			return;
		message_reset_data(msg_no);
menuloop:
/* For Resume Process Use
		if(sim_stop_measurement_menu_call){
			if (menu_stop_standby_start == 0){
				menu_resume_timer = menu_resume_timer - (millis() - menu_stop_standby_start);
				menu_stop_standby_start = millis();
				menu_standby_start = 0;
				calib_state = CALB_STATE_STOPPING;
			}
			if (millis() - menu_stop_standby_start >= 5000) {
					dummy_menumode_cont(msg_no, mode, params, RESULT_FAIL);
					message_send(SIM_EXT_REQUEST_MSG_NO);
					menu_resume_timer = 5000;
					menu_stop_standby_start = 0;
					sim_stop_measurement_menu_call = false;
					calib_state = CALB_STATE_INIT;
					return;
			}else{
				Serial.println("ON STOPPING");
				goto betlog;
			}
		}else{
*/
			if (menu_standby_start == 0){
				menu_standby_start = millis();
				Serial.println("ON STANDBY_1");
			}
			if (millis() - menu_standby_start >= menu_resume_timer) {
					dummy_menumode_cont(msg_no, mode, params,RESULT_OK);
					message_send(SIM_EXT_REQUEST_MSG_NO);
					menu_standby_start = 0;
					sim_stop_measurement_menu_call = false;
					Serial.println("ON STANDBY_2");
					return;
			}else{
				Serial.println("ON STANDBY_3");
				delay(500);
				goto menuloop;
			}
//		}
		Serial.println("ON STANDBY_4");
        
    nak:
        message_set_ctrl(msg_no, MESSAGE_NAK);
        message_clear_data(msg_no);
     
 }
void sim_on_adjust_op(int msg_no) {

	char lcl_fieldlabel[100];
	char lcl_direction[3];
	char lcl_pls[255];
	char lcl_defaultpls[100];
	char lcl_currentpls[100];

    Serial.println("adjust_recieved");
    message_read_status_t read_stat;
	read_stat = message_read_string(msg_no, lcl_fieldlabel);
	if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
	strcpy(wc_adj_common.read_fieldlabel, lcl_fieldlabel);

	read_stat = message_read_string(msg_no, lcl_direction);
	if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
	strcpy(wc_adj_common.read_direction, lcl_direction);

	read_stat = message_read_string(msg_no, lcl_pls); 
	if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
	strcpy(wc_adj_common.read_pls, lcl_pls);

	read_stat = message_read_string(msg_no, lcl_defaultpls);
	if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
	strcpy(wc_adj_common.read_defaultpls, lcl_defaultpls);

	read_stat = message_read_string(msg_no, lcl_currentpls);
	if (!MESSAGE_READ_SUCCESS(read_stat)) goto nak;
	strcpy(wc_adj_common.read_currentpls, lcl_currentpls);
	  
	set_adj_common(wc_adj_common);

	dummy_adjust(msg_no);
	message_send(SIM_EXT_REQUEST_MSG_NO);

	message_clear_data(msg_no);
	delay(1500);

	dummy_adjust_cont(msg_no);
	message_send(SIM_EXT_REQUEST_MSG_NO);

    return;
    
	nak:
        message_set_ctrl(msg_no, MESSAGE_NAK);
        message_clear_data(msg_no);
 }

// on sequence
bool sim_read_wifi_settings(int msg_no) {
  char field_buffer[1000];
  char connection_mode[3];
  char wifi_ssid[19];
  char wifi_psk[19];
  message_read_status_t read_stat;
  message_reset_data(msg_no);
  for (int idx = 0; idx < 17; idx++) { //Skip 17 fields
    read_stat = message_read_string(msg_no, field_buffer);
    if (!MESSAGE_READ_SUCCESS(read_stat)) return false;
  }
  read_stat = message_read_string(msg_no, connection_mode);
  if (!MESSAGE_READ_SUCCESS(read_stat)) return false;
  read_stat = message_read_string(msg_no, field_buffer); //Skip wifi name
  if (!MESSAGE_READ_SUCCESS(read_stat)) return false;
  read_stat = message_read_string(msg_no, wifi_ssid);
  if (!MESSAGE_READ_SUCCESS(read_stat)) return false;
  read_stat = message_read_string(msg_no, wifi_psk);
  if (!MESSAGE_READ_SUCCESS(read_stat)) return false;
  // Ignore remaining fields
  Serial.println("WiFi settings modify");
  Serial.print("Mode: ");
  Serial.println(connection_mode);
  Serial.print("SSID: ");
  Serial.println(wifi_ssid);
  Serial.print("PSK: ");
  Serial.println(wifi_psk);
  wifi_settings_t settings;
  settings.is_set = true;
  if (strcmp(connection_mode, "AP") == 0) {
    settings.is_ap = true;
  } else if (strcmp(connection_mode, "ST") == 0) {
    settings.is_ap = false;
  } else {
    return false;
  }
  strcpy(settings.ssid, wifi_ssid);
  strcpy(settings.psk, wifi_psk);
  set_wifi_settings(settings);
  return true;
}

void sim_on_adjust_param_reading(int msg_no) {
  if (sim_read_wifi_settings(msg_no)) {
    message_set_ctrl(msg_no, MESSAGE_ACK);
    wifi_disconnect();
    wifi_connect(
      BG_PROC_STATE_NO,
      [] () { //on_connect
        set_state(sim_ext_request_proc, BG_PROC_STATE_NO);
      },
      [] () { //on_error
        Serial.println("ERROR: Wifi connection");
        set_state(sim_ext_request_proc, BG_PROC_STATE_NO);
      }
    );
  } else {
    message_set_ctrl(msg_no, MESSAGE_NAK);
  }
  message_clear_data(msg_no);
}

void sim_ext_request_proc() {
  if (message_recv(SIM_EXT_REQUEST_MSG_NO)) {
    if (message_get_ctrl(SIM_EXT_REQUEST_MSG_NO) == MESSAGE_ENQ) {
      switch (message_get_opcode(SIM_EXT_REQUEST_MSG_NO)) {
        case MESSAGE_OPCODE_ADJUST_PARAM_READING:
			sim_on_adjust_param_reading(SIM_EXT_REQUEST_MSG_NO);
			break;
        case MESSAGE_OPCODE_GET_STATUS:
			sim_on_get_status(SIM_EXT_REQUEST_MSG_NO);
			break;
        case MESSAGE_OPCODE_COVER_OP:
			sim_on_cover_operation(SIM_EXT_REQUEST_MSG_NO);
			break;
        case MESSAGE_OPCODE_GET_ERR_INFO:
			dummy_error_info(SIM_EXT_REQUEST_MSG_NO);
			break;
        case MESSAGE_OPCODE_GET_MEAS_TIME:
			sim_on_get_meas_time(SIM_EXT_REQUEST_MSG_NO);
			break;

        case MESSAGE_OPCODE_GET_SYSTEM_INFO:
			sim_on_get_sysinfo(SIM_EXT_REQUEST_MSG_NO);
			break;

        case MESSAGE_OPCODE_GET_PARAM_READING:
			sim_on_paramread_op(SIM_EXT_REQUEST_MSG_NO, false);
			break;

        case MESSAGE_OPCODE_GET_PARAM_INITIALIZING:
			sim_on_paramread_op(SIM_EXT_REQUEST_MSG_NO, true);
			break;

        case MESSAGE_OPCODE_GET_REAGENT_INFO_LIST:
			dummy_reagent_info_list(SIM_EXT_REQUEST_MSG_NO);
			break;
        case MESSAGE_OPCODE_GET_REAGENT_INFO:
			sim_on_reagent_info(SIM_EXT_REQUEST_MSG_NO);
			break;
        case MESSAGE_OPCODE_SETUP_MEAS:
			sim_on_setup_meas(SIM_EXT_REQUEST_MSG_NO);
			break;
        case MESSAGE_OPCODE_START_MEAS:
			sim_on_start_meas(SIM_EXT_REQUEST_MSG_NO, false);
			break;
        case MESSAGE_OPCODE_STOP_MEAS:
			sim_on_stop_meas(SIM_EXT_REQUEST_MSG_NO);
			break;
		case MESSAGE_OPCODE_STAT_MEAS:
			//delay(2000);
			sim_on_start_meas(SIM_EXT_REQUEST_MSG_NO, true);
			break;
        case MESSAGE_OPCODE_END_MEAS:
			sim_on_end_meas(SIM_EXT_REQUEST_MSG_NO);
			break;

		case MESSAGE_OPCODE_MEAS_IMAGE:
			sim_on_image_req(SIM_EXT_REQUEST_MSG_NO);
			break;
        //new
        case MESSAGE_OPCODE_MENU_OP:
			sim_on_menu_op(SIM_EXT_REQUEST_MSG_NO);
			return;
			break;
		case MESSAGE_OPCODE_ADJ_OP:
			sim_on_adjust_op(SIM_EXT_REQUEST_MSG_NO);
			return;
			break;
        //new
        case MESSAGE_OPCODE_RES_EDIT:
			//sim_on_result_edit(SIM_EXT_REQUEST_MSG_NO);
			return;
			break;
		//new
        case MESSAGE_OPCODE_SHUTDOWN:
			sim_on_shutdown(SIM_EXT_REQUEST_MSG_NO);
			break;
        default:
			break;
      }
      message_send(SIM_EXT_REQUEST_MSG_NO);
    } else {
      sim_has_response = true;
    }
  }
}
