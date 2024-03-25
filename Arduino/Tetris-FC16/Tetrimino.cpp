#include "Common.h"
#include "Tetrimino.h"

const char Tetrimino::_shapeNames[7];
const int Tetrimino::_shapeWidths[7];
const bool Tetrimino::_shapes[7][4][4];

Tetrimino::Tetrimino(void) {
  _shapeIdx = random(0, 7);
  _setShape(_shapeIdx);
}

Tetrimino::Tetrimino(char shapeName) {
  for (int i = 0; i < 7; i++) {
    if (Tetrimino::_shapeNames[i] == shapeName) {
      _shapeIdx = i;
      _setShape(_shapeIdx);
      return;
    }
  }
}

int Tetrimino::width(void) {
  return _shapeWidths[_shapeIdx];
}

void Tetrimino::rotate(void){
  int N = 4;

  // Plain rotate
  for (int layer = 0; layer < N/2; layer++) {
    int first = layer;
    int last = N - 1 - layer;
    for (int i = first; i < last; i++) {
      int offset = i - first;
      int top = shape[first][i];
      shape[first][i] = shape[last - offset][first]; // left -> top
      shape[last - offset][first] = shape[last][last - offset]; // bottom -> left
      shape[last][last - offset] = shape[i][last]; // right -> bottom
      shape[i][last] = top; // top -> right
    }
  }

  // Trim top
  int numTrim = -1;
  for (int i = 0; i < N && numTrim==-1; i++) {
    for (int j = 0; j < N; j++) {
      if (shape[i][j]) {
        numTrim = i;
        break;
      }
    }
  }
  if (numTrim) {
    for (int i = numTrim; i < N; i++) {
      for (int j = 0; j < N; j++) {
        shape[i-numTrim][j] = shape[i][j];
        shape[i][j] = false;
      }
    }
  }

  // Trim left
  numTrim = -1;
  for (int i = 0; i < N && numTrim==-1; i++) {
    for (int j = 0; j < N; j++) {
      if (shape[j][i]) {
        numTrim = i;
        break;
      }
    }
  }
  if (numTrim) {
    for (int i = numTrim; i < N; i++) {
      for (int j = 0; j < N; j++) {
        shape[j][i-numTrim] = shape[j][i];
        shape[j][i] = 0;
      }
    }
  }
}

void Tetrimino::print(void) {
  int N = 4;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      Serial.print(shape[i][j]);
      Serial.print(" ");
    }
    Serial.println("");
  }
  Serial.println("");
}

void Tetrimino::_setShape(int shapeIdx) {
  #ifdef DEBUG
  Serial.print("Tetrimino: "); Serial.println(_shapeNames[shapeIdx]);
  #endif
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      shape[i][j] = Tetrimino::_shapes[shapeIdx][i][j];
    }
  }
}
