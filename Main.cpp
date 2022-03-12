#include <iostream>
#include "GameBoard.cpp"
using namespace std;

int main(int argc, char* argv[]){
    string file1 = argv[1]; string file2 = argv[2]; string file3 = argv[3];
    GameBoard gameBoard(file1);
    gameBoard.readFileAndExecuteCommands(file2,file3);
    return 0;
}