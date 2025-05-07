#pragma once

enum side {
  RED,
  BLUE
};

enum bot {
  BIG,
  SMALL
};

static bot currentBot = SMALL;
static side fieldColor = RED;

void black_blue();
void black_red();
void red_blue();
void red_red();