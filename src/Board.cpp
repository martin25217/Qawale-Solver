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

int maxSizeQueue(){
        int max = 0;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(board[i][j].size() > max) max = board[i][j].size(); 
            }
        }
        return max;
    }

void printGameState(){ // nova fja koja ispisuje dva puta, ali mislim da sada treba doraditi play fju al msm da je to to ~Viki
        int maxHeight = maxSizeQueue();
        
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                
                std::string result;

                for(int k = 0; k < this->board[i][j].size(); k++){
                    Colors element = this->board[i][j].dequeue();
                    if(element == red){
                        result.push_back('r');
                        this->board[i][j].enqueue(red);
                    }
                    else if(element == white){
                        result.push_back('w');
                        this->board[i][j].enqueue(white);
                    }
                    else{
                        result.push_back('y');
                        this->board[i][j].enqueue(yellow);
                    }
                }

                for(int k = 0; k < maxHeight - this->board[i][j].size(); k++) result.push_back(' ');
                std::cout << result; 
                if(j != 3) std::cout << '|';
                if(j == 3) std::cout << std::endl;
                
            }
        }
    }
    
//making move
 bool play(std::string userIn, Colors playerColor){

        input convertedUserInput = convertStringToInput(splitString(userIn));
        if(!validateInput(convertedUserInput)) return false;

        char* trail = convertedUserInput.direction;

        Queue<Colors> peak = board[convertedUserInput.startRow][convertedUserInput.startColumn];
        int rows = convertedUserInput.startRow;
        int columns = convertedUserInput.startColumn;
        
        peak.enqueue(playerColor);

        while(!peak.isEmpty()){
            if(*trail = 'r') board[rows][columns++].enqueue(peak.dequeue());
            if(*trail = 'l') board[rows][columns--].enqueue(peak.dequeue());
            if(*trail = 'u') board[rows++][columns].enqueue(peak.dequeue());
            if(*trail = 'd') board[rows--][columns].enqueue(peak.dequeue());
        }

        delete &convertedUserInput;

        return true;
    }

};
