#include "game.h"
Game::Game(){
    for (int i = 0; i<BOARD_SIZE; i++){
        for (int j = 0; j<BOARD_SIZE; j++){
            this->board[i][j] = 0;
            this->backUp[i][j] = 0;
        }
    }
    int row1 = RAND_IDX, col1 = RAND_IDX;
    int row2, col2;
    do{
        row2 = RAND_IDX;
        col2 = RAND_IDX;
    } while(row2 == row1 && col2 == col1);
    this->board[row1][col1] = RAND_VAL;
    this->board[row2][col2] = RAND_VAL;
}

bool Game::isWinner(){
    for (int i = 0; i<BOARD_SIZE; i++){
        for (int j = 0; j<BOARD_SIZE; j++){
            if (this->board[i][j] == WINNER_NUM) return true;
        }
    }
    return false;
};

bool Game::isLoser(){
    for (int i = 0; i<BOARD_SIZE; i++){
        for (int j = 0; j<BOARD_SIZE; j++){
            if (board[i][j] == 0) return false;
            if (i >= 1 &&  board[i][j] == board[i-1][j]) return false;
            if (j >= 1 && board[i][j] == board[i][j-1]) return false;
            if (i < BOARD_SIZE - 1 && board[i][j] == board[i+1][j]) return false;
            if (j < BOARD_SIZE - 1 && board[i][j] == board[i][j+1]) return false;
        }
    }
    return true;
}

bool Game::isValidIdx(int x, int y){
    if (this->board[x][y] == 0) return true;
    return false;
}

void Game::genIdx(){
    int* tempRow = new int [BOARD_SIZE*BOARD_SIZE];
    int* tempColumn = new int [BOARD_SIZE*BOARD_SIZE];
    int it = 0;
    for (int i = 0; i<BOARD_SIZE; i++){
        for (int j = 0; j<BOARD_SIZE; j++){
            if (isValidIdx(i,j)){
                tempRow[it] = i;
                tempColumn[it] = j;
                it++;
            }
        }
    }
    if (it == 0) return;
    int idx = RAND(it);
    this->board[tempRow[idx]][tempColumn[idx]] = RAND_VAL;
    delete [] tempRow; 
    delete [] tempColumn;
}

void Game::change(int idx, bool isRow, bool isBack){
    if (idx > BOARD_SIZE) return;
    int len = 0;
    int *temp = new int [BOARD_SIZE];
    if (isRow){
        for (int i = 0; i<BOARD_SIZE; i++){
            if (this->board[idx][i] != 0){
                temp[len] = this->board[idx][i];
                len++;
            }
        }
    }
    else{
        for (int i = 0; i<BOARD_SIZE; i++){
            if (this->board[i][idx] != 0){
                temp[len] = this->board[i][idx];
                len++;
            }
        }
    }
    if (len == 0) return;
    int it = 0, tempIt, tempNextIt;
    while (it < len - 1){
        if (isBack){
            tempIt = it;
            tempNextIt = it+1;
        }
        else{
            tempIt = len - 1 - it;
            tempNextIt = len - 2 - it;
        }
        if (temp[tempIt] == temp[tempNextIt]){
            temp[tempIt]*=2;
            temp[tempNextIt] = 0;
            it++;
        }
        it++;
    }
    it = 0;
    if (isBack){
        if (isRow){
            for (int i = 0; i<len; i++){
                if (temp[i] != 0){
                    this->board[idx][it] = temp[i];
                    it++;
                }
            }
            for (int i = it; i<BOARD_SIZE; i++) this->board[idx][i] = 0;
        }
        else{
            for (int i = 0; i<len; i++){
                if (temp[i] != 0){
                    this->board[it][idx] = temp[i];
                    it++;
                }
            }
            for (int i = it; i<BOARD_SIZE; i++) this->board[i][idx] = 0;
        }    
    }
    else{
        if (isRow){
            for (int i = len-1; i>=0; i--){
                if (temp[i] != 0){
                    board[idx][BOARD_SIZE - 1 - it] = temp[i];
                    it++;
                }
            }
            for (int i = BOARD_SIZE - 1 - it; i>=0; i--) board[idx][i] = 0;
        }
        else{
            for (int i = len-1; i>=0; i--){
                if (temp[i] != 0){
                    board[BOARD_SIZE - 1 - it][idx] = temp[i];
                    it++;
                }
            }
            for (int i = BOARD_SIZE - 1 - it; i>=0; i--) board[i][idx] = 0;
        }   
    }
    delete [] temp;
}

