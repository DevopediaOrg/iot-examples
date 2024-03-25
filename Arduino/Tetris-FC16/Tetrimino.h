#ifndef Tetrimino_h
#define Tetrimino_h

class Tetrimino {
  public:
    bool shape[4][4];

    Tetrimino(void);
    Tetrimino(char shapeName);
    int width(void);
    void rotate(void);
    void print(void);

  private:
    int _shapeIdx = -1;
    const static char _shapeNames[7] = {
      'T', 'S', 'Z', 'L', 'J', 'I', 'O'
    };
    const static int _shapeWidths[7] = {
       3,   3,   3,   3,   3,   4,   2
    };
    const static bool _shapes[7][4][4] = {
      {
        {  true,  true,  true, false },
        { false,  true, false, false },
        { false, false, false, false },
        { false, false, false, false }
      },
      {
        { false,  true,  true, false },
        {  true,  true, false, false },
        { false, false, false, false },
        { false, false, false, false }
      },
      {
        {  true,  true, false, false },
        { false,  true,  true, false },
        { false, false, false, false },
        { false, false, false, false }
      },
      {
        {  true, false, false, false },
        {  true,  true,  true, false },
        { false, false, false, false },
        { false, false, false, false }
      },
      {
        { false, false,  true, false },
        {  true,  true,  true, false },
        { false, false, false, false },
        { false, false, false, false }
      },
      {
        {  true,  true,  true,  true },
        { false, false, false, false },
        { false, false, false, false },
        { false, false, false, false }
      },
      {
        {  true,  true, false, false },
        {  true,  true, false, false },
        { false, false, false, false },
        { false, false, false, false }
      }
    };

    void _setShape(int shapeIdx);
};

#endif