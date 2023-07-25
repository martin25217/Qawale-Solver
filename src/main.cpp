#include"../src/Board.cpp"
#include <string>
#include <iostream>





int main(void){

    Board *board = new Board();

    board->printGameState();
    board->play("00|ddd", red);
    board->printGameState(); 
}
