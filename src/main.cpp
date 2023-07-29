#include"../src/Board.cpp"
#include <string>
#include <iostream>





int main(void){

    Board *board = new Board();
board->printGameState();

    int win;

    do{
        std::cout << "Player ";
        if(turn % 2 == 0) std::cout << "red";
        else std::cout << "white";
        std::cout << ": enter your input in the form of RowColumn|Directions"<< std::endl;
        std::string inputString;
        std::cin >> inputString;
        std::cout << "Your move is: ";
        std::cout << inputString << std::endl;

        bool played;

        if(turn % 2 == 0) played = board->play(inputString, red);
        else played = board->play(inputString, white);

        if(played == false) turn -= 1;

        board->printGameState();

        win = board->winCheck();
        if(win == 1) std::cout << "WIN: Winner is white player!" << std::endl;
        else if(win == 2) std::cout << "WIN: Winner is red player!" << std::endl;
        else if(win == 3) std::cout << "No winner: game is undecided." << std::endl;

        turn += 1;
    }while(win == 0 && turn < 17);

    if(win == 0) std::cout << "No winner: game is undecided." << std::endl;
    
}
