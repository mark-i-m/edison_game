#include "rgb_lcd.h"

#define BOARD_R 2
#define BOARD_C 15

class board {
    char b[BOARD_R][BOARD_C];
    char bar = 0;
    char gameover = 0;

    void init();
  
  public:
    board();
    void adv_board();
    void next_block();
    void print_board(rgb_lcd *lcd);
    void switch_bar();
};
