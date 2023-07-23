#include<iostream>
#include<string>

typedef struct{
    int startRow;
    int startColumn;
    char* direction;
}input;


char* splitString(std::string input){
    char *result = (char*) malloc((input.size()+1)*sizeof(char));

    for(int i = 0; i <  input.size(); i++){
        *(result + i) = input.at(i);
    }

    *(result + input.size()) = '\0';
    return result;
}


input convertStringToInput(char* userInputString){
    input result;
    result.startRow = *userInputString- 48;
    result.startColumn = *(userInputString + 1) - 48;
    result.direction = userInputString + 3;
    return result;
}



