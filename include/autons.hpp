#pragma once

enum side {
  RED,
  BLUE
};

enum bot {
  BIG,
  SMALL
};

extern bot currentBot = SMALL;
extern side fieldColor = RED;

void black_blue();
void black_red();
void red_blue();
void red_red();