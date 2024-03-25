#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Common.h"
#include "DotMatrixBoard.h"

DotMatrixBoard::DotMatrixBoard(int x, int y) : Board(x, y) {
  _numDevices = x / 8; // support only factors of 8
}

DotMatrixBoard::~DotMatrixBoard(void) {
  if (_mx) delete _mx;
  _mx = NULL;
}

void DotMatrixBoard::setPins(int8_t din, int8_t cs, int8_t clk) {
  _din = din;
  _cs = cs;
  _clk = clk;
  _mx = new MD_MAX72XX(MD_MAX72XX::FC16_HW, _cs, _numDevices);
  _mx->begin();
  _mx->control(MD_MAX72XX::INTENSITY, MAX_INTENSITY/2);
}

void DotMatrixBoard::print(void) {
  _mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  for (int i = 0; i < _x; i++) {
    for (int j = 0; j < _y; j++) {
      if (i >= _tx && i < _tx+4 && j >= _ty && j < _ty+4 && _active && _active->shape[i-_tx][j-_ty]) {
        _mx->setPoint(j, i, _active->shape[i-_tx][j-_ty]);
      }
      else {
        _mx->setPoint(j, i, _b[i][j]);
      }
    }
  }
  
  _mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void DotMatrixBoard::testPrint(bool value) {
  _mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (int i = 0; i < _x; i++) {
    for (int j = 0; j < _y; j++) {
      _mx->setPoint(j, i, value);
    }
  }  
  _mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}
