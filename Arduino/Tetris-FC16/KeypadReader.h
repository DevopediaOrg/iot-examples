#ifndef KeypadReader_h
#define KeypadReader_h

#include "CmdReader.h"

class KeypadReader : public CmdReader {
  public:
    void setPins(int lft, int rgt, int dwn, int rot);
    static String read(void);

  private:
    static int _lft, _rgt, _dwn, _rot;
    volatile static String _cmd;

    static void _read(void);
};

#endif
