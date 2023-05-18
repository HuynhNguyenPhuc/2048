#include <iostream>
#include <vector>
#include <conio.h>
#include <direct.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include "color.hpp"

using namespace std;

#define BOARD_SIZE 4
#define CELL_WIDTH 7
#define CELL_HEIGHT 5
#define WINNER_NUM 2048

#define RAND(i) rand()%i
#define RAND_IDX rand()%BOARD_SIZE
#define RAND_VAL 4 - (2*rand())%4

#define PADDING_LEFT 50
#define PADDING_TOP 2
#define PADDING_TOP_2 10

#define DELAY_TIME 1000