#include<iostream>
#include<string>

typedef struct{
    int startRow;
    int startColumn;
    char* direction;
}input;

char* getPlayerInput(){
    return NULL;
}

input convertStringToInput(char* userInputString){
    input result;
    result.startRow = *userInputString- 48;
    result.startColumn = *userInputString - 48;
    result.direction = userInputString + 3;
    return result;
}