bool Game::makePlay(char input){
    if (input != 'w' && input != 'a' && input != 's' && input != 'd' && input != 'e') return false;
    for (int i = 0; i<BOARD_SIZE; i++){
        for (int j = 0; j<BOARD_SIZE; j++){
            this->backUp[i][j] = this->board[i][j];
        }
    }
    for (int i = 0; i<BOARD_SIZE; i++){
        switch(input){
            case 'w':
                this->change(i, false, true);
                break;
            case 's':
                this->change(i, false, false);
                break;
            case 'a':
                this->change(i, true, true);
                break;
            case 'd':
                this->change(i, true, false);
                break;
        }
    }
    for (int i = 0; i<BOARD_SIZE; i++){
        for (int j = 0; j<BOARD_SIZE; j++){
            if (this->backUp[i][j] != this->board[i][j]){
                this->genIdx();
                return true;
            }
        }
    }
    return false;
}

int Game::getDigit(int n){
    int res = 0;
    if (n == 0) return 1;
    while (n > 0){
        n/=10;
        res++;
    }
    return res;
}

void Game::printBoard(){
    int width = (CELL_WIDTH + 1)*BOARD_SIZE + 1;
    int i, j, k, l, nDigit, padding;
    for (i = 0; i<BOARD_SIZE; i++){
        int row = (CELL_HEIGHT + 1)*i;
        for (j = 0; j<=CELL_HEIGHT; j++){
            gotoXY(PADDING_LEFT, PADDING_TOP + row + j);
            if (j == 0){
                for (k = 0; k<width; k++) cout<<dye::on_red(" ");
            }
            else{
                for (k = 0; k<width; k++){
                    if (k%(CELL_WIDTH + 1) == 0) cout<<dye::on_red(" ");
                    else cout<<dye::on_white(" ");
                }
            }
        }
        
    }
    gotoXY(PADDING_LEFT, PADDING_TOP + (CELL_HEIGHT + 1)*BOARD_SIZE);
    for (int i = 0; i<width; i++) cout<<dye::on_red(" ");
}

void Game::printState(){
    int i, j, nDigit, padding;
    for (i = 0; i<BOARD_SIZE; i++){
        int row = (CELL_HEIGHT + 1)*i + (CELL_HEIGHT / 2 + 1);
        for (j = 0; j<BOARD_SIZE; j++){
            if (this->board[i][j]==0) continue;
            nDigit = getDigit(this->board[i][j]);
            padding = (CELL_WIDTH - nDigit)/2;
            gotoXY(PADDING_LEFT + j*(CELL_WIDTH + 1) + padding+1, PADDING_TOP + row);
            cout<<dye::purple_on_white(this->board[i][j]);
        }   
    }
}

void Game::play(){  
    char input; bool check;
    this->printBoard();
    this->printState();
    while (!this->isWinner() && !this->isLoser()){
        input = getch();
        if (input == 'e') return;
        if (makePlay(input)){
            this->printBoard();
            this->printState();
        }
    }
    
    Sleep(DELAY_TIME/2);
    system("cls");
    gotoXY(PADDING_LEFT, PADDING_TOP_2);
    if (this->isWinner()) cout<<"You win!";
    else if (this->isLoser()) cout<<"You lose!";
     gotoXY(PADDING_LEFT, PADDING_TOP_2 + 2);
    cout<<"Press any key to go back to menu...";
    getch();
    Sleep(DELAY_TIME);
}

