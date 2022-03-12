#ifndef COMMANDS_H_
#define COMMANDS_H_
#include <iostream>
#include "GameBoard.cpp"

using namespace std;

class Commands{
    public:
        GameBoard* gameBoard;
        string deck[52];

    public:
        Commands(string fileName);
        ~Commands();
        string open(int pileNum);
        string openFromStock();
        string moveToFoundationP(int pileNum);
        string moveToFoundationW();
        string movePile(int srcPileNum,int srcPileCardIndex, int destPileNum);
        string moveWaste(int destPileNum);
        string moveFoundation(int srcFoundationNum, int destPileNum);
        string exit();
        void writeFile(string fileName, string content);
        void readFileAndExecuteCommands(string inputFile,string outputFile);
        
};



#endif /* COMMANDS_H_ */