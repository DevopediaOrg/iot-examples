#ifndef DotMatrixBoard_h
#define DotMatrixBoard_h

#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Board.h"

class DotMatrixBoard : public Board {
  public:
    DotMatrixBoard(int x, int y);
    ~DotMatrixBoard(void);
    void setPins(int8_t din, int8_t cs, int8_t clk);
    void print(void);
    void testPrint(bool value);

  private:
    int8_t _din, _cs, _clk;
    int _numDevices;
    MD_MAX72XX* _mx = NULL;
};

#endif
