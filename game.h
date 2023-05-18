#ifndef __GAME_H__
#define __GAME_H__

#include "main.h"
#include "graphic.h"

class Game{
    private:
        int board[BOARD_SIZE][BOARD_SIZE];
        int backUp[BOARD_SIZE][BOARD_SIZE];
        
        bool isWinner();
        bool isLoser();
        bool isValidIdx(int x, int y);
        void genIdx();
        void change(int idx, bool isRow, bool isBack);
        bool makePlay(char input);
        int getDigit(int n);
        void printBoard();
        void printState();

    public:
        Game();
        void play();
};

#endif