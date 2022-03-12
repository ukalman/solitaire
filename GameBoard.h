#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_
#include <iostream>
#include <sstream>
#include <string>
#include "Card.cpp"

using namespace std;

class GameBoard{
    public:
        Card foundationArea[4][13];
        Card stock[24];
        Card waste[8][3];
        Card piles[7][19];
        int arrayIndex = 0;
        int count = 0;
    public:
        GameBoard(string fileName);
        int length(Card* ptr, int size);
        int maxLengthOfPiles();
        bool isSameColor(Card &card1,Card &Card2);
        bool canBeMovedToPile(Card &card1,Card &card2);
        bool canBeMovedToFound(Card &card1,Card &card2);
        string displayWaste();
        string displayFoundationArea();
        string displayTable();
        string movePile(int srcPileNum,int srcPileCardIndex, int destPileNum);
        string moveWaste(int destPileNum);
        string moveFoundation(int srcFoundationNum, int destPileNum);
        string openFromStock();
        string open(int pileNum);
        string moveToFoundationP(int pileNum);
        string moveToFoundationW();
        void readFileAndExecuteCommands(string inputFile,string outputFile);

};

#endif /* GAMEBOARD_H_ */