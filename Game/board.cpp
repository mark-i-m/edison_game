#include <stdlib.h>

#include "board.h"

#define max(a,b) ((a) > (b) ? (a) : (b))

#define NUM_COLORS 8
int colors[NUM_COLORS][3] = {
  {255,255,255},
  {255,255,128},
  {255,255,  0},
  {255,128,128},
  {255,  0,255},
  {128,128,255},
  {0  ,255,255},
  {128,128,128},
};

board::board(unsigned long s, rgb_lcd *l) {
  init();

  lcd = l;

  // seed the random number generator
  srand(s);
}

void board::init() {
  for (int r = 0; r < BOARD_R; ++r) {
    for (int c = 0; c < BOARD_C; ++c) {
      b[r][c] = ' ';
    }
  }

  score = 1;
  level = 0;
  gameover = 0;
}

void board::update_score(char block, int mode) {
  switch (block) {
    case '*':
      if (mode == FELL) {
        score -= 1;
      } else if (mode == BLOCKED) {
        score += 1;
      }
      break;

    case '#':
      if (mode == FELL) {
        score -= 40;
      }
      break;

    case '+':
      if (mode == BLOCKED) {
        score += 10;
      }
      break;
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
    update_score(b[0][BOARD_C-2], BLOCKED);
    b[0][BOARD_C-2] = ' ';
  } else if (b[1][BOARD_C-2] != ' ' && !bar) {
    update_score(b[1][BOARD_C-2], BLOCKED);
    b[1][BOARD_C-2] = ' ';
  }

  // star fell through
  if (b[0][BOARD_C-1] != ' ') {
    update_score(b[0][BOARD_C-1], FELL);
  } else if (b[1][BOARD_C-1] != ' ') {
    update_score(b[1][BOARD_C-1], FELL);
  }

  // game over
  if (score <= 0) {
    gameover = 1;
  } else {
    // adjust level
    level = score / 20;
  }
}

char board::get_new_block() {
  int r = rand();

  switch (r % 3) {
    case 0:
      return '*';
    case 1:
      return '#';
    case 2:
      return '+';
  }
}

void board::next_block() {
  int r = rand();

  if (r % 3 == 0) {
    if (r % 2 == 0) {
      b[bar][0] = get_new_block();
      b[!bar][0] = ' ';
    } else if (r % 5 == 0) {
      b[bar][0] = ' ';
      b[!bar][0] = get_new_block();
    }
  } else {
    b[0][0] = ' ';
    b[1][0] = ' ';
  }
}

void board::print_board() {
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

  str1[0] = ((score % 20) / 10) + 0x30;
  str2[0] = ((score % 20) % 10) + 0x30;

  if (!gameover) {
    int c = level % NUM_COLORS;
    lcd->setRGB(colors[c][0], colors[c][1], colors[c][2]);
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
    init();
  } else {
    bar = !bar;
  }
}

unsigned board::get_level() {
  return level;
}

void board::reset() {
  gameover = 1;
}
