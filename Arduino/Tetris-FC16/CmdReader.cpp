#include "Common.h"
#include "CmdReader.h"

String CmdReader::read(void) {
  String cmd = "";
  if (Serial.available() > 0) {
    cmd = String((char)Serial.read());
    if (cmd == "j") cmd = "lft";
    else if (cmd == "l") cmd = "rgt";
    else if (cmd == "k") cmd = "dwn";
    else if (cmd == "i") cmd = "rot";
    else cmd = "";
  }
  return cmd;
}
