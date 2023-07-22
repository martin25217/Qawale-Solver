#include"../src/Board.cpp"
#include <string>
#include <iostream>

using namespace std;

int main(void){
    Board *board = new Board();

    int maxHeight = board->maxQ();

    for(int i = 0; i < 16; i++){
        Queue<Colors> b = board->printB(i);
        cout << b.printQ(maxHeight);
        if(i % 4 != 3) cout << '|';
        if(i % 4 == 3) cout << endl;
    }
}
