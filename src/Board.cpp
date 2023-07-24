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

    //Input functions start

    void printGameState(){
        int maxHeight = maxSizeQueue();

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                
                
                std::cout << printQueue(maxHeight, this->board[i][j]); 
                if(j != 3) std::cout << '|';
                if(j == 3) std::cout << std::endl;
                
            }
        }
    }

    int maxSizeQueue(){
        int max = 0;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(board[i][j].size() > max) max = board[i][j].size(); 
            }
        }
        return max;
    }

    std::string printQueue(int maxHeight, Queue<Colors> queue){
        std::string result;
        Queue<Colors> helperQueue;

        int size = queue.size();
        for(int i = 0; i < size; i++){
            Colors element = queue.dequeue();
            if(element == red) result.push_back('r');
            else if(element == white) result.push_back('w');
            else result.push_back('y');
            helperQueue.enqueue(element);
        }

        while(!helperQueue.isEmpty()) queue.enqueue(helperQueue.dequeue()); //po meni je ovo problem
        int length = queue.size();
        for(int i = length; i < maxHeight; i++) result.push_back(' ');

        return result;
    }

    //Input functions end

//making move
 bool play(std::string userIn, Colors playerColor){
        if(!validateInput(convertStringToInput(splitString(userIn)))) return false;

        char* trail = splitString(userIn);
        std::cout << printQueue(maxSizeQueue(), this->board[int(trail[0]) - 48][int(trail[1]) - 48]) << std::endl;
        Queue<Colors> peak;
        for(int i = 0; i < this->board[int(trail[0])][int(trail[1])].size(); i++) peak.enqueue(this->board[int(trail[0])][int(trail[1])].dequeue());
        peak.enqueue(playerColor);

        board[int(trail[0])][int(trail[1])].clear();

        for(int i = 2; *(trail + i) != '\0'; i++){
            Colors c = peak.dequeue();
            if(trail[i] == 'd'){
                this->board[trail[0] + 1][trail[1]].enqueue(c);
            }
            else if(trail[i] == 'u'){
                this->board[trail[0] - 1][trail[1]].enqueue(c);
            }
            else if(trail[i] == 'l'){
                this->board[trail[0]][trail[1] - 1].enqueue(c);
            }
            else{
                this->board[trail[0]][trail[1] + 1].enqueue(c);
            }
        }

        return true;
    }

};
