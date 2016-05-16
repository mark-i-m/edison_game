#include "rgb_lcd.h"

#define BOARD_R 2
#define BOARD_C 15

class board {
    char b[BOARD_R][BOARD_C];
    char bar = 0;
    char gameover = 0;
    unsigned score = 1;
    unsigned level = 0;

    void init();
  
  public:
    board(unsigned long s);
    void adv_board();
    void next_block();
    void print_board(rgb_lcd *lcd);
    void switch_bar();
    unsigned get_level();
    void reset();
};
