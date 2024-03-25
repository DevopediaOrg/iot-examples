#ifndef Scorer_h
#define Scorer_h

class Scorer {
  public:
    Scorer(void);
    void scoreRows(int numRows);
    void scoreNewTetrimino(void);
    unsigned long getScore(void);

  private:
    unsigned long _score = 0;
};

#endif
