#include <stdlib.h>

#include "board.h"

board::board() {
  init();
}

void board::init() {
  for (int r = 0; r < BOARD_R; ++r) {
    for (int c = 0; c < BOARD_C; ++c) {
      b[r][c] = ' ';
    }
  }
}

void board::adv_board() {
  for (int r = 0; r < BOARD_R; ++r) {
    for (int c = BOARD_C - 1; c > 0; --c) {
      b[r][c] = b[r][c - 1];
    }
  }

  // bar blocking the star
  // bar 1 = left
  if (b[0][BOARD_C-2] != ' ' && bar) {
    b[0][BOARD_C-2] = ' ';
  } else if (b[1][BOARD_C-2] != ' ' && !bar) {
    b[1][BOARD_C-2] = ' ';
  }

  // game over
  if (b[0][BOARD_C-1] != ' ' ||
      b[1][BOARD_C-1] != ' ') {
        gameover = 1;
  }
}

void board::next_block() {
  int r = rand();

  if (r % 3 == 0) {
    b[0][0] = '*';
    b[1][0] = ' ';
  } else if (r % 5 == 0) {
    b[0][0] = ' ';
    b[1][0] = '*';
  } else {
    b[0][0] = ' ';
    b[1][0] = ' ';
  }
}

void board::print_board(rgb_lcd *lcd) {
  char str1[] = "                ";
  char str2[] = "                ";

  for (int c = 0; c < BOARD_C; ++c) {
    str1[c] = b[0][c];
  }
  for (int c = 0; c < BOARD_C; ++c) {
    str2[c] = b[1][c];
  }
  
  if (bar) {
    str1[BOARD_C-2] = '|';
  } else {
    str2[BOARD_C-2] = '|';
  }

  if (!gameover) {
    lcd->setRGB(255,255,0);
    lcd->setCursor(0, 0);
    lcd->print(str1);
    lcd->setCursor(0, 1);
    lcd->print(str2);
  } else {
    lcd->setRGB(255,0,0);
    lcd->setCursor(0, 0);
    lcd->print("GAME OVER      ");
    lcd->setCursor(0, 1);
    lcd->print("Press 2 restart");
  }
}

void board::switch_bar() {
  if (gameover) {
    gameover = 0;
    init();
  } else {
    bar = !bar;
  }
}
