#include "../src/Queue.cpp"
#include "../src/Input.cpp"

class Board{

    private:
    Queue<Colors> board[4][4];

    public:
    Board(){
        board[0][0].enqueue(yellow);
        board[0][0].enqueue(yellow);

        board[0][3].enqueue(yellow);
        board[0][3].enqueue(yellow);

        board[3][0].enqueue(yellow);
        board[3][0].enqueue(yellow);

        board[3][3].enqueue(yellow);
        board[3][3].enqueue(yellow);
    }

    bool validateInput(input userInput){
        if(userInput.startColumn < 0 || userInput.startColumn > 3) return false;
        if(userInput.startRow < 0 || userInput.startRow > 3) return false;

        if(board[userInput.startRow][userInput.startColumn].size() == 0) return false;

        int directionLength;
        for(directionLength = 1; *(userInput.direction + directionLength) != '\0'; directionLength++);
        //There is a sagnificant chance that this condition here is always off by one or a few more
        //Should bugs where every input is rejected occur this is the first place to look
        if(directionLength != board[userInput.startRow][userInput.startColumn].size() + 1) return false;

        int rowHelper = userInput.startRow;
        int columnHelper = userInput.startColumn;
        char *directionHelper = userInput.direction;

        do{
            if(*directionHelper != 'l' && *directionHelper != 'r'
            && *directionHelper != 'u' && *directionHelper != 'd') return false;

            if(*directionHelper == 'l') rowHelper--;
            if(*directionHelper == 'r') rowHelper++;

            if(*directionHelper == 'u') columnHelper--;
            if(*directionHelper == 'd') columnHelper++;

            if(columnHelper < 0 || columnHelper > 3) return false;
            if(rowHelper < 0 || rowHelper > 3) return false;

            directionHelper++;

        }while(*directionHelper != '\0');

        return true; 
        }

};
