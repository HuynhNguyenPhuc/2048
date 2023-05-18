#include "game.h"
#include "graphic.h"

// g++ -o main main.cpp game.cpp graphic.cpp color.hpp -std=c++14

void instructions(){
    system("cls");
    gotoXY(PADDING_LEFT, PADDING_TOP_2);     cout<<"Instructions";
    gotoXY(PADDING_LEFT, PADDING_TOP_2 + 1); cout<<"----------------";
    gotoXY(PADDING_LEFT, PADDING_TOP_2 + 2); cout<<"Get 2048 value to win this game!";
    gotoXY(PADDING_LEFT, PADDING_TOP_2 + 3); cout<<"Press 'a' to move left";
    gotoXY(PADDING_LEFT, PADDING_TOP_2 + 4); cout<<"Press 'd' to move right";
    gotoXY(PADDING_LEFT, PADDING_TOP_2 + 5); cout<<"Press 'w' to move up";
    gotoXY(PADDING_LEFT, PADDING_TOP_2 + 6); cout<<"Press 's' to move down";
    gotoXY(PADDING_LEFT, PADDING_TOP_2 + 7); cout<<"Press 'e' to exit the game";
    gotoXY(PADDING_LEFT, PADDING_TOP_2 + 9); cout<<"Press any key to go back to menu...";
    getch();
}

int main()
{
    srand(time(NULL));

    while (true){
        system("cls");
        gotoXY(PADDING_LEFT, PADDING_TOP_2);     cout<<" -------------------------- ";
        gotoXY(PADDING_LEFT, PADDING_TOP_2 + 1); cout<<" |                        | ";  
        gotoXY(PADDING_LEFT, PADDING_TOP_2 + 2); cout<<" |          2048          | ";
        gotoXY(PADDING_LEFT, PADDING_TOP_2 + 3); cout<<" |                        | ";   
        gotoXY(PADDING_LEFT, PADDING_TOP_2 + 4); cout<<" --------------------------";
        gotoXY(PADDING_LEFT, PADDING_TOP_2 + 6); cout<<"Press 1 to start game";
        gotoXY(PADDING_LEFT, PADDING_TOP_2 + 7); cout<<"Press 2 to see instructions";  
        gotoXY(PADDING_LEFT, PADDING_TOP_2 + 8); cout<<"Press 3 to quit";
        char op = getch();
        
        if(op == '1'){
            system("cls");
            Game* game = new Game();
            game->play();
            delete game;
        }
        else if(op == '2') instructions();
        else if(op == '3') break;
    }
    return 0;
}