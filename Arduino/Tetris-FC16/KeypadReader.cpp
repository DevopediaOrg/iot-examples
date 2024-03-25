#include "Common.h"
#include "KeypadReader.h"

static int KeypadReader::_lft, KeypadReader::_rgt, KeypadReader::_dwn, KeypadReader::_rot;
volatile static String KeypadReader::_cmd;

void KeypadReader::setPins(int lft, int rgt, int dwn, int rot) {
  _lft = lft; pinMode(_lft, INPUT);
  _rgt = rgt; pinMode(_rgt, INPUT);
  _dwn = dwn; pinMode(_dwn, INPUT);
  _rot = rot; pinMode(_rot, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), _read, RISING);
}

String KeypadReader::read(void) {
  char cmd[4]; // give space for \0 char
  _cmd.getBytes(cmd, 4);
  _cmd = "";
  Serial.print("cmd: "); Serial.println(cmd);
  return String(cmd);
}

void KeypadReader::_read(void) {
  // TODO Handle multiple key presses
  if (digitalRead(_lft) == HIGH) _cmd = "lft";
  else if (digitalRead(_rgt) == HIGH) _cmd = "rgt";
  else if (digitalRead(_dwn) == HIGH) _cmd = "dwn";
  else if (digitalRead(_rot) == HIGH) _cmd = "rot";
  else _cmd = "";
}
