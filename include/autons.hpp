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

//RED AUTONS
void drive_example();
void drive_and_turn();
void turn_example();

//BLACK AUTONS
void testbig();