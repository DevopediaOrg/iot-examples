#include "Common.h"
#include "Scorer.h"

Scorer::Scorer(void) {
  _score = 0;
}

void Scorer::scoreRows(int numRows) {
  if (numRows == 1) _score += 5;
  else if (numRows == 2) _score += 15;
  else if (numRows == 3) _score += 30;
  else if (numRows == 4) _score += 50;
}

void Scorer::scoreNewTetrimino(void) {
  _score += 2;  
}

unsigned long Scorer::getScore(void) {
  return _score;
}
