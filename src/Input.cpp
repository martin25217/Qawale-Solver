#include<iostream>
#include<string>


char* splitString(std::string input){
    char *result = (char*) malloc((input.size()+1)*sizeof(char));

    for(int i = 0; i <  input.size(); i++){
        *(result + i) = input.at(i);
    }

    *(result + input.size()) = '\0';
    return result;
}

