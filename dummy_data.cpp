#include "constants.h"
#include "prototypes.h"

void dummy_system_info(int msg_no) {
  message_set_opcode(msg_no, MESSAGE_OPCODE_GET_SYSTEM_INFO);
  message_set_ctrl(msg_no, MESSAGE_ACK);
  message_clear_data(msg_no);
  message_put_string(msg_no, param_get_ope_mode()); //Operation mode
  message_put_string(msg_no, "0000000000000000"); //Boot program name
  message_put_string(msg_no, "0000000000"); //Boot program version
  message_put_string(msg_no, "0000000000000000"); //Boot program date
  message_put_string(msg_no, "0000000000000000"); //Write program name
  message_put_string(msg_no, "0000000000"); //Write program version
  message_put_string(msg_no, "0000000000000000"); //Write program date
  message_put_string(msg_no, "0000000000000000"); //Main program name
  message_put_string(msg_no, "0000000000"); //Main program version
  message_put_string(msg_no, "0000000000000000"); //Main program date
  message_put_string(msg_no, "0000000000000000"); //Sub boot program name
  message_put_string(msg_no, "0000000000"); //Sub boot program version
  message_put_string(msg_no, "0000000000000000"); //Sub boot program date
  message_put_string(msg_no, "0000000000000000"); //Sub write program name
  message_put_string(msg_no, "0000000000"); //Sub write program version
  message_put_string(msg_no, "0000000000000000"); //Sub write program date
  message_put_string(msg_no, "0000000000000000"); //Sub program name
  message_put_string(msg_no, "0000000000"); //Sub program version
  message_put_string(msg_no, "0000000000000000"); //Sub program date
  message_put_string(msg_no, "0000000000000000"); //Wifi module name
  message_put_string(msg_no, "0000000000"); //Wifi module version
  message_put_string(msg_no, "0000000000000000"); //Wifi module date
  message_put_string(msg_no, "0000000000000000"); //Bluetooth module name
  message_put_string(msg_no, "0000000000"); //Bluetooth module version
  message_put_string(msg_no, "0000000000000000"); //Bluetooth module date
  message_put_string(msg_no, param_get_serial_no()); //Serial No.
  message_put_string(msg_no, "00"); //Spec. No.
  message_put_string(msg_no, "00"); //Rev. No.
  message_put_string(msg_no, param_get_device_name()); //Device name

  message_send(0);
}

void dummy_system_version(int msg_no, int count) {
	int randomo;
	switch(count){
	case 1:
		  Serial.println("Sysinfo_send_again1");
		  message_set_opcode(msg_no, MESSAGE_OPCODE_GET_SYSTEM_INFO);
		  message_set_ctrl(msg_no, MESSAGE_ENQ);
		  message_clear_data(msg_no);

		  message_put_string(msg_no, "SERIAL"); //Reference
		  message_put_string(msg_no, param_get_serial_no()); //Serial No.
		  randomo = (rand() % 801);
		  //randomo = (rand() % 2);
		  message_put_int(msg_no, randomo);  
		  message_send(1);
		break;
	case 2:
		  Serial.println("Sysinfo_send_again2");
		  message_set_opcode(msg_no, MESSAGE_OPCODE_GET_SYSTEM_INFO);
		  message_set_ctrl(msg_no, MESSAGE_ENQ);
		  message_clear_data(msg_no);
		  message_put_string(msg_no, "MAIN_ROM_VER"); //Reference
		  for (int idx = 1; idx <= 4; idx++) {
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                    //status
		  }
		  message_send(1);
		break;	
	case 3:
		  Serial.println("Sysinfo_send_again3");
		  message_set_opcode(msg_no, MESSAGE_OPCODE_GET_SYSTEM_INFO);
		  message_set_ctrl(msg_no, MESSAGE_ENQ);
		  message_clear_data(msg_no);
		  message_put_string(msg_no, "IF_ROM_VER"); //Reference
		  for (int idx = 1; idx <= 4; idx++) {
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                   //status
		  }
		  message_send(1);
		break;	
  	case 4:
		  Serial.println("Sysinfo_send_again3");
		  message_set_opcode(msg_no, MESSAGE_OPCODE_GET_SYSTEM_INFO);
		  message_set_ctrl(msg_no, MESSAGE_ENQ);
		  message_clear_data(msg_no);
		  message_put_string(msg_no, "MEAS_ROM_VER"); //Reference
		  for (int idx = 1; idx <= 4; idx++) {
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                   //status
		  }
		  message_send(1);
		break;	
	case 5:
		  Serial.println("Sysinfo_send_again5");
		  message_set_opcode(msg_no, MESSAGE_OPCODE_GET_SYSTEM_INFO);
		  message_set_ctrl(msg_no, MESSAGE_ENQ);
		  message_clear_data(msg_no);
		  message_put_string(msg_no, "FEEDER_ROM_VER"); //Reference
		  for (int idx = 1; idx <= 4; idx++) {
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                    //status
		  }
		  message_send(1);
		break;
	case 6:
		  Serial.println("Sysinfo_send_again6");
		  message_set_opcode(msg_no, MESSAGE_OPCODE_GET_SYSTEM_INFO);
		  message_set_ctrl(msg_no, MESSAGE_ENQ);
		  message_clear_data(msg_no);
		  message_put_string(msg_no, "NOZZLE_ROM_VER"); //Reference
		  for (int idx = 1; idx <= 4; idx++) {
			randomo = (rand() % 801);
			message_put_int(msg_no, randomo);                   //status
		  }
		  message_send(1);

		break;
	case 7:
		  Serial.println("Sysinfo_send_again7");
		  message_set_opcode(msg_no, MESSAGE_OPCODE_GET_SYSTEM_INFO);
		  message_set_ctrl(msg_no, MESSAGE_ENQ);
		  message_clear_data(msg_no);
		  message_put_string(msg_no, "SAMPLER_ROM_VER"); //Reference
		  for (int idx = 1; idx <= 4; idx++) {
			randomo = (rand() % 801);
			message_put_int(msg_no, randomo);                   //status
		  }
		  message_send(1);
		break;
	case 8:
		  Serial.println("Sysinfo_send_again8");
		  message_set_opcode(msg_no, MESSAGE_OPCODE_GET_SYSTEM_INFO);
		  message_set_ctrl(msg_no, MESSAGE_ENQ);
		  message_clear_data(msg_no);
		  message_put_string(msg_no, "LIQUID_DETECT_ROM_VER"); //Reference
		  for (int idx = 1; idx <= 4; idx++) {
			randomo = (rand() % 801);
			message_put_int(msg_no, randomo);                   //status
		  }
		  message_send(1);
		break;
	case 9:
		  Serial.println("Sysinfo_send_again9");
		  message_set_opcode(msg_no, MESSAGE_OPCODE_GET_SYSTEM_INFO);
		  message_set_ctrl(msg_no, MESSAGE_ENQ);
		  message_clear_data(msg_no);
		  message_put_string(msg_no, "MOTOR_CONTROL_ROM_VER"); //Reference
		  for (int idx = 1; idx <= 4; idx++) {
			randomo = (rand() % 801);
			message_put_int(msg_no, randomo);                    //status
		  }
		  message_send(1);
		break;
	default:
		break;
	}
}

void dummy_reagent_info_list(int msg_no) {
  message_set_opcode(msg_no, MESSAGE_OPCODE_GET_REAGENT_INFO_LIST);
  message_set_ctrl(msg_no, MESSAGE_ACK);
  message_clear_data(msg_no);
  //Single
  for (int idx = 0; idx < 32; idx++) {
    message_put_string(msg_no, "0"); //Rev no. Basic info Rev A
    message_put_string(msg_no, "0"); //Rev no. Basic info Rev B
    message_put_string(msg_no, "00"); //Lot no. Lot info Lot A
    message_put_string(msg_no, "00"); //Lot no. Lot info Lot B
  }
  //Multi
  for (int idx = 0; idx < 16; idx++) {
    message_put_string(msg_no, "0"); //Rev no. Basic info Rev A
    message_put_string(msg_no, "0"); //Rev no. Basic info Rev B
    message_put_string(msg_no, "00"); //Lot no. Lot info Lot A
    message_put_string(msg_no, "00"); //Lot no. Lot info Lot B
  }
  //EL
  for (int idx = 0; idx < 8; idx++) {
    message_put_string(msg_no, "0"); //Rev no. Basic info Rev A
    message_put_string(msg_no, "0"); //Rev no. Basic info Rev B
  }
  //EPlate
  for (int idx = 0; idx < 8; idx++) {
    message_put_string(msg_no, "0"); //Rev no. Basic info Rev A
    message_put_string(msg_no, "0"); //Rev no. Basic info Rev B
    message_put_string(msg_no, "00"); //Lot no. Lot info Lot A
    message_put_string(msg_no, "00"); //Lot no. Lot info Lot B
  }
}
void dummy_single_basic(int msg_no, char *item_no, char *lot_no) {
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
}

