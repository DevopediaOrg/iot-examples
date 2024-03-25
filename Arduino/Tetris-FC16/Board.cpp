#include "Common.h"
#include "Board.h"

Board::Board(int x, int y) {
  _x = x;
  _y = y;
  _b = _allocMem();
}

Board::~Board(void) {
  _deactivateTm();
  _freeMem(_b);
  _b = NULL;
}

void Board::updateFall(void) {
  if (_withActiveTm()) _fall();
  else _add(new Tetrimino());
  _clearFullRows();
}

void Board::processCmd(String cmd) {
  if (_withActiveTm()) {
    if (cmd == "lft") _moveLeft();
    else if (cmd == "rgt") _moveRight();
    else if (cmd == "dwn") _moveDown();
    else if (cmd == "rot") _rotate();
    _clearFullRows();
  }
}

bool Board::isGameOver(void) {
  return _gameOver;
}

void Board::print(void) {
  Serial.print("Score: "); Serial.println(_scorer.getScore());
  for (int i = 0; i < _x; i++) {
    #ifdef DEBUG
    Serial.print((long)_b[i], HEX); Serial.print(": ");
    #endif
    for (int j = 0; j < _y; j++) {
      if (i >= _tx && i < _tx+4 && j >= _ty && j < _ty+4 && _active && _active->shape[i-_tx][j-_ty]) {
        if (_b[i][j] == _active->shape[i-_tx][j-_ty]) {
          Serial.print("ERROR: board and tetrimino conflicting at position (");
          Serial.print(i); Serial.print(":"); Serial.print(j); Serial.println(")");
          while (true) { }
        }
        Serial.print(_active->shape[i-_tx][j-_ty]);
      }
      else {
        Serial.print(_b[i][j]);
      }
      Serial.print(" ");
    }
    Serial.println("");
  }
  Serial.println("");
}

bool** Board::_allocMem(void) {
  bool** m = new bool*[_x];
  for (int i = 0; i < _x; i++) {
    m[i] = new bool[_y];
  }
  for (int i = 0; i < _x; i++) {
    for (int j = 0; j < _y; j++) {
      m[i][j] = false;
    }
  }
  return m;
}

void Board::_freeMem(bool **m) {
  for (int i = 0; i < _x; i++) delete m[i];
  delete m;
}

void Board::_clearFullRows(void) {
  // Clear full rows but don't collapse
  for (int i = 0; i < _x; i++) {
    bool toClear = true;
    for (int j = 0; j < _y; j++) {
      if (!_b[i][j]) {
        toClear = false;
        break;
      }
    }
    if (toClear) {
      delete _b[i];
      _b[i] = NULL;
    }
  }

  #ifdef DEBUG
  Serial.print("Rows to clear: ");
  for (int i = 0; i < _x; i++) {
    if(_b[i] == NULL) {
      Serial.print(i); Serial.print(" ");
    }
  }
  Serial.println("");
  #endif

  // Collapse rows from the lowest row by moving the row pointers
  int src_i = _x - 1, dst_i = _x - 1;
  while (src_i >= 0) {
    if (_b[src_i] == NULL) {
      src_i--;
    }
    else if (src_i != dst_i) {
      _b[dst_i] = _b[src_i];
      src_i--;
      dst_i--;
    }
    else {
      src_i--;
      dst_i--;
    }
  }

  _scorer.scoreRows(dst_i - src_i);

  // Init fresh rows at the top
  while (dst_i >= 0) {
    _b[dst_i] = new bool[_y];
    for (int j = 0; j < _y; j++) {
      _b[dst_i][j] = false;
    }
    dst_i--;
  }
}

void Board::_add(Tetrimino* tm) {
  _active = tm;
  _tx = 0;
  _ty = random(0, _y - tm->width() + 1);
  if (_isValidMove()) {
    _moveTm();
    _scorer.scoreNewTetrimino();
  }
  else {
    _gameOver = true;
    _deactivateTm();
  }
}

void Board::_deactivateTm(void) {
  #ifdef DEBUG
  Serial.println("Deactivated");
  #endif
  if (_active) delete _active;
  _active = NULL;
  _tx = _ty = 0;
}

void Board::_moveLeft(void) {
  if (_isValidMove(0, -1)) {
    _moveTm(0, -1);
  }
}

void Board::_moveRight(void) {
  if (_isValidMove(0, 1)) {
    _moveTm(0, 1);
  }
}

void Board::_moveDown(void) {
  if (_isValidMove(1, 0)) {
    _moveTm(1, 0);
  }
}

void Board::_rotate(void) {
  _active->rotate();
  if (_isValidMove()) {
    _moveTm();
  }
  else { // restore previous orientation
    _active->rotate();
    _active->rotate();
    _active->rotate();
  }
}

void Board::_fall(void) {
  if (_isValidMove(1, 0)) {
    _moveTm(1, 0);
  }
}

bool Board::_isValidMove(int offX, int offY) {
  int ii = max(0, min(_tx + offX, _x));
  int jj = max(0, min(_ty + offY, _y));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (_active->shape[i][j]) {
        if (ii+i >= _x || jj+j >= _y) return false; // outside board
        if (_b[ii+i][jj+j]) return false; // conflict with board
      }
    }
  }
  return true;
}

void Board::_moveTm(int offX, int offY) {
  int ii = max(0, min(_tx + offX, _x));
  int jj = max(0, min(_ty + offY, _y));
  _tx = ii; _ty = jj; // confirms tetrimino move

  bool deactivate = false;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (_active->shape[i][j]) {
        if (ii + i == _x - 1 || // reached bottom
            _b[ii + i + 1][jj + j]) {  // an obstruction below
          deactivate = true;
          break;
        }
      }
    }
  }

  if (deactivate) {
    // Fix tetrimino to board
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (_active->shape[i][j]) {
          _b[ii+i][jj+j] = _active->shape[i][j];
        }
      }
    }
    _deactivateTm();
  }
}

bool Board::_withActiveTm(void) {
  return _active!=NULL;
}
