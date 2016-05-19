#include "rgb_lcd.h"

#define BOARD_R 2
#define BOARD_C 15

#define FELL 0
#define BLOCKED 1

class board {
    char b[BOARD_R][BOARD_C];
    rgb_lcd *lcd;
    char bar = 0;
    char gameover = 0;
    int score = 1;
    unsigned level = 0;

    void init();
    char get_new_block();
    void update_score(char block, int mode);
  
  public:
    board(unsigned long s, rgb_lcd *l);
    void adv_board();
    void next_block();
    void print_board();
    void switch_bar();
    unsigned get_level();
    void reset();
};