void dummy_single_lot(int msg_no, char *item_no, char *lot_no) {
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
}

void dummy_multi_basic(int msg_no, char *item_no, char *lot_no) {
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
}

void dummy_multi_lot(int msg_no, char *item_no, char *lot_no) {
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
}

void dummy_el_basic(int msg_no, char *item_no, char *lot_no) {
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
}

void dummy_eplate_basic(int msg_no, char *item_no, char *lot_no) {
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
}

void dummy_eplate_lot(int msg_no, char *item_no, char *lot_no) {
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
  message_put_string(msg_no, "0");
}

void dummy_reagent_info(int msg_no, int request_it, char *item_no, char *lot_no) {
  message_set_opcode(msg_no, MESSAGE_OPCODE_GET_REAGENT_INFO);
  message_set_ctrl(msg_no, MESSAGE_ACK);
  message_clear_data(msg_no);
  switch (request_it) {
    case REAGENT_SINGLE_BASIC:
    dummy_single_basic(msg_no, item_no, lot_no);
    break;
    case REAGENT_SINGLE_LOT:
    dummy_single_lot(msg_no, item_no, lot_no);
    break;
    case REAGENT_MULTI_BASIC:
    dummy_multi_basic(msg_no, item_no, lot_no);
    break;
    case REAGENT_MULTI_LOT:
    dummy_multi_lot(msg_no, item_no, lot_no);
    break;
    case REAGENT_EL_BASIC:
    dummy_el_basic(msg_no, item_no, lot_no);
    break;
    case REAGENT_EPLATE_BASIC:
    dummy_eplate_basic(msg_no, item_no, lot_no);
    break;
    case REAGENT_EPLATE_LOT:
    dummy_eplate_lot(msg_no, item_no, lot_no);
    break;
  }
}

void dummy_error_info(int msg_no) {
  message_set_opcode(msg_no, MESSAGE_OPCODE_GET_ERR_INFO);
  message_set_ctrl(msg_no, MESSAGE_ACK);
  message_clear_data(msg_no);
  message_put_int(msg_no, 0); //Error count
}

void dummy_error_notice(int msg_no) {
  message_set_opcode(msg_no, MESSAGE_OPCODE_ERR_NTC);
  message_set_ctrl(msg_no, MESSAGE_ENQ);
  message_clear_data(msg_no);
  message_put_string(msg_no, "0000"); //Error no.
  message_put_int(msg_no, 0); //Status
  message_put_string(msg_no, "00000000000000000000"); //File name
  message_put_int(msg_no, 0); //Line
  message_put_string(msg_no, "00000000000000000000000000000000000000000000000000"); //Additional info
}

