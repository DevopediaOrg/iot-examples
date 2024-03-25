#ifndef Board_h
#define Board_h

#include "Arduino.h"
#include "Tetrimino.h"
#include "Scorer.h"

class Board {
  public:
    Board(int x, int y);
    ~Board(void);
    void updateFall(void);
    void processCmd(String cmd);
    bool isGameOver(void);
    void print(void);

  protected:
    int _x, _y; // board dimensions
    bool** _b;
    Tetrimino* _active = NULL;
    int _tx, _ty; // top-left position of _active

  private:
    Scorer _scorer;
    bool _gameOver = false;

    bool** _allocMem(void);
    void _freeMem(bool **m);
    void _clearFullRows(void);
    void _add(Tetrimino* tm);
    void _deactivateTm(void);
    void _moveLeft(void);
    void _moveRight(void);
    void _moveDown(void);
    void _rotate(void);
    void _fall(void);
    bool _isValidMove(int offX=0, int offY=0);
    void _moveTm(int offX=0, int offY=0);
    bool _withActiveTm(void);
};

#endif
