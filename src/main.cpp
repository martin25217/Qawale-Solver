#include"../src/Board.cpp"
#include <string>
#include <iostream>





int main(void){

    Board *board = new Board();

    board->printGameState();
    board->printGameState(); //ovo je dovoljno za probleme
    /*
    std::cout << "Enter your input in the form of RowColumn|Directions"<< std::endl;
    std::string inputString;
    std::cin >> inputString;
    std::cout << inputString << std::endl;

    if(turn % 2 == 0) board->play(inputString, red); // provjere unosa stringa sam ukljucula u fji
    else board->play(inputString, white);
*/
}