void dummy_param_reading(int msg_no, int parameter, int subparameter, int delInit, int isAll ) {
	int randomo;

	if (delInit == 2){
		return;
	}else if(delInit == 1){
		message_set_opcode(msg_no, MESSAGE_OPCODE_GET_PARAM_INITIALIZING);
	}else{
		message_set_opcode(msg_no, MESSAGE_OPCODE_GET_PARAM_READING);
	}

    message_set_ctrl(msg_no, MESSAGE_ACK);
    message_clear_data(msg_no);

	if (parameter == 1){
		message_put_string(msg_no, "QC_MATERIAL");
		for (int idx = 0; idx < 80; idx++) {
			if ((idx == 3)||(idx == 4)||(idx == 5)){
				message_put_string(msg_no,"2223-01-01 11:11:11"); //
				continue;
			}
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  
		}
	}else if (parameter == 2){
		message_put_string(msg_no, "USRE_ACCOUNT");
		for (int idx = 0; idx < 13; idx++) {
			if ((idx == 10)||(idx == 11)||(idx == 12)){
				message_put_string(msg_no,"2223-01-01 11:11:11"); //
				continue;
			}
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  
		}
	}else if (parameter == 3){
    message_put_string(msg_no, "STRIP_ITEM");
    switch(subparameter){
      	case 1:    
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 0);
			message_put_string(msg_no, "GLU");
			message_put_int(msg_no, 15);  
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 5);    
			message_put_int(msg_no, 5.55);
			message_put_int(msg_no, 1111);
			message_put_int(msg_no, 9999);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 9888.9888);
			message_put_int(msg_no, 9565.2311);
			message_put_int(msg_no, 9222.9841);
			message_put_int(msg_no, 1231.5123);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "00000000.1111111$22222222.33333333$44444444.5555555$66666666.7777777$11111111.22222222$33333333.44444444$55555555.66666666$77777777.88888888$99999999.9999999^");    
			message_put_int(msg_no, 0.0);
			message_put_int(msg_no, 99.9);
			message_put_int(msg_no, 95.9);
			message_put_int(msg_no, 93.9);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 996.8);
			message_put_int(msg_no, 993.1);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 193.6);
			message_put_int(msg_no, 593.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 293.6);
			message_put_int(msg_no, 153.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 9.7865);
			message_put_int(msg_no, 7777.7777);
			message_put_int(msg_no, 987.4);
			break;
		case 2:
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_string(msg_no, "PRO");
			message_put_int(msg_no, 15);  
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 5);    
			message_put_int(msg_no, 5.55);
			message_put_int(msg_no, 1111);
			message_put_int(msg_no, 9999);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 9888.9888);
			message_put_int(msg_no, 9565.2311);
			message_put_int(msg_no, 9222.9841);
			message_put_int(msg_no, 1231.5123);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "00000000.1111111$22222222.33333333$44444444.5555555$66666666.7777777$11111111.22222222$33333333.44444444$55555555.66666666$77777777.88888888$99999999.9999999^");    
			message_put_int(msg_no, 0.0);
			message_put_int(msg_no, 99.9);
			message_put_int(msg_no, 95.9);
			message_put_int(msg_no, 93.9);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 996.8);
			message_put_int(msg_no, 993.1);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 193.6);
			message_put_int(msg_no, 593.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 293.6);
			message_put_int(msg_no, 153.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 9.7865);
			message_put_int(msg_no, 7777.7777);
			message_put_int(msg_no, 987.4);
			break;	
		case 3:
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 0);
			message_put_string(msg_no, "KET");
			message_put_int(msg_no, 15);  
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 5);    
			message_put_int(msg_no, 5.55);
			message_put_int(msg_no, 1111);
			message_put_int(msg_no, 9999);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 9888.9888);
			message_put_int(msg_no, 9565.2311);
			message_put_int(msg_no, 9222.9841);
			message_put_int(msg_no, 1231.5123);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "00000000.1111111$22222222.33333333$44444444.5555555$66666666.7777777$11111111.22222222$33333333.44444444$55555555.66666666$77777777.88888888$99999999.9999999^");    
			message_put_int(msg_no, 0.0);
			message_put_int(msg_no, 99.9);
			message_put_int(msg_no, 95.9);
			message_put_int(msg_no, 93.9);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 996.8);
			message_put_int(msg_no, 993.1);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 193.6);
			message_put_int(msg_no, 593.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 293.6);
			message_put_int(msg_no, 153.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 9.7865);
			message_put_int(msg_no, 7777.7777);
			message_put_int(msg_no, 987.4);
			break;	
		case 4:
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 0);
			message_put_string(msg_no, "BIL");
			message_put_int(msg_no, 15);  
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 5);    
			message_put_int(msg_no, 5.55);
			message_put_int(msg_no, 1111);
			message_put_int(msg_no, 9999);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 9888.9888);
			message_put_int(msg_no, 9565.2311);
			message_put_int(msg_no, 9222.9841);
			message_put_int(msg_no, 1231.5123);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "00000000.1111111$22222222.33333333$44444444.5555555$66666666.7777777$11111111.22222222$33333333.44444444$55555555.66666666$77777777.88888888$99999999.9999999^");    
			message_put_int(msg_no, 0.0);
			message_put_int(msg_no, 99.9);
			message_put_int(msg_no, 95.9);
			message_put_int(msg_no, 93.9);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 996.8);
			message_put_int(msg_no, 993.1);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 193.6);
			message_put_int(msg_no, 593.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 293.6);
			message_put_int(msg_no, 153.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 9.7865);
			message_put_int(msg_no, 7777.7777);
			message_put_int(msg_no, 987.4);
			break;	
		case 5:
			message_put_int(msg_no, 5);
			message_put_int(msg_no, 0);
			message_put_string(msg_no, "URO");
			message_put_int(msg_no, 15);  
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 5);    
			message_put_int(msg_no, 5.55);
			message_put_int(msg_no, 1111);
			message_put_int(msg_no, 9999);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 9888.9888);
			message_put_int(msg_no, 9565.2311);
			message_put_int(msg_no, 9222.9841);
			message_put_int(msg_no, 1231.5123);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "00000000.1111111$22222222.33333333$44444444.5555555$66666666.7777777$11111111.22222222$33333333.44444444$55555555.66666666$77777777.88888888$99999999.9999999^");    
			message_put_int(msg_no, 0.0);
			message_put_int(msg_no, 99.9);
			message_put_int(msg_no, 95.9);
			message_put_int(msg_no, 93.9);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 996.8);
			message_put_int(msg_no, 993.1);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 193.6);
			message_put_int(msg_no, 593.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 293.6);
			message_put_int(msg_no, 153.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 9.7865);
			message_put_int(msg_no, 7777.7777);
			message_put_int(msg_no, 987.4);
			break;	
		case 6:
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 0);
			message_put_string(msg_no, "NITs");
			message_put_int(msg_no, 15);  
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 5);    
			message_put_int(msg_no, 5.55);
			message_put_int(msg_no, 1111);
			message_put_int(msg_no, 9999);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 9888.9888);
			message_put_int(msg_no, 9565.2311);
			message_put_int(msg_no, 9222.9841);
			message_put_int(msg_no, 1231.5123);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "00000000.1111111$22222222.33333333$44444444.5555555$66666666.7777777$11111111.22222222$33333333.44444444$55555555.66666666$77777777.88888888$99999999.9999999^");    
			message_put_int(msg_no, 0.0);
			message_put_int(msg_no, 99.9);
			message_put_int(msg_no, 95.9);
			message_put_int(msg_no, 93.9);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 996.8);
			message_put_int(msg_no, 993.1);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 193.6);
			message_put_int(msg_no, 593.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 293.6);
			message_put_int(msg_no, 153.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 9.7865);
			message_put_int(msg_no, 7777.7777);
			message_put_int(msg_no, 987.4);
			break;	
		case 7:
			message_put_int(msg_no, 7);
			message_put_int(msg_no, 0);
			message_put_string(msg_no, "pH");
			message_put_int(msg_no, 15);  
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 5);    
			message_put_int(msg_no, 5.55);
			message_put_int(msg_no, 1111);
			message_put_int(msg_no, 9999);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 9888.9888);
			message_put_int(msg_no, 9565.2311);
			message_put_int(msg_no, 9222.9841);
			message_put_int(msg_no, 1231.5123);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "00000000.1111111$22222222.33333333$44444444.5555555$66666666.7777777$11111111.22222222$33333333.44444444$55555555.66666666$77777777.88888888$99999999.9999999^");    
			message_put_int(msg_no, 0.0);
			message_put_int(msg_no, 99.9);
			message_put_int(msg_no, 95.9);
			message_put_int(msg_no, 93.9);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 996.8);
			message_put_int(msg_no, 993.1);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 193.6);
			message_put_int(msg_no, 593.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 293.6);
			message_put_int(msg_no, 153.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 9.7865);
			message_put_int(msg_no, 7777.7777);
			message_put_int(msg_no, 987.4);
			break;	
		case 8:
			message_put_int(msg_no, 8);
			message_put_int(msg_no, 0);
			message_put_string(msg_no, "BLD");
			message_put_int(msg_no, 15);  
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 5);    
			message_put_int(msg_no, 5.55);
			message_put_int(msg_no, 1111);
			message_put_int(msg_no, 9999);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 9888.9888);
			message_put_int(msg_no, 9565.2311);
			message_put_int(msg_no, 9222.9841);
			message_put_int(msg_no, 1231.5123);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "00000000.1111111$22222222.33333333$44444444.5555555$66666666.7777777$11111111.22222222$33333333.44444444$55555555.66666666$77777777.88888888$99999999.9999999^");    
			message_put_int(msg_no, 0.0);
			message_put_int(msg_no, 99.9);
			message_put_int(msg_no, 95.9);
			message_put_int(msg_no, 93.9);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 996.8);
			message_put_int(msg_no, 993.1);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 193.6);
			message_put_int(msg_no, 593.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 293.6);
			message_put_int(msg_no, 153.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 9.7865);
			message_put_int(msg_no, 7777.7777);
			message_put_int(msg_no, 987.4);
			break;	
		case 9:
			message_put_int(msg_no, 9);
			message_put_int(msg_no, 0);
			message_put_string(msg_no, "LEU");
			message_put_int(msg_no, 15);  
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 5);    
			message_put_int(msg_no, 5.55);
			message_put_int(msg_no, 1111);
			message_put_int(msg_no, 9999);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 9888.9888);
			message_put_int(msg_no, 9565.2311);
			message_put_int(msg_no, 9222.9841);
			message_put_int(msg_no, 1231.5123);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "00000000.1111111$22222222.33333333$44444444.5555555$66666666.7777777$11111111.22222222$33333333.44444444$55555555.66666666$77777777.88888888$99999999.9999999^");    
			message_put_int(msg_no, 0.0);
			message_put_int(msg_no, 99.9);
			message_put_int(msg_no, 95.9);
			message_put_int(msg_no, 93.9);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 996.8);
			message_put_int(msg_no, 993.1);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 193.6);
			message_put_int(msg_no, 593.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 293.6);
			message_put_int(msg_no, 153.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 9.7865);
			message_put_int(msg_no, 7777.7777);
			message_put_int(msg_no, 987.4);
			break;	
		case 10:
			message_put_int(msg_no, 10);
			message_put_int(msg_no, 0);
			message_put_string(msg_no, "CRE");
			message_put_int(msg_no, 15);  
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 5);    
			message_put_int(msg_no, 5.55);
			message_put_int(msg_no, 1111);
			message_put_int(msg_no, 9999);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 9888.9888);
			message_put_int(msg_no, 9565.2311);
			message_put_int(msg_no, 9222.9841);
			message_put_int(msg_no, 1231.5123);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "00000000.1111111$22222222.33333333$44444444.5555555$66666666.7777777$11111111.22222222$33333333.44444444$55555555.66666666$77777777.88888888$99999999.9999999^");    
			message_put_int(msg_no, 0.0);
			message_put_int(msg_no, 99.9);
			message_put_int(msg_no, 95.9);
			message_put_int(msg_no, 93.9);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 996.8);
			message_put_int(msg_no, 993.1);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 193.6);
			message_put_int(msg_no, 593.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 293.6);
			message_put_int(msg_no, 153.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 9.7865);
			message_put_int(msg_no, 7777.7777);
			message_put_int(msg_no, 987.4);
			break;	
		case 11:
			message_put_int(msg_no, 11);
			message_put_int(msg_no, 0);
			message_put_string(msg_no, "ALB");
			message_put_int(msg_no, 15);  
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 5);    
			message_put_int(msg_no, 5.55);
			message_put_int(msg_no, 1111);
			message_put_int(msg_no, 9999);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 9888.9888);
			message_put_int(msg_no, 9565.2311);
			message_put_int(msg_no, 9222.9841);
			message_put_int(msg_no, 1231.5123);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "00000000.1111111$22222222.33333333$44444444.5555555$66666666.7777777$11111111.22222222$33333333.44444444$55555555.66666666$77777777.88888888$99999999.9999999^");    
			message_put_int(msg_no, 0.0);
			message_put_int(msg_no, 99.9);
			message_put_int(msg_no, 95.9);
			message_put_int(msg_no, 93.9);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 996.8);
			message_put_int(msg_no, 993.1);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 193.6);
			message_put_int(msg_no, 593.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 293.6);
			message_put_int(msg_no, 153.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 9.7865);
			message_put_int(msg_no, 7777.7777);
			message_put_int(msg_no, 987.4);
			break;	
		case 12:
			message_put_int(msg_no, 12);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "P/C");
			message_put_int(msg_no, 15);  
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 5);    
			message_put_int(msg_no, 5.55);
			message_put_int(msg_no, 1111);
			message_put_int(msg_no, 9999);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 9888.9888);
			message_put_int(msg_no, 9565.2311);
			message_put_int(msg_no, 9222.9841);
			message_put_int(msg_no, 1231.5123);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "00000000.1111111$22222222.33333333$44444444.5555555$66666666.7777777$11111111.22222222$33333333.44444444$55555555.66666666$77777777.88888888$99999999.9999999^");    
			message_put_int(msg_no, 0.0);
			message_put_int(msg_no, 99.9);
			message_put_int(msg_no, 95.9);
			message_put_int(msg_no, 93.9);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 996.8);
			message_put_int(msg_no, 993.1);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 193.6);
			message_put_int(msg_no, 593.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 293.6);
			message_put_int(msg_no, 153.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 9.7865);
			message_put_int(msg_no, 7777.7777);
			message_put_int(msg_no, 987.4);
			break;	
		case 13:
			message_put_int(msg_no, 13);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "A/C");
			message_put_int(msg_no, 15);  
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 5);    
			message_put_int(msg_no, 5.55);
			message_put_int(msg_no, 1111);
			message_put_int(msg_no, 9999);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 9888.9888);
			message_put_int(msg_no, 9565.2311);
			message_put_int(msg_no, 9222.9841);
			message_put_int(msg_no, 1231.5123);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 1);
			message_put_string(msg_no, "00000000.1111111$22222222.33333333$44444444.5555555$66666666.7777777$11111111.22222222$33333333.44444444$55555555.66666666$77777777.88888888$99999999.9999999^");    
			message_put_int(msg_no, 0.0);
			message_put_int(msg_no, 99.9);
			message_put_int(msg_no, 95.9);
			message_put_int(msg_no, 93.9);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 3);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 996.8);
			message_put_int(msg_no, 993.1);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 4);
			message_put_int(msg_no, 6);
			message_put_int(msg_no, 1);
			message_put_int(msg_no, 193.6);
			message_put_int(msg_no, 593.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 293.6);
			message_put_int(msg_no, 153.2);
			message_put_int(msg_no, 0);
			message_put_int(msg_no, 9.7865);
			message_put_int(msg_no, 7777.7777);
			message_put_int(msg_no, 987.4);
			break;	
		default:
			break;
			}
	}else if (parameter == 4){
		message_put_string(msg_no, "CAL_CURVE");
		message_put_int(msg_no, subparameter);
		if (subparameter == 1){
			message_put_string(msg_no, "GLU");
			message_put_string(msg_no, "mg/dL");
			message_put_string(msg_no, "mmol/L");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");
		}else if(subparameter == 2){
			message_put_string(msg_no, "PRO");
			message_put_string(msg_no, "mg/dL");
			message_put_string(msg_no, "g/L");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");

		}else if(subparameter == 3){
			message_put_string(msg_no, "BIL");
			message_put_string(msg_no, "mg/dL");
			message_put_string(msg_no, "mmol/L");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");
		}else if(subparameter == 4){
			message_put_string(msg_no, "URO");
			message_put_string(msg_no, "mg/dL");
			message_put_string(msg_no, "mmol/L");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");
		}else if(subparameter == 5){
			message_put_string(msg_no, "pH");
			message_put_string(msg_no, "mmol/L");
			message_put_string(msg_no, " ");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");
		}else if(subparameter == 6){
			message_put_string(msg_no, "BLD");
			message_put_string(msg_no, "mg/dL");
			message_put_string(msg_no, "mmol/L");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");
		}else if(subparameter == 7){
			message_put_string(msg_no, "KET");
			message_put_string(msg_no, "mg/dL");
			message_put_string(msg_no, "mmol/L");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");
		}else if(subparameter == 8){
			message_put_string(msg_no, "NITs");
			message_put_string(msg_no, "mg/dL");
			message_put_string(msg_no, " ");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");
		}else if(subparameter == 9){
			message_put_string(msg_no, "LEU");
			message_put_string(msg_no, "Leu/ul");
			message_put_string(msg_no, "Leu/ul");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");
		}else if(subparameter == 10){
			message_put_string(msg_no, "CRE");
			message_put_string(msg_no, "mmol/L");
			message_put_string(msg_no, "g/L");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");
		}else if(subparameter == 11){
			message_put_string(msg_no, "ALB");
			message_put_string(msg_no, "mg/dL");
			message_put_string(msg_no, "g/L");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");
		}else if(subparameter == 12){
			message_put_string(msg_no, "A/C");
			message_put_string(msg_no, "mg/gCr");
			message_put_string(msg_no, "mg/gCr");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");
		}else if(subparameter == 13){
			message_put_string(msg_no, "P/C-80");
			message_put_string(msg_no, "mg/gCr");
			message_put_string(msg_no, "mg/gCr");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");
		}else if(subparameter == 13){
			message_put_string(msg_no, "P/C-150");
			message_put_string(msg_no, "mg/gCr");
			message_put_string(msg_no, "mg/gCr");
			message_put_string(msg_no, "NORMAL");
			message_put_string(msg_no, "DILUTE");
			message_put_string(msg_no, "OVERNAME");
		}else{
			message_put_string(msg_no, "NONE");
			message_put_string(msg_no, "NONE");
			message_put_string(msg_no, "NONE");
			message_put_string(msg_no, "NONE");
			message_put_string(msg_no, "NONE");
			message_put_string(msg_no, "NONE");
		}
		for (int idx = 0; idx < 128; idx++) {
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo); 
		}
	}else if (parameter == 5){
   std::string arrayNum[6] = {"0", "1", "2", "3", "4", "5"};
    int randIndex = rand() % 6; 
    const char* rndStr = arrayNum[randIndex].c_str();
    message_put_string(msg_no, "STRIP_INFO");
     switch(subparameter){
      	case 1:    
				message_put_int(msg_no, 8);
				message_put_string(msg_no, "9UB");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				break;
		case 2:
				message_put_int(msg_no, 9);
				message_put_string(msg_no, "8UA");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
		case 3:
				message_put_int(msg_no, 10);
				message_put_string(msg_no, "8UB");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
		case 4:        
				message_put_int(msg_no, 11);
				message_put_string(msg_no, "7UA");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
		case 5:
				message_put_int(msg_no, 12);
				message_put_string(msg_no, "7UB");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
		case 6:        
				message_put_int(msg_no, 13);
				message_put_string(msg_no, "5UA");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
		case 7:        
				message_put_int(msg_no, 14);
				message_put_string(msg_no, "5UB");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
		case 8:        
				message_put_int(msg_no, 15);
				message_put_string(msg_no, "4UA");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
		case 9:       
				message_put_int(msg_no, 1);
				message_put_string(msg_no, "10EA");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
		case 10:        
				message_put_int(msg_no, 2);
				message_put_string(msg_no, "9EA");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
		case 11:        
				message_put_int(msg_no, 3);
				message_put_string(msg_no, "8EA");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
		case 12:        
				message_put_int(msg_no, 4);
				message_put_string(msg_no, "7EA");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
		case 13:       
				message_put_int(msg_no, 5);
				message_put_string(msg_no, "6EA");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
        case 14:        
				message_put_int(msg_no, 6);
				message_put_string(msg_no, "5EA");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
        case 15:        
				message_put_int(msg_no, 7);
				message_put_string(msg_no, "4EA");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
        case 16:        
				message_put_int(msg_no, 16);
				message_put_string(msg_no, "9EB");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
        case 17:        
				message_put_int(msg_no, 17);
				message_put_string(msg_no, "10PA");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
        case 18:        
				message_put_int(msg_no, 28);
				message_put_string(msg_no, "10UB");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
        case 19:        
				message_put_int(msg_no, 29);
				message_put_string(msg_no, "11UA");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
        case 20:        
				message_put_int(msg_no, 30);
				message_put_string(msg_no, "10V");     
				message_put_string(msg_no, rndStr);     
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15^");    
				message_put_string(msg_no, "0$1$2$3^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^");    
				message_put_string(msg_no, "0$1$2$3$4$5$6$7$8$9$10$11$12$13$14$15$16$17$18$19$20$21$22$23^"); 
				break;	
		default:
			break;
		}
	}else if (parameter == 6){
		message_put_string(msg_no, "HOST_COMM");
		for (int idx = 0; idx < 32; idx++) {
      if(idx == 1){
        randomo = (rand() % 4);
        String str1 = String(randomo);
        const char* str1_ptr = str1.c_str();
        message_put_string(msg_no, str1_ptr);  
      } else if(idx == 2){
        randomo = (rand() % 2);
        String str1 = String(randomo);
        const char* str1_ptr = str1.c_str();
        message_put_string(msg_no, str1_ptr);   
      } else if(idx == 6 || idx == 7){
        double random = rand() / (double)(RAND_MAX/100.0);
        random = round(random * 10.0)/10.0;
        String str1 = String(random);
        const char* str1_ptr = str1.c_str();
        message_put_string(msg_no, str1_ptr); 
      } else if(idx == 8 || idx == 9 || idx == 10 || idx == 11 || idx == 12 || idx == 13){
        double random = rand() / (double)(RAND_MAX/1000.0);
        random = round(random * 10.0)/10.0;
        String str1 = String(random);
        const char* str1_ptr = str1.c_str();
        message_put_string(msg_no, str1_ptr); 
      } else if(idx == 15){
        randomo = (rand() % 2 + 1);
        switch(randomo){
          case 0:
            message_put_string(msg_no, "Device1"); 
            break;
          case 1:
            message_put_string(msg_no, "Device2"); 
            break;
          case 2:
            message_put_string(msg_no, "Device3"); 
            break;
          default:
            message_put_string(msg_no, "Device1"); 
            break;
        }
      } else if(idx == 22){
        randomo = (rand() % 2 + 1);
        switch(randomo){
          case 0:
            message_put_string(msg_no, "79.149.238.48"); 
            break;
          case 1:
            message_put_string(msg_no, "143.0.24.250"); 
            break;
          case 2:
            message_put_string(msg_no, "192.168.001.000"); 
            break;
          default:
            message_put_string(msg_no, "192.168.001.000"); 
            break;
        }
      } else if(idx == 23){
        randomo = (rand() % 2 + 1);
        switch(randomo){
          case 0:
            message_put_string(msg_no, "204.140.190.192"); 
            break;
          case 1:
            message_put_string(msg_no, "205.136.206.226"); 
            break;
          case 2:
            message_put_string(msg_no, "240.132.78.139"); 
            break;
          default:
            message_put_string(msg_no, "240.132.78.139"); 
            break;
        }
      } else if(idx == 24){
        randomo = (rand() % 2 + 1);
        switch(randomo){
          case 0:
            message_put_string(msg_no, "102.86.208.217"); 
            break;
          case 1:
            message_put_string(msg_no, "134.23.139.10"); 
            break;
          case 2:
            message_put_string(msg_no, "23.176.15.128"); 
            break;
          default:
            message_put_string(msg_no, "23.176.15.128"); 
            break;
        }
      } else if(idx == 27){
        randomo = (rand() % 2 + 1);
        switch(randomo){
          case 0:
            message_put_string(msg_no, "25.4.232.119"); 
            break;
          case 1:
            message_put_string(msg_no, "96.19.7.215"); 
            break;
          case 2:
            message_put_string(msg_no, "152.62.177.239"); 
            break;
          default:
            message_put_string(msg_no, "152.62.177.239"); 
            break;
        }
      } else if(idx == 25 || idx == 28){
        randomo = (rand() % 65536);
        message_put_int(msg_no, randomo);
      } else if (idx == 29 || idx == 31){
        randomo = (rand() % 7);   
        String str1 = String(randomo);
        const char* str1_ptr = str1.c_str();
        message_put_string(msg_no, str1_ptr);  
      } else {
        randomo = (rand() % 2);
			  message_put_int(msg_no, randomo);     
      }           
		}
	}else if (parameter == 7){
		message_put_string(msg_no, "AUTO_OUTPUT");
		for (int idx = 0; idx < 18; idx++) {
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  
		}
	}else if (parameter == 8){
		message_put_string(msg_no, "PRINTER_SETTING");
		for (int idx = 0; idx < 13; idx++) {
      if (idx == 1){
        randomo = (rand() % 3 + 1);
        message_put_int(msg_no, randomo); 
      } else if (idx == 2 || idx == 3){
        randomo = (rand() % 9 + 1);
        message_put_int(msg_no, randomo); 
      } else if(idx == 10){
        randomo = (rand() % 2 + 1);
        switch(randomo){
          case 0:
            message_put_string(msg_no, "Bluetooth1"); 
            break;
          case 1:
            message_put_string(msg_no, "Bluetooth2"); 
            break;
          case 2:
            message_put_string(msg_no, "Bluetooth3"); 
            break;
          default:
            message_put_string(msg_no, "Bluetooth1"); 
            break;
        }     
      } else if(idx == 11){ 
        randomo = (rand() % 2 + 1);
        switch(randomo){
          case 0:
            message_put_string(msg_no, "9e:92:dc:e6:a0:d7"); 
            break;
          case 1:
            message_put_string(msg_no, "b8:d6:8b:70:29:75"); 
            break;
          case 2:
            message_put_string(msg_no, "fc:17:35:35:f2:7f"); 
            break;
          default:
            message_put_string(msg_no, "9e:92:dc:e6:a0:d7"); 
            break;
        }
      } else if(idx == 12){
        randomo = (rand() % 9999 + 1);
        message_put_int(msg_no, randomo); 
      } else {
        randomo = (rand() % 2);
        message_put_int(msg_no, randomo); 
      }	                 
		}
	}else if (parameter == 9){
		message_put_string(msg_no, "USER_SETTING");
		for (int idx = 0; idx < 36; idx++) {
			//randomo = (rand() % 801);
			randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  
		}
	}else if (parameter == 10){
		message_put_string(msg_no, "FEEDER_SETTING");
		for (int idx = 0; idx < 5; idx++) {
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  
		}
	}else if (parameter == 11){
		message_put_string(msg_no, "STRIP_REGISTRATION");
		randomo = (rand() % 801);
		//randomo = (rand() % 2);
		message_put_int(msg_no, randomo);       
	}else if (parameter == 12){
		message_put_string(msg_no, "REAGENT_CODE_HYT");
		for (int idx = 0; idx < 7; idx++) {
		 	if ((idx == 3)||(idx == 5) || (idx == 6)){
				message_put_string(msg_no,"2223-01-01 11:11:11"); //
				continue;
			}
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  
		}
	}else if (parameter == 13){
		message_put_string(msg_no, "ERROR_TROUBLE_HYT");
		for (int idx = 0; idx < 6; idx++) {
			if (idx == 3){
				message_put_string(msg_no,"2223-01-01 11:11:11"); //
				continue;
			}
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  
		}
	}else if (parameter == 14){
		message_put_string(msg_no, "OPERATION_HYT");
		for (int idx = 0; idx < 4; idx++) {
			if (idx == 1){
				message_put_string(msg_no,"2223-01-01 11:11:11"); //
				continue;
			}
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  
		}
	}else if (parameter == 15){
		message_put_string(msg_no, "MAINTENANCE_HYT");
		for (int idx = 0; idx < 7; idx++) {
			if ((idx == 1)||(idx == 2)){
				message_put_string(msg_no,"2223-01-01 11:11:11"); //
				continue;
			}
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  
		}
	}else if (parameter == 16){
		message_put_string(msg_no, "COUNTER");
		for (int idx = 0; idx < 16; idx++) {
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  
		}
	}else if (parameter == 17){
		message_put_string(msg_no, "SG_INF");
		for (int idx = 0; idx < 17; idx++) {
    	if (idx == 2){
				message_put_string(msg_no,"2223-01-01 11:11:11"); //
				continue;
			}
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  
		}
	}else if (parameter == 18){
		message_put_string(msg_no, "TURB_INF");
		for (int idx = 0; idx < 12; idx++) {
			  if(idx == 2) {
				message_put_string(msg_no,"2222-22-22 11:11:11");
			  } else {
					randomo = (rand() % 801);
					//randomo = (rand() % 2);
					message_put_int(msg_no, randomo);                  
				}
		}
	}else if (parameter == 19){
		message_put_string(msg_no, "HB_INF");
		for (int idx = 0; idx < 4; idx++) {
			if (idx == 0){
				message_put_string(msg_no,"2223-01-01 11:11:11"); //
				continue;
			}
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  
		}
	}else if (parameter == 20){
		message_put_string(msg_no, "COLOR_INF");
		for (int idx = 0; idx < 49; idx++) {
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  
		}
	}else if (parameter == 21){
			// message_put_string(msg_no, "TEMP_CORR");
			// message_send(msg_no);
			if(delInit == 1){
				message_set_opcode(msg_no, MESSAGE_OPCODE_GET_PARAM_INITIALIZING);
			}else{
				message_set_opcode(msg_no, MESSAGE_OPCODE_GET_PARAM_READING);
			}
			message_set_ctrl(msg_no, MESSAGE_ACK);
			message_clear_data(msg_no);
			for(int count = 1; count < 56; count++){
				delay(250);
				switch(count){
				case 1:
					message_put_string(msg_no, "TEMP_CORR");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;
				case 2:
					message_put_string(msg_no, "REF_OVER_VAL");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 3:
					message_put_string(msg_no, "ABN_COLOR");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 4:
					message_put_string(msg_no, "RANK_FORM");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 5:
					message_put_string(msg_no, "ABN_MARK_LEVEL");
          randomo = (rand() % 2+1);
          message_put_int(msg_no, randomo); 
					break;	
				case 6:
					message_put_string(msg_no, "DROP_MISS_DATA");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 7:
					message_put_string(msg_no, "AD_RESULT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 8:
					message_put_string(msg_no, "CHECK_RESULT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 9:
					message_put_string(msg_no, "SG_ABN_MARK_LEVEL");
          randomo = (rand() % 6);
          message_put_int(msg_no, randomo); 
					break;	
				case 10:
					message_put_string(msg_no, "TURB_ABN_MARK_LEVEL");
          randomo = (rand() % 6);
          message_put_int(msg_no, randomo); 
					break;	
				case 11:
					message_put_string(msg_no, "BIL_FP_DETECT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 12:
					message_put_string(msg_no, "BIL_FP_VAL");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 13:
					message_put_string(msg_no, "PRO_CRE_CORR");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 14:
					message_put_string(msg_no, "COLOR_BGV");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 15:
					message_put_string(msg_no, "SG_MEAS_RANGE_MARK");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 16:
					message_put_string(msg_no, "WASH_SOL_SENS");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 17:
					message_put_string(msg_no, "SAMPLER_SIM");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 18:
					message_put_string(msg_no, "SAPL_TRBL_DETECT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;
				case 19:
					message_put_string(msg_no, "ADD_WAS");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 20:
					message_put_string(msg_no, "SG_METER");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 21:
					message_put_string(msg_no, "TB_CL_TRBL_DETECT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 22:
					message_put_string(msg_no, "STRIP_TYPE_DETECT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 23:
					message_put_string(msg_no, "DROP_MISS_DETECT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 24:
					message_put_string(msg_no, "STRIP_STRIKE-SLIP_DETECT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 25:
					message_put_string(msg_no, "STRIP_BOX_FULL_DETECT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 26:
					message_put_string(msg_no, "STRIP_BOX_TRAY_DETECT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 27:
					message_put_string(msg_no, "PATOLIGHT_ON");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 28:
					message_put_string(msg_no, "REAGENT_CODE_DETECT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 29:
					message_put_string(msg_no, "AUX_COMPATI_MODE1");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 30:
					message_put_string(msg_no, "SAME_BARCODE_DETECT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 31:
					message_put_string(msg_no, "NEW_PC_RANK");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 32:
					message_put_string(msg_no, "NEW_PC_RANK_INFO");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 33:
					message_put_string(msg_no, "E110_JUDGE_TYPE");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 34:
					message_put_string(msg_no, "AX4080_SPEC");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 35:
					message_put_string(msg_no, "CAL_CURVE_RANK_TYPE");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 36:
					message_put_string(msg_no, "SERIAL_NO");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 37:
					message_put_string(msg_no, "CTRL_RACK_COUNT");
          message_put_int(msg_no, randomo); 
					break;	
				case 38:
					message_put_string(msg_no, "TUBE_TYPE");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 39:
					message_put_string(msg_no, "SAMPLER_MODE");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 40:
					message_put_string(msg_no, "LOWER_WAIT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 41:
					message_put_string(msg_no, "TOYOBO_CONNECT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 42:
					message_put_string(msg_no, "UD-9440_CONNECT");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 43:
					message_put_string(msg_no, "REF_OVER_DATA");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 44:
					message_put_string(msg_no, "RACK_FUNCTION");
          randomo = (rand() % 5);
          message_put_int(msg_no, randomo); 
          continue;
					break;	
				case 45:
					message_put_string(msg_no, "SPANISH_MODE");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 46:
					message_put_string(msg_no, "DROP_VOL_ADJ");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 47:
					message_put_string(msg_no, "REMOTE_MODE");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 48:
					message_put_string(msg_no, "ETHER_IP");
          message_put_string(msg_no, "145.135.5.242"); 
					break;	
				case 49:
					message_put_string(msg_no, "ETHER_SUBNET");
          message_put_string(msg_no, "245.203.158.34"); 
					break;	
				case 50:
					message_put_string(msg_no, "ETHER_GATEWAY");
          message_put_string(msg_no, "186.26.102.3"); 
					break;	
				case 51:
					message_put_string(msg_no, "REMOTE_IP");
          message_put_string(msg_no, "173.130.100.236"); 
					break;	
				case 52:
					message_put_string(msg_no, "REMOTE_PORT");
          message_put_string(msg_no, "23148"); 
					break;	
				case 53:
					message_put_string(msg_no, "DRAG_DISP");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 54:
					message_put_string(msg_no, "ERROR_DISP");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				case 55:
					message_put_string(msg_no, "STAT_SEL");
          randomo = (rand() % 2);
          message_put_int(msg_no, randomo); 
					break;	
				default:
					break;
				}
			}// for
	
	}else if (parameter == 22){
		message_put_string(msg_no, "BCR_SETTING");
		for (int idx = 0; idx < 10; idx++) {
			if(idx == 0){
        randomo = (rand() % 2 + 1);
        message_put_int(msg_no, randomo);    
      } else if (idx == 1 || idx == 2 || idx == 5 || idx == 6){
        randomo = (rand() % 18 + 1);
        String str1 = String(randomo);
        const char* str1_ptr = str1.c_str();
        message_put_string(msg_no, str1_ptr);  
      } else if(idx == 3){
        randomo = (rand() % 2 + 1);
        message_put_int(msg_no, randomo);     
      } else if(idx == 4){
        randomo = (rand() % 2);
        message_put_int(msg_no, randomo);    
      } else{
        randomo = (rand() % 2 + 1);  
        switch(randomo){
          case 0:
            message_put_string(msg_no, "Sample"); 
            break;
          case 1:
            message_put_string(msg_no, "Sample Control"); 
            break;
          case 2:
            message_put_string(msg_no, "ID Sample"); 
            break;
          default:
            message_put_string(msg_no, "Sample ID"); 
            break;
        }         
      }
    }
	} else if (parameter == 23){
		message_put_string(msg_no, "MECH_ADJUST_SETTING");
		for (int idx = 0; idx < 63; idx++) {
			randomo = (rand() % 200 + 50);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);       
		}
	} else if (parameter == 24){
		message_put_string(msg_no, "QCFILE_SEL");
		for (int idx = 0; idx < 3; idx++) {
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);
		}
	}else{
		Serial.println("menu_send_again");
		message_set_opcode(msg_no, MESSAGE_OPCODE_GET_PARAM_READING);
		message_set_ctrl(msg_no, MESSAGE_ACK);
		message_clear_data(msg_no);

		for (int idx = 0; idx < 5; idx++) {
			randomo = (rand() % 801);
			//randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                //status
		}
	}
}

void dummy_measinfo(int msg_no, int statuscount, int prio) {
  message_set_opcode(msg_no, MESSAGE_OPCODE_MEASINFO_NTC);
  message_set_ctrl(msg_no, MESSAGE_ENQ);
  message_clear_data(msg_no);
  char curstat[25] = "1";
  char priority[25] = "R";
 // random number generator
  
  if (prio == 1){
	  strcpy(priority, "M");
  }else if (prio == 2){
	  strcpy(priority, "S");

  }else if (prio == 3){
	  strcpy(priority, "QC");
  }else{
	  // Do Nothing
  }

  for (int idx = 1; idx <= 9; idx++) {
  
    if ((statuscount == 0)&&(idx<2)){
        strcpy(curstat, "3");
    }else if ((statuscount == 1) && (idx<3)) {
        strcpy(curstat, "3");
    }else if ((statuscount == 2) && (idx < 4)) {
        strcpy(curstat, "3");
    } else if ((statuscount == 3) && (idx < 5)) {
        strcpy(curstat, "3");
    } else  if ((statuscount == 4) && (idx < 6)) {
        strcpy(curstat, "3");
    } else if ((statuscount == 5) && (idx < 7)) {
        strcpy(curstat, "3");
    } else if((statuscount == 6) && (idx < 8)) {
        strcpy(curstat, "3");
    } else if ((statuscount == 7) && (idx < 9)) {
        strcpy(curstat, "3");
    } else if ((statuscount == 8) && (idx <  10)) {
        strcpy(curstat, "3");
    }
    else {
        strcpy(curstat, "1");
    }

    message_put_string(msg_no, curstat);                  //status
    message_put_string(msg_no, priority);                  // Priority Type,
    message_put_int(msg_no, statuscount);                  // Measurement Number,
   // message_put_int(msg_no, "poljok5845221");			   //barcode : '1322655845221',
	message_put_string(msg_no, "1322655845221");			   //barcode : '1322655845221',
    message_put_int(msg_no, statuscount);                  //rackNumber : 1,
    message_put_int(msg_no, statuscount);                  //testTubePosition : 1,
    message_put_int(msg_no, statuscount);                  //rackId : 1,
  }

}

void dummy_barcode(int msg_no) {
    message_set_opcode(msg_no, MESSAGE_OPCODE_MEASINFO_NTC);
    message_set_ctrl(msg_no, MESSAGE_ENQ);
    message_clear_data(msg_no);
    for (int idx = 1; idx <= 9; idx++) {
        message_put_string(msg_no, "1");                  //status
        message_put_string(msg_no, "1");                  // Priority Type,
        message_put_string(msg_no, "1");                  // Measurement Number,
        message_put_string(msg_no, "poljok5845221");      //barcode : '1322655845221',
        message_put_string(msg_no, "1");                  //rackNumber : 1,
        message_put_string(msg_no, "1");                  //testTubePosition : 1,
        message_put_string(msg_no, "1");                  //rackId : 1,
    }
}

void dummy_menumode(int msg_no) {
	message_set_opcode(msg_no, MESSAGE_OPCODE_MENU_OP);
    message_set_ctrl(msg_no, MESSAGE_ACK);
    message_clear_data(msg_no);
}

void dummy_menumode_cont(int msg_no, int menumode, int parameters, int result) {
	int randomo;
	menu_mode_t local_menu = get_menu_mode();

	if (menumode == 0){
		Serial.println("menu_send_again");
		message_set_opcode(msg_no, MESSAGE_OPCODE_MENU_OP);
		message_set_ctrl(msg_no, MESSAGE_ENQ);
		message_clear_data(msg_no);

		message_put_int(msg_no, menumode); //Reference
		message_put_int(msg_no, 1); //
		message_put_int(msg_no, result);
		message_put_string(msg_no,"2023-01-01 11:11:11"); //
		message_put_string(msg_no, local_menu.returndata.data1);
		message_put_string(msg_no, local_menu.returndata.data2);
		randomo = (rand() % 801);
		message_put_int(msg_no, randomo);  
		randomo = (rand() % 801);
		message_put_int(msg_no, randomo);  
		randomo = (rand() % 801);
		message_put_int(msg_no, randomo);  
		randomo = (rand() % 801);
		message_put_int(msg_no, randomo);  
		randomo = (rand() % 801);
		message_put_int(msg_no, randomo);  
	}else if (menumode == 3){
		Serial.println("menu_send_again");
		message_set_opcode(msg_no, MESSAGE_OPCODE_MENU_OP);
		message_set_ctrl(msg_no, MESSAGE_ENQ);
		message_clear_data(msg_no);

		message_put_int(msg_no, menumode); //Reference
		message_put_int(msg_no, 1); //
		message_put_int(msg_no, result);
		message_put_string(msg_no,"2023-01-01 11:11:11"); //
		message_put_string(msg_no, local_menu.returndata.data1);
		randomo = (rand() % 801);
		message_put_int(msg_no, randomo);  
	}else if (menumode == 4){
		Serial.println("menu_send_again");
		message_set_opcode(msg_no, MESSAGE_OPCODE_MENU_OP);
		message_set_ctrl(msg_no, MESSAGE_ENQ);
		message_clear_data(msg_no);

		message_put_int(msg_no, menumode); //Reference
		message_put_int(msg_no, 1); //
		message_put_int(msg_no, result);
		message_put_string(msg_no,"2023-01-01 11:11:11"); //
		message_put_string(msg_no, local_menu.returndata.data1);
		randomo = (rand() % 801);
		message_put_int(msg_no, randomo);    
	}else if(menumode == 25){
		Serial.println("menu_send_again_25");
		message_set_opcode(msg_no, MESSAGE_OPCODE_ADJ_INFO);
		message_set_ctrl(msg_no, MESSAGE_ENQ);
		message_clear_data(msg_no);

		message_put_string(msg_no, "ADJUST_INFO");
		message_put_int(msg_no, menumode); //Reference
		message_put_int(msg_no, 0);
		message_put_int(msg_no, 4);
		for (int idx = 1; idx <= 7; idx++) {
			//randomo = (rand() % 801);
			randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  //status
		}
	}else if(menumode == 26){
		Serial.println("menu_send_again_26");
		message_set_opcode(msg_no, MESSAGE_OPCODE_CHK_RESULT);
		message_set_ctrl(msg_no, MESSAGE_ENQ);
		message_clear_data(msg_no);

		randomo = (rand() % 801);
		message_put_int(msg_no, randomo); //Reference
		message_put_string(msg_no, param_get_serial_no()); //Serial No.
		message_put_string(msg_no,"AnalyzerSystem"); //

		randomo = (rand() % 801);
		message_put_int(msg_no, randomo);   //

		message_put_string(msg_no,"2223-01-01 11:11:11"); //
		message_put_string(msg_no,"88.8"); 

		message_put_int(msg_no, 6207);
		message_put_int(msg_no, local_menu.testno);

		// Wavelength
		for (int idx = 1; idx <= 5; idx++) {
			randomo = (rand() % 2);
			message_put_int(msg_no, randomo);       
			for (int idx2 = 1; idx2 <= 10; idx2++) {
				if (idx2 == 2){
					message_put_string(msg_no,"999.9$888.8$777.7$665.6$555.5$444.4$333.3$222.2$111.1$999.9$888.8$777.7$665.6$555.5$444.4$333.3^");
				}else if((idx2 == 3)||(idx2 == 4)){
					message_put_string(msg_no,"999$888$777$665$555$444$333$222$111$999$888$777$665$555$444$333^");
				}else{
					randomo = (rand() % 801);
					message_put_int(msg_no, randomo);                  //status
				}
			}
		}
		for (int idx3 = 1; idx3 <= 5; idx3++) {
			randomo = (rand() % 2);
			message_put_int(msg_no, randomo);       
			for (int idx4 = 1; idx4 <= 10; idx4++) {
				randomo = (rand() % 801);
				message_put_int(msg_no, randomo);                  //status
			}
		}
		message_put_string(msg_no," ");
		message_put_string(msg_no," ");
		message_put_string(msg_no," ");
		randomo = (rand() % 801);
		message_put_int(msg_no, randomo);
	}else{
		Serial.println("menu_send_again");
		message_set_opcode(msg_no, MESSAGE_OPCODE_MENU_OP);
		message_set_ctrl(msg_no, MESSAGE_ENQ);
		message_clear_data(msg_no);

		message_put_int(msg_no, menumode); //Reference
		message_put_int(msg_no, 1); //
		message_put_int(msg_no, result); 
		parameters -= 3;
		for (int idx = 1; idx <= parameters; idx++){
			//randomo = (rand() % 801);
			randomo = (rand() % 2);
			message_put_int(msg_no, randomo);                  //status
		}
	}
}

void dummy_menuadj(int msg_no) {
	Serial.println("menu_adj_receive");
    message_set_opcode(msg_no, MESSAGE_OPCODE_MENU_OP);
    message_set_ctrl(msg_no, MESSAGE_ACK);
    message_clear_data(msg_no);
    //message_send(1);
}

void dummy_menuadj_cont(int msg_no, int menumode, int step, int testno) {
	
	menu_mode_t local_menu = get_menu_mode();
	all_adj_t local_adj = get_adj_all();
	
    Serial.println("menu_send_again_adj");
    message_set_opcode(msg_no, MESSAGE_OPCODE_MENU_OP);
    message_set_ctrl(msg_no, MESSAGE_ENQ, true);
    message_clear_data(msg_no);

	//if ((step == 0)||(step == 2)){
	if ((step == 0)||(step == 2)){
		if (menumode == 5){
			message_put_int(msg_no, menumode); //Reference
			message_put_int(msg_no, step);     //status
			message_put_int(msg_no, testno);   //status
			message_put_string(msg_no, local_adj.pulse_adj.read_defaultpls);
			message_put_string(msg_no, local_adj.pulse_adj.read_currentpls);
			set_adj_all(local_adj);

		}else if (menumode == 6){
			local_menu.testno = testno;
			local_menu.menumode = menumode;
			set_menu_mode(local_menu);
			message_put_int(msg_no, menumode); //Reference
			message_put_int(msg_no, step);                  //status
			message_put_int(msg_no, testno);                  //status
			message_put_string(msg_no, local_adj.intro_adj.read_defaultpls);
			message_put_string(msg_no, local_adj.intro_adj.read_currentpls);
			message_put_string(msg_no, local_adj.intro_adj.read_front_defaultpls);
			message_put_string(msg_no, local_adj.intro_adj.read_front_currentpls);
			message_put_string(msg_no, local_adj.intro_adj.read_delvry_defaultpls);
			message_put_string(msg_no, local_adj.intro_adj.read_delvry_currentpls);
			set_adj_all(local_adj);
		}
	}

	if ((step == 4)&&(testno == 0)){
		if (menumode == 5){
			message_put_int(msg_no, menumode); //Reference
			message_put_int(msg_no, 5);                  //status
			message_put_string(msg_no, "1");                  //status
			message_put_string(msg_no, local_adj.pulse_adj.read_defaultpls);
			message_put_string(msg_no, local_adj.pulse_adj.read_currentpls);
			set_adj_all(local_adj);

		}else if (menumode == 6){
			message_put_int(msg_no, menumode); //Reference
			message_put_int(msg_no, step);                  //status
			message_put_int(msg_no, testno);                  //status
			message_put_string(msg_no, local_adj.intro_adj.read_defaultpls);
			message_put_string(msg_no, local_adj.intro_adj.read_currentpls);
			message_put_string(msg_no, local_adj.intro_adj.read_front_defaultpls);
			message_put_string(msg_no, local_adj.intro_adj.read_front_currentpls);
			message_put_string(msg_no, local_adj.intro_adj.read_delvry_defaultpls);
			message_put_string(msg_no, local_adj.intro_adj.read_delvry_currentpls);
			set_adj_all(local_adj);
		}

	}else if ((step == 4)&&(testno == 1)){
		common_adj_t local_common_adj = get_adj_common();
		if (menumode == 5){
			strcpy(local_adj.pulse_adj.read_defaultpls, local_common_adj.read_defaultpls);
			strcpy(local_adj.pulse_adj.read_currentpls, local_common_adj.read_currentpls);

			message_put_int(msg_no, menumode); //Reference
			message_put_int(msg_no, step);                  //status
			message_put_int(msg_no, testno);                  //status
			message_put_string(msg_no, local_adj.pulse_adj.read_defaultpls);
			message_put_string(msg_no, local_adj.pulse_adj.read_currentpls);
			set_adj_all(local_adj);

		}else if (menumode == 6){
			if (local_menu.testno == 0){
				strcpy(local_adj.intro_adj.read_currentpls, local_common_adj.read_currentpls);
				Serial.println("0");
			}
			if (local_menu.testno == 1){
				strcpy(local_adj.intro_adj.read_front_currentpls,local_common_adj.read_currentpls);
				Serial.println("1");
			}
			if (local_menu.testno == 2){
				strcpy(local_adj.intro_adj.read_delvry_currentpls, local_common_adj.read_currentpls);
				Serial.println("2");
			}

			message_put_int(msg_no, menumode); //Reference
			message_put_int(msg_no, step);                  //status
			message_put_int(msg_no, testno);                  //status
			message_put_string(msg_no, local_adj.intro_adj.read_defaultpls);
			message_put_string(msg_no, local_adj.intro_adj.read_currentpls);
			message_put_string(msg_no, local_adj.intro_adj.read_front_defaultpls);
			message_put_string(msg_no, local_adj.intro_adj.read_front_currentpls);
			message_put_string(msg_no, local_adj.intro_adj.read_delvry_defaultpls);
			message_put_string(msg_no, local_adj.intro_adj.read_delvry_currentpls);
			set_adj_all(local_adj);
		}
	}
}

void dummy_adjust(int msg_no) {
    message_set_opcode(msg_no, MESSAGE_OPCODE_ADJ_OP);
    message_set_ctrl(msg_no, MESSAGE_ACK);
    message_clear_data(msg_no);

}

void dummy_adjust_cont(int msg_no) {
	menu_mode_t local_menu = get_menu_mode();
	common_adj_t local_adj = get_adj_common();

    message_set_opcode(msg_no, MESSAGE_OPCODE_ADJ_OP);
    message_set_ctrl(msg_no, MESSAGE_ENQ);
    message_clear_data(msg_no);

	message_put_string(msg_no, local_adj.read_fieldlabel); 
	message_put_string(msg_no, local_adj.read_direction);	
	message_put_string(msg_no, local_adj.read_pls); 
	message_put_string(msg_no, local_adj.read_defaultpls);
	message_put_string(msg_no, local_adj.read_currentpls);
}

void dummy_shutdown_cont(int msg_no, int result) {
	message_set_opcode(msg_no, MESSAGE_OPCODE_SHUTDOWN);
	message_set_ctrl(msg_no, MESSAGE_ACK);
	message_clear_data(msg_no);

	message_put_string(msg_no, "KEY_STUTDOWN"); //Reference
	message_put_int(msg_no, result);
}

void dummy_tip_case(int msg_no) {
  message_set_opcode(msg_no, MESSAGE_OPCODE_TIPCASE_NTC);
  message_set_ctrl(msg_no, MESSAGE_ENQ);
  message_clear_data(msg_no);
  message_put_int(msg_no, 1); //Reference
  message_put_int(msg_no, 1); //Sample
  message_put_int(msg_no, 1); //Tip 1
  message_put_int(msg_no, 1); //Tip 2
  message_put_int(msg_no, 1); //Tip 3
  message_put_int(msg_no, 1); //Tip 4
  message_put_int(msg_no, 1); //CF Cuvette
}

void dummy_systemlog(int msg_no) {
    message_set_opcode(msg_no, MESSAGE_OPCODE_SYSTEMLOG_NTC);
    message_set_ctrl(msg_no, MESSAGE_ENQ);
    message_clear_data(msg_no);
    message_put_string(msg_no, "1");
    message_put_string(msg_no, "1");
    for (int idx = 1; idx <= 64; idx++) {;
        message_put_string(msg_no, "poljok5845221"); 
        message_put_string(msg_no, "1");                  
        message_put_string(msg_no, "1");                  
        message_put_string(msg_no, "1");                  
        message_put_string(msg_no, "1");                  
        message_put_string(msg_no, "1");                  
        message_put_string(msg_no, "1");                  
        message_put_string(msg_no, "1");                  
        message_put_string(msg_no, "1");                  
    }
}

void dummy_error_code(int msg_no) {
    int randomo;
	error_code_t error_code = get_error_code();
    Serial.println("Error Notice Send");
    message_set_opcode(msg_no, MESSAGE_OPCODE_ERROR_NTC);
    message_set_ctrl(msg_no, MESSAGE_ENQ);
    message_clear_data(msg_no);
    message_put_string(msg_no, error_code.error_PopUp_number); //Reference
    for (int idx = 1; idx <= 4; idx++) {
		 randomo = (rand() % 801);
		 message_put_int(msg_no, randomo);                   //status
    }
}