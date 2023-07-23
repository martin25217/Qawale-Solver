#include"../src/Board.cpp"
#include <string>
#include <iostream>





int main(void){

    Board *board = new Board();

    board->printGameState();

    std::cout << "Enter your input in the form of RowColumn|Directions"<< std::endl;
    std::string inputString;
    std::cin >> inputString;
    std::cout << inputString << std::endl;

    char* inputStringSplit = splitString(inputString);

    input playerInput = convertStringToInput(inputStringSplit); 

}
