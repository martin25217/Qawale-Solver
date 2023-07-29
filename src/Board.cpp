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
        
        if(!validateInput(convertStringToInput(splitString(userIn)))) return false;

        char* trail = splitString(userIn);

        int iCoordinate = trail[0] - 48, jCoordinate = trail[1] - 48;

        Queue<Colors> peak;
        int size = this->board[iCoordinate][jCoordinate].size();
        for(int i = 0; i < size; i++){
            Colors c = this->board[iCoordinate][jCoordinate].dequeue();
            peak.enqueue(c);
        }
        peak.enqueue(playerColor);
        
        board[iCoordinate][jCoordinate].clear();
        
        for(int i = 3; *(trail + i) != '\0'; i++){
            Colors c = peak.dequeue();
            if(trail[i] == 'd'){
                this->board[++iCoordinate][jCoordinate].enqueue(c);
            }
            else if(trail[i] == 'u'){
                this->board[--iCoordinate][jCoordinate].enqueue(c);
            }
            else if(trail[i] == 'l'){
                this->board[iCoordinate][--jCoordinate].enqueue(c);
            }
            else{
                board[iCoordinate][++jCoordinate].enqueue(c);
            }
        }
        
        return true;
    }

int winCheck(){
        int w = 0, r = 0;
        std::string col;
        std::string row;
        
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                Colors cCol = this->board[i][j].peek();
                Colors cRow = this->board[j][i].peek();
                if(cCol == yellow) col.push_back('y');
                else if(cCol == red) col.push_back('r');
                else col.push_back('w');
                if(cRow == yellow) row.push_back('y');
                else if(cRow == red) row.push_back('r');
                else row.push_back('w');
            }
            if(col == "rrrr") r++;
            else if(col == "wwww") w++;
            if(row == "rrrr") r++;
            else if(col == "wwww") w++;
            col.clear();
            row.clear();
        }

        for(int i = 0; i < 4; i++){
            Colors cCol = this->board[i][i].peek();
            Colors cRow = this->board[3 - i][3 - i].peek();
            if(cCol == yellow) col.push_back('y');
            else if(cCol == red) col.push_back('r');
            else col.push_back('w');
            if(cRow == yellow) row.push_back('y');
            else if(cRow == red) row.push_back('r');
            else row.push_back('w');
        }
        if(col == "rrrr") r++;
        else if(col == "wwww") w++;
        if(row == "rrrr") r++;
        else if(col == "wwww") w++;

        if(w == r && w == 0) return 0; //0 -> no winner
        else if(w == r) return 3; //3 -> izjednačeno -> oba imaju niz od 4
        else if(w > r) return 1; //1 -> w je pobijedio
        else return 2; //2 -> r je pobijedio

    }

};
