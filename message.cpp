#include "constants.h"
#include "prototypes.h"

#define MESSAGE_DATA_LEN 10000
#define MESSAGE_COUNT 3

#define DELIMITER 0x1F
#define END_OF_LINE 0x1E
#define CR 0x0D

struct message_t {
  char opcode;
  char delim0;
  char control;
  char datanum;
  char delim1;
  char delim2;
  char data[MESSAGE_DATA_LEN];

  bool get_has_data() {
    return data[0] != 0;
  }

  int get_total_len() {
    return strlen(data) + 5;
  }
};

message_t messages[MESSAGE_COUNT];
char *data_ptr[MESSAGE_COUNT];
//char **recieve;

void message_init() {
  for (int idx = 0; idx < MESSAGE_COUNT; idx++) {
    message_t *msg = &messages[idx];
    data_ptr[idx] = msg->data;
  }
}

void message_deinit() {
}

void message_set_opcode(int msg_no, int opcode) {
  message_t *msg = &messages[msg_no];
  msg->opcode = opcode;
  msg->delim0 = DELIMITER;
}

void message_set_ctrl(int msg_no, int control, bool put_eol) {
  message_t *msg = &messages[msg_no];
  msg->control = control;
  if (put_eol) {
	msg->delim1 = CR;
    msg->delim2 = END_OF_LINE;
  }
}

void message_put_data(int msg_no, const char *data, int len) {
  char *ptr = data_ptr[msg_no];
  *(ptr - 1) = DELIMITER; //Note: will overflow to delim1 on first data (intended)
  memcpy(ptr, data, len);
  ptr += len;
  *ptr++ = CR;
  *ptr++ = END_OF_LINE;
  *ptr = 0;
  data_ptr[msg_no] = ptr;
}

void message_put_string(int msg_no, const char *str) {
  int len = strlen(str);
  message_put_data(msg_no, str, len);
}

void message_put_int(int msg_no, int value) {
  char buffer[32];
  int len = sprintf(buffer, "%d", value);
  message_put_data(msg_no, buffer, len);
}

void message_put_float(int msg_no, float value) {
  char buffer[32];
  int len = sprintf(buffer, "%f", value);
  message_put_data(msg_no, buffer, len);
}

int message_get_opcode(int msg_no) {
  message_t *msg = &messages[msg_no];
  return msg->opcode;
}

int message_get_ctrl(int msg_no) {
  message_t *msg = &messages[msg_no];
  return msg->control;
}

message_read_status_t message_read_data(int msg_no, char *buffer) {
  char *ptr = data_ptr[msg_no];
  if (*ptr == 0) {
    return MESSAGE_ERR_READ_NO_DATA;
  }
  while (*ptr != DELIMITER && *ptr != END_OF_LINE && *ptr != CR) {
    if (*ptr == 0) { //TODO: resume even null char is received?
      return MESSAGE_ERR_READ_UNEXPECTED_EOM;
    }
    *buffer++ = *ptr++;
  }
  int len = ptr - data_ptr[msg_no];
  data_ptr[msg_no] = ptr + 4; //+1 because of the 2 delimiter and eol and CR
  return len;
}

message_read_status_t message_read_string(int msg_no, char *buffer) {
  message_read_status_t result = message_read_data(msg_no, buffer);
  if (MESSAGE_READ_SUCCESS(result)) {
    int len = result;
    buffer[len] = 0;
  }
  return result;
}

message_read_status_t message_read_int(int msg_no, int *i_buffer) {
  char buffer[32];
  message_read_status_t result = message_read_string(msg_no, buffer);
  if (MESSAGE_READ_SUCCESS(result)) {
    int sscanf_result = sscanf(buffer, "%d", i_buffer);
    if (sscanf_result != 1) {
      return MESSAGE_ERR_READ_INVALID_FORM;
    }
  }
  return result;
}

message_read_status_t message_read_float(int msg_no, float *f_buffer) {
  char buffer[32];
  message_read_status_t result = message_read_string(msg_no, buffer);
  if (MESSAGE_READ_SUCCESS(result)) {
    int sscanf_result = sscanf(buffer, "%f", f_buffer);
    if (sscanf_result != 1) {
      return MESSAGE_ERR_READ_INVALID_FORM;
    }
  }
  return result;
}

void message_clear_data(int msg_no) {
  message_t *msg = &messages[msg_no];
  msg->delim1 = CR;
  msg->delim2 = END_OF_LINE;
  //TODO: Choose better method to clear data
  msg->data[0] = 0; //Fast but unsafe
  memset(msg->data, 0, sizeof(msg->data)); //Slow but safe
  data_ptr[msg_no] = msg->data;
}

void message_reset_data(int msg_no) {
  message_t *msg = &messages[msg_no];
  data_ptr[msg_no] = msg->data;
}

const char* message_get_raw_data_ptr(int msg_no) {
  message_t *msg = &messages[msg_no];
  return msg->data;
}

void message_copy(int msg_src_no, int msg_dst_no) {
  message_t *src = &messages[msg_src_no];
  message_t *dst = &messages[msg_dst_no];
  memcpy(dst, src, sizeof(message_t));
}

bool message_send(int msg_no) {
  auto server_client = server_get_client();
  message_t *msg = &messages[msg_no];
  int len = msg->get_total_len();
  msg->datanum = len;
  char *buffer = (char*)msg;
  if (server_client) {
    server_client->write(buffer, len);
    Serial.print("<< ");
    message_print(msg_no);
    return true;
  }
  return false;
}

bool message_recv(int msg_no) {
  auto server_client = server_get_client();
  if (!server_client) {
    return false;
  }
  message_t *msg = &messages[msg_no];
  char *buffer = (char*)msg;
  int len = 0;
  while (true) {
    int c = server_client->read();
    if (c >= 0) {
      buffer[len++] = (char)c;
      if (c == END_OF_LINE) {
        break;
      }
    } else {
      return false;
    }
    if (len % 1000 == 0) {
      yield();
    }
  }
  buffer[len] = 0;
  data_ptr[msg_no] = msg->data;
  Serial.print(">> ");
  message_print(msg_no);
  return true;
}

void message_recv_async(int state_no, int msg_no, message_recv_cb_t on_recv) {
  set_state(
    [msg_no, on_recv] () {
      if (message_recv(msg_no)) {
        on_recv();
      }
    }, state_no);
}

char print_field_buffer[1000];

void message_print(int msg_no) {
  message_t *msg = &messages[msg_no];
  Serial.print("#");
  Serial.print(msg_no);
  Serial.print(" (");
  Serial.print((int)msg->opcode, HEX);
  Serial.print(") ");
  switch (msg->control) {
    case MESSAGE_ENQ:
    Serial.println("Request");
    break;
    case MESSAGE_ACK:
    Serial.println("Ack");
    break;
    case MESSAGE_NAK:
    Serial.println("Nak");
    break;
    default:
    Serial.print("Unknown (");
    Serial.print((int)msg->control, HEX);
    Serial.println(")");
    break;
  }
  int field_no = 1;
  // WARNING: Not thread safe
  char *saved_data_ptr = data_ptr[msg_no];
  message_reset_data(msg_no);
  while (true) {
    if (MESSAGE_READ_SUCCESS(message_read_string(msg_no, print_field_buffer))) {
      Serial.print("\t");
      Serial.print(field_no++);
      Serial.print(": \"");
      Serial.print(print_field_buffer);
      //*recieve = print_field_buffer;
      //Serial.print(*recieve);
      //recieve++;
      Serial.println("\"");
    } else {
      break;
    }
  }
  data_ptr[msg_no] = saved_data_ptr;
}
