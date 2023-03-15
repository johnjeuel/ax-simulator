#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include <WiFi.h>
#include <ESPmDNS.h>

typedef std::function<void()> state_func_t;
typedef std::function<void()> cb_func_t;

typedef std::function<void(const char*, int)> input_cb_t;
typedef std::function<void(int)> input_int_cb_t;
typedef std::function<void(bool)> input_yesno_cb_t;

typedef std::function<void()> complete_cb_t;
typedef std::function<void()> error_cb_t;
typedef std::function<void()> empty_cb_t;

typedef std::function<void()> connect_cb_t;
typedef std::function<void()> unset_cb_t;

typedef std::function<void()> message_recv_cb_t;

typedef std::function<void()> client_lost_cb_t;


#define EMPTY_STATE_FUNC state_func_t()

struct wifi_settings_t {
  bool is_set = false;
  bool is_ap = false;
  char ssid[64];
  char psk[64];
  int tcp_port = 0;
  bool enable_mdns = true;
  char mdns_sname[64];
};

struct error_code_t {
    char error_PopUp_number[64];
};

struct return_data_t {
	char data1[10];
	char data2[10];
	char data3[10];
};

struct menu_mode_t {
    int menumode;
	int testno;
	int parameters;
	int onProcess;
	return_data_t returndata;
};

struct common_adj_t {
	char read_fieldlabel[100];
	char read_direction[100];
	char read_pls[100];
	char read_defaultpls[100];
	char read_currentpls[100];
};

typedef struct pulse_adj_t {
	char read_defaultpls[100];
	char read_currentpls[255];
};

typedef struct intro_adj_t {
	char read_defaultpls[100];
	char read_currentpls[100];
	char read_front_defaultpls[100];
	char read_front_currentpls[100];
	char read_delvry_defaultpls[100];
	char read_delvry_currentpls[100];
};

struct all_adj_t {
	pulse_adj_t pulse_adj;
	intro_adj_t intro_adj;
};


typedef int message_read_status_t;

#define MESSAGE_READ_SUCCESS(s) (s >= 0)

// ----- Server ------

void server_initialize(int);
void server_close();
void server_update();
void server_client_disconnect();

void server_attach_client_lost(client_lost_cb_t);

WiFiClient* server_get_client();

//(Implement)
//void server_client_lost();

// -------------------


// ----- State Funcs ------

void interactive_main();
void receive_mode_init();
void send_mode_init();
void sim_init();
void wifi_setup_init();
void param_edit_init();
void sim_error_popUp_forced_init();
void sim_error_popUp();
void sim_error_popUp_forced();
void sim_waitingForRack();
void sim_waitingForRack_cont();
void sim_meas_long();
void sim_meas_image();


void set_state(state_func_t, int);
void delayed_set_state(state_func_t, int, long);

// ------------------------

// ----- User Input -------

void read_input(int, input_cb_t, error_cb_t);
void read_int(int state, input_int_cb_t on_input, error_cb_t on_error, empty_cb_t on_empty = empty_cb_t());
void read_yesno(int state, input_yesno_cb_t on_input, error_cb_t on_error, empty_cb_t on_empty = empty_cb_t());

void data_input(int, int, complete_cb_t, error_cb_t);

// ------------------------

// ------ Message ---------

void message_init();
void message_deinit();
void message_set_opcode(int, int);
void message_set_ctrl(int msg_no, int ctrl, bool put_eol = true);
void message_put_data(int, const char*, int);
void message_put_string(int, const char*);
void message_put_int(int, int);
void message_put_float(int, float);
int message_get_opcode(int);
int message_get_ctrl(int);
message_read_status_t message_read_data(int, char*);
message_read_status_t message_read_string(int, char*);
message_read_status_t message_read_int(int, int*);
message_read_status_t message_read_float(int, float*);
void message_clear_data(int);
void message_reset_data(int);
const char* message_get_raw_data_ptr(int);
void message_copy(int, int);
bool message_send(int);
bool message_recv(int);
void message_recv_async(int, int, message_recv_cb_t);
void message_print(int);

// ------------------------

// -------- Wifi ----------

void set_wifi_settings(wifi_settings_t&);
wifi_settings_t& get_wifi_settings();
void wifi_connect(int state_no, connect_cb_t on_connect, error_cb_t on_error, unset_cb_t on_unset = unset_cb_t());
void wifi_disconnect();

void wifi_update();

// ------------------------

// ------ Param -----------

const char* param_get_ope_mode();
const char* param_get_device_name();
const char* param_get_serial_no();
byte param_get_led_r();
byte param_get_led_g();
byte param_get_led_b();

void param_set_defaults();
void param_set_ope_mode(const char*);
void param_set_device_name(const char*);
void param_set_serial_no(const char*);
void param_set_led_r(byte);
void param_set_led_g(byte);
void param_set_led_b(byte);

// ------------------------

// ------- Dummy ----------

void dummy_system_info(int);
void dummy_reagent_info_list(int);
void dummy_reagent_info(int, int, char*, char*);
void dummy_error_info(int);
void dummy_error_notice(int);
void dummy_param_reading(int, int , int, int, int);
void dummy_barcode(int);
void dummy_menumode(int);
void dummy_menumode_cont(int, int, int, int);
void dummy_menuadj(int);
void dummy_menuadj_cont(int,int, int, int);
void dummy_measinfo(int,int, int);
void dummy_shutdown_cont(int, int);
void dummy_tip_case(int);
void dummy_systemlog(int);
void dummy_error_code(int);
void dummy_system_version(int,int);
void dummy_adjust(int);
void dummy_adjust_cont(int);



void set_error_code(error_code_t&);
error_code_t& get_error_code();

void set_menu_mode(menu_mode_t&);
menu_mode_t& get_menu_mode();

void set_adj_common(common_adj_t&);
common_adj_t& get_adj_common();

void set_adj_all(all_adj_t&);
all_adj_t& get_adj_all();

// ------------------------

#endif // #ifndef PROTOTYPES_H_INCLUDED
