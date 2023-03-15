#include "constants.h"
#include "prototypes.h"

int di_cur_field = 0;
int di_empty_line = 0;

void data_input(int state_no, int msg_no, complete_cb_t on_complete, error_cb_t on_error) {
  di_cur_field = 1;
  di_empty_line = 0;
  Serial.println("Data input");
  Serial.println("Enter an empty line twice to confirm");
  Serial.print("Field ");
  Serial.print(di_cur_field);
  Serial.print(": "); 
  read_input(
  state_no,
  [msg_no, on_complete] (const char* buffer, int len) {
    if (len == 0) {
      di_empty_line++;
      if (di_empty_line == 2) {
        Serial.println("(end)");
        on_complete();
      }
      return;
    }
    di_empty_line = 0;
    Serial.write(buffer, len);
    Serial.println();
    Serial.print("Field ");
    Serial.print(++di_cur_field);
    Serial.print(": "); 
    message_put_data(msg_no, buffer, len);
  }, on_error);
}
