#include "GameBoard.h"
#include <fstream>


GameBoard::GameBoard(string fileName){
    string deck[52];
    int lnnumber = 0;
    string line;
    ifstream myFile (fileName);
    if (myFile.is_open()){
        while (getline (myFile,line)){
            deck[lnnumber] = line;
            lnnumber ++;;
        }
        myFile.close();
    }
    else{ 
        cout << "Unable to open file";
        return;
    }
    Card deckOfCards[52];
    for(int i = 0; i < 52; i++){
        string str = "";
        (deck[i].at(1) == '0') ? str += deck[i].at(2) : str = str + deck[i].at(1) + deck[i].at(2);
        stringstream str2(str);
        int val = 0;
        str2 >> val;
        Card card(deck[i],deck[i].at(0),val);
        deckOfCards[i] = card;
    }
    int count = 0; 
    int decrease = 8;   
    for(int i = 51; i > 23; i-= decrease){
        switch (count)
        {
        case 0:
            this->piles[count][count] = deckOfCards[i];
            this->piles[count+1][count] = deckOfCards[i-1];
            this->piles[count+2][count] = deckOfCards[i-2];
            this->piles[count+3][count] = deckOfCards[i-3];
            this->piles[count+4][count] = deckOfCards[i-4];
            this->piles[count+5][count] = deckOfCards[i-5];
            this->piles[count+6][count] = deckOfCards[i-6];
            decrease--;
            count++;
            break;
        case 1:
            this->piles[count][count] = deckOfCards[i];
            this->piles[count+1][count] = deckOfCards[i-1];
            this->piles[count+2][count] = deckOfCards[i-2];
            this->piles[count+3][count] = deckOfCards[i-3];
            this->piles[count+4][count] = deckOfCards[i-4];
            this->piles[count+5][count] = deckOfCards[i-5];
            decrease--;
            count++;
            break;
        case 2:
            this->piles[count][count] = deckOfCards[i];
            this->piles[count+1][count] = deckOfCards[i-1];
            this->piles[count+2][count] = deckOfCards[i-2];
            this->piles[count+3][count] = deckOfCards[i-3];
            this->piles[count+4][count] = deckOfCards[i-4];
            decrease--;
            count++;
            break;
        case 3:
            this->piles[count][count] = deckOfCards[i];
            this->piles[count+1][count] = deckOfCards[i-1];
            this->piles[count+2][count] = deckOfCards[i-2];
            this->piles[count+3][count] = deckOfCards[i-3];
            decrease--;
            count++;
            break;
        case 4:
            this->piles[count][count] = deckOfCards[i];
            this->piles[count+1][count] = deckOfCards[i-1];
            this->piles[count+2][count] = deckOfCards[i-2];
            decrease--;
            count++;
            break;
        case 5:
            this->piles[count][count] = deckOfCards[i];
            this->piles[count+1][count] = deckOfCards[i-1];
            decrease--;
            count++;
            break;    
        case 6:
            this->piles[count][count] = deckOfCards[i];
            decrease--;
            count++;
            break;        
        default:
            break;
        }
    }
    int index = 0;
    for(int i = 23; i >= 0; i--){
        this->stock[index] = deckOfCards[i];
        index++;
    }
    for(int i = 0; i < 7; i++){
        piles[i][i].open();
    }
    Card spam;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 3; j++){
            waste[i][j] = spam;
        }
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            foundationArea[i][j] = spam;
        }
    }

}

void writeFile(string fileName, string content){
    ofstream myfile;
    myfile.open(fileName,ios_base::app);
    myfile << content;
    myfile.close();
}

int GameBoard::length(Card *ptr,int size){
    int length = 0;
    for(int i = 0; i < size; i++){
        if(ptr[i].getName() == ""){
            break;
        }
        else{
            length++;
        }
    }
    return length;
}

int GameBoard::maxLengthOfPiles(){
    int maxLength;
    for(int i = 0; i < 7; i++){
        if(length(piles[i],19) >= maxLength){
            maxLength = length(piles[i],19);
        }
    }
    return maxLength;
}

bool GameBoard::isSameColor(Card *card1, Card *card2){
    if((card1.getSuit() ==  'D' || card1.getSuit() == 'H') && (card2.getSuit() ==  'D' || card2.getSuit() == 'H')){
        return true;
    }
    else if((card1.getSuit() ==  'C' || card1.getSuit() == 'S') && (card2.getSuit() ==  'C' || card2.getSuit() == 'S')){
        return true;
    }
    return false;
}

bool GameBoard::canBeMovedToPile(Card &card1, Card &card2){
    int value1 = card1.getValue();
    int value2= card2.getValue();
    if(card2.getSuit() == '-'){
        if(value1 == 13){
            return true;
        }
        return false;
        
    }
    else{
        if(isSameColor(card1,card2)){
            return false;
        }
        else{
            if((value1 + 1) == value2){
                return true;
            }
            else{
                return false;
            }
        }
    }
}

bool GameBoard::canBeMovedToFound(Card &card1,Card &card2){
    int value1 = card1.getValue();
    int value2= card2.getValue();
    if(value2 == 0){
        if(value1 == 1){
            return true;
        }
        return false;
    }
    else{
        if(card1.getSuit() == card2.getSuit()){
            if((value1 -1) == value2){
                return true;
            }
            return false;
        }
        else{
            return false;
        }
    }
}

string GameBoard::displayWaste(){
    string output = "";
    bool checkIf;
    if(length(waste[arrayIndex-1],3) > 0 && length(waste[arrayIndex],3) == 0 && arrayIndex > 0){
        checkIf = true;
    }
    else{
        checkIf = false;
    }
    if(checkIf == false){
        if(length(waste[arrayIndex],3) == 0){
        output += " ___ ___ ___";    
        }
        else{
            for(int i = 0; i < 3; i++){
                if(waste[arrayIndex][i].getName() == ""){
                    output += " ___";
                }
                else{
                    output += " " + waste[arrayIndex][i].show();    
                }      
            }
        } 
    }
    else{
        arrayIndex--;
        output += " " + waste[arrayIndex][length(waste[arrayIndex],3)-1].show();
        output += " ___ ___";   
    }
    return output;
}

string GameBoard::displayFoundationArea(){
    string output = "";
    for(int i = 0; i < 4; i++){
        if(length(foundationArea[i],13) == 0){
            output += " ___";
        }
        else{
            int lenghtOfFoundation = length(foundationArea[i],13);
            output += " " + foundationArea[i][lenghtOfFoundation-1].show();
        }
    }
    return output;

}

string GameBoard::displayTable(){
    string output = "";
    if(length(stock,24) == 0){
        output += "___";
    }
    else{
        output += stock[0].show();
    }
    
    output += displayWaste();
    output += "        ";
    output += displayFoundationArea();
    output += "\n\n";
    for(int i = 0; i < maxLengthOfPiles(); i++){
        for(int j = 0; j < 7; j++){
            if(piles[j][i].getName() == ""){
                output += "   ";
            }           
            else{
                output += piles[j][i].show();    
            }
            output += "   ";
        }
        output += "\n";
    }   
    return output;
}

string GameBoard::movePile(int srcPileNum,int srcPileCardIndex, int destPileNum){
    string output = "";
    Card spam;
    int lenghtOfSrc = length(piles[srcPileNum],19);
    int lengthOfDest = length(piles[destPileNum],19);
    if(canBeMovedToPile(piles[srcPileNum][lenghtOfSrc-(srcPileCardIndex+1)],piles[destPileNum][lengthOfDest-1])){
        for(int i = 0; i < srcPileCardIndex + 1; i++){
            piles[destPileNum][lengthOfDest+i] = piles[srcPileNum][lenghtOfSrc -(srcPileCardIndex+1) + i];
            piles[srcPileNum][lenghtOfSrc-(srcPileCardIndex+1) + i] = spam;
           
        }    
        output += "****************************************\n\n";
    }
    else{
        output += "Invalid Move!\n\n****************************************\n\n";
    }
    output += displayTable() + "\n";
    return output;
   
}

string GameBoard::moveWaste(int destPileNum){
    string output = "";
    Card spam;

    if(canBeMovedToPile(waste[arrayIndex][length(waste[arrayIndex],3)-1],piles[destPileNum][length(piles[destPileNum],19)-1])){
        piles[destPileNum][length(piles[destPileNum],19)] = waste[arrayIndex][length(waste[arrayIndex],3)-1];
        waste[arrayIndex][length(waste[arrayIndex],3)-1] = spam; 
        
        output += "****************************************\n\n";
    }
    else{

        output += "Invalid Move!\n\n****************************************\n\n";
    }
    
    output += displayTable() + "\n";
    return output;

}

string GameBoard::moveFoundation(int srcFoundationNum, int destPileNum){
    string output = "";
    Card spam;
    if(canBeMovedToPile(foundationArea[srcFoundationNum][length(foundationArea[srcFoundationNum],13)-1],piles[destPileNum][length(piles[destPileNum],19)-1])){
        piles[destPileNum][length(piles[destPileNum],19)] = foundationArea[srcFoundationNum][length(foundationArea[srcFoundationNum],13)-1];
        foundationArea[srcFoundationNum][length(foundationArea[srcFoundationNum],13)-1] = spam;   
        output += "****************************************\n\n";
    }
    else{
        output += "Invalid Move\n\n****************************************\n\n";
    }
    output +=  displayTable() + "\n";
    return output;
}

string GameBoard::openFromStock(){
    int n = length(stock,24) - 1;
    string output = "";
    if(n == -1){
        Card spam;
        int m = 0;
        bool isWasteEmpty = true;
        for(int i = 0; i < 8; i++){
            if(isWasteEmpty == false){
                break;
            }
            for(int j = 0; j < 3; j++){
                if(waste[i][j].getName() != ""){
                    isWasteEmpty = false;
                    break;
                }
            }
        }
        if(isWasteEmpty){
            output += "Invalid Move!\n\n****************************************\n\n";
            output += displayTable() + "\n";
            return output;
        }
        else{
            count = 0;
            arrayIndex = 0;
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 3; j++){
                    if(waste[i][j].getName() != ""){
                        stock[m] = waste[i][j];
                        stock[m].flip();
                        waste[i][j] = spam;
                        m++;   
                    }
                }
            }
            output += displayTable() + "\n";
            return output;
        }
    }
    if(count > 0){
        arrayIndex++;
    }   
    count++;
    Card spam;
    for(int i = 0; i < 3; i++){
        stock[i].open();
        waste[arrayIndex][i] = stock[i];   
    }
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < n; j++){
            stock[j] = stock[j+1];
        }    
    }
    
    for(int i = 0; i < 3; i++){
        stock[n-i] = spam;
    }
    output += "****************************************\n\n" + displayTable() + "\n";
    return output;
    
}

string GameBoard::open(int pileNum){
    string output = "";
    piles[pileNum][length(piles[pileNum],19)-1].open();
    output += "****************************************\n\n" + displayTable() + "\n";
    return  output;
}

string GameBoard::moveToFoundationP(int pileNum){
    Card spam;
    string output = "";
    bool isOpen = piles[pileNum][length(piles[pileNum],19)-1].getIsOpen();
    char suit = piles[pileNum][length(piles[pileNum],19)-1].getSuit();
    switch (suit){
    
    case 'H':
        if(canBeMovedToFound(piles[pileNum][length(piles[pileNum],24)-1],foundationArea[0][length(foundationArea[0],13)-1]) && isOpen){
            foundationArea[0][length(foundationArea[0],13)] = piles[pileNum][length(piles[pileNum],19)-1];
            foundationArea[0][length(foundationArea[0],13)].open();
            piles[pileNum][length(piles[pileNum],19)-1] = spam;
            if(foundationArea[0][12].getName() == "H13" && foundationArea[1][12].getName() == "D13" && foundationArea[2][12].getName() == "S13" && foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }
            output += "****************************************\n\n" + displayTable() + "\n";
            return output;  
        }
        else{
            output += "Invalid Move!\n\n****************************************\n\n" + displayTable() + "\n";
            return output;
        }
        break;
    case 'D':
        if(canBeMovedToFound(piles[pileNum][length(piles[pileNum],19)-1],foundationArea[1][length(foundationArea[1],13)-1]) && isOpen){
            foundationArea[1][length(foundationArea[1],13)] = piles[pileNum][length(piles[pileNum],19)-1];
            foundationArea[1][length(foundationArea[1],13)].open();
            piles[pileNum][length(piles[pileNum],19)-1] = spam;
            if(foundationArea[0][12].getName() == "H13" && foundationArea[1][12].getName() == "D13" && foundationArea[2][12].getName() == "S13" && foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }

            output += "****************************************\n\n" + displayTable() + "\n"; 
            return output;
        }
        else{

            output += "Invalid Move!\n\n****************************************\n\n" + displayTable() + "\n";
            return output;
        }
        break;


    case 'S':
        if(canBeMovedToFound(piles[pileNum][length(piles[pileNum],19)-1],foundationArea[2][length(foundationArea[2],13)-1]) && isOpen){
            foundationArea[2][length(foundationArea[2],13)] = piles[pileNum][length(piles[pileNum],19)-1];
            foundationArea[2][length(foundationArea[2],13)].open();
            piles[pileNum][length(piles[pileNum],19)-1] = spam;
            if(foundationArea[0][12].getName() == "H13" && foundationArea[1][12].getName() == "D13" && foundationArea[2][12].getName() == "S13" && foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }

            output += "****************************************\n\n" + displayTable() + "\n"; 
            return output;
        }
        else{

            output += "Invalid Move!\n\n****************************************\n\n" + displayTable() + "\n";
            return output;
        }
        break;
    case 'C':
        if(canBeMovedToFound(piles[pileNum][length(piles[pileNum],19)-1],foundationArea[3][length(foundationArea[3],13)-1]) && isOpen){
            foundationArea[3][length(foundationArea[3],13)] = piles[pileNum][length(piles[pileNum],19)-1];
            foundationArea[3][length(foundationArea[3],13)].open();
            piles[pileNum][length(piles[pileNum],19)-1] = spam;
            if(foundationArea[0][12].getName() == "H13" && foundationArea[1][12].getName() == "D13" && foundationArea[2][12].getName() == "S13" && foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }

            output += "****************************************\n\n" + displayTable() + "\n";
            return output;  
        }
        else{

            output += "Invalid Move!\n\n****************************************\n\n" + displayTable() + "\n";
            return output;
        }
        break;
    default:

        output += "Invalid Move!\n\n****************************************\n\n" + displayTable() + "\n"; 
        return output;
        break;
    }
    
}

string GameBoard::moveToFoundationW(){
    string output = "";
    Card spam;
    char suit = waste[arrayIndex][length(waste[arrayIndex],3)-1].getSuit();
    switch (suit){
    
    case 'H':
        if(canBeMovedToFound(waste[arrayIndex][length(waste[arrayIndex],3)-1],foundationArea[0][length(foundationArea[0],13)-1])){
            foundationArea[0][length(foundationArea[0],13)] = waste[arrayIndex][length(waste[arrayIndex],3)-1];
            foundationArea[0][length(foundationArea[0],13)].open();
            waste[arrayIndex][length(waste[arrayIndex],3)-1] = spam;
            
            if(foundationArea[0][12].getName() == "H13" && foundationArea[1][12].getName() == "D13" && foundationArea[2][12].getName() == "S13" && foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }
            
            output += "****************************************\n\n" + displayTable() + "\n"; 
            return output; 
        }
        else{
            output += "Invalid Move!\n\n****************************************\n" + displayTable() + "\n";
            return output;
        }
        break;
    case 'D':
        if(canBeMovedToFound(waste[arrayIndex][length(waste[arrayIndex],3)-1],foundationArea[1][length(foundationArea[1],13)-1])){
            foundationArea[1][length(foundationArea[1],13)] = waste[arrayIndex][length(waste[arrayIndex],3)-1];
            foundationArea[1][length(foundationArea[1],13)].open();
            waste[arrayIndex][length(waste[arrayIndex],3)-1] = spam;
            if(foundationArea[0][12].getName() == "H13" && foundationArea[1][12].getName() == "D13" && foundationArea[2][12].getName() == "S13" && foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }

            output += "****************************************\n\n" + displayTable() + "\n"; 
            return output; 
        }
        else{

            output += "Invalid Move!\n\n****************************************\n\n" + displayTable() + "\n"; 
            return output;
        }
        break;


    case 'S':
        if(canBeMovedToFound(waste[arrayIndex][length(waste[arrayIndex],3)-1],foundationArea[2][length(foundationArea[2],13)-1])){
            foundationArea[2][length(foundationArea[2],13)] = waste[arrayIndex][length(waste[arrayIndex],3)-1];
            foundationArea[2][length(foundationArea[2],13)].open();
            waste[arrayIndex][length(waste[arrayIndex],3)-1] = spam;
            if(foundationArea[0][12].getName() == "H13" && foundationArea[1][12].getName() == "D13" && foundationArea[2][12].getName() == "S13" && foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }
 
            output += "****************************************\n\n" + displayTable() + "\n"; 
            return output;   
        }
        else{

            output += "Invalid Move!\n\n****************************************\n\n" + displayTable() + "\n"; 
            return output;

        }
        break;
    case 'C':
        if(canBeMovedToFound(waste[arrayIndex][length(waste[arrayIndex],3)-1],foundationArea[3][length(foundationArea[3],13)-1])){
            foundationArea[3][length(foundationArea[3],13)] = waste[arrayIndex][length(waste[arrayIndex],3)-1];
            foundationArea[3][length(foundationArea[3],13)].open();
            waste[arrayIndex][length(waste[arrayIndex],3)-1] = spam;
            if(foundationArea[0][12].getName() == "H13" && foundationArea[1][12].getName() == "D13" && foundationArea[2][12].getName() == "S13" && foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }

            output += "****************************************\n\n" + displayTable() + "\n";
            return output;
        }
        else{
   
            output += "Invalid Move!\n\n****************************************\n\n" + displayTable() + "\n";
            return output;
        }
        break;
    default:
 
        output += "Invalid Move!\n\n****************************************\n\n" + displayTable() + "\n";
        return output;
        break;
    }
}

void GameBoard::readFileAndExecuteCommands(string inputFile,string outputFile){
    writeFile(outputFile,displayTable() + "\n");
    string line;
    ifstream file (inputFile);
    if(file.is_open()){
        while(getline (file,line)){
            if(line == "open from stock"){
                string content = "open from stock\n\n";
                writeFile(outputFile,content);
                writeFile(outputFile,openFromStock());  
            }
            else if(line == "exit"){
                string content = "exit\n\n****************************************\n\nGame Over!\n";
                writeFile(outputFile,content);
            }
            else{
                string lineArray[5];
                int i = 0;
                stringstream s(line);
                while(s.good() && i < 5){
                    s >> lineArray[i];
                    ++i;
                }
                if(lineArray[0] == "open"){
                    string content = "open " + lineArray[1] + "\n\n";
                    int pileNum = 0;
                    stringstream sNum(lineArray[1]);  
                    sNum >> pileNum;
                    writeFile(outputFile,content);
                    writeFile(outputFile,open(pileNum));
                }
                else if(lineArray[0] == "move"){
                    if(lineArray[1] == "to"){
                        if(lineArray[3] == "pile"){
                            string content = "move to foundation pile " + lineArray[4] + "\n\n";
                            int pileNum = 0;
                            stringstream sNum(lineArray[4]);     
                            sNum >> pileNum;
                            writeFile(outputFile,content);
                            writeFile(outputFile,moveToFoundationP(pileNum)); 
                        }
                        else if(lineArray[3] == "waste"){
                            string content = "move to foundation waste\n\n";
                            writeFile(outputFile,content); 
                            writeFile(outputFile,moveToFoundationW());    
                        }        
                    }
                    else if(lineArray[1] == "pile"){
                        string content = "move pile " + lineArray[2] + " " + lineArray[3] + " " + lineArray[4] + "\n\n";
                        int srcPileNum = 0; int srcPileIndex = 0; int destPileNum = 0;
                        stringstream sSrcNum(lineArray[2]);
                        stringstream sSrcIndex(lineArray[3]);
                        stringstream sDestNum(lineArray[4]);
                        sSrcNum >> srcPileNum;
                        sSrcIndex >> srcPileIndex;
                        sDestNum >> destPileNum;
                        writeFile(outputFile,content);
                        writeFile(outputFile,movePile(srcPileNum,srcPileIndex,destPileNum));   
                    }
                    else if(lineArray[1] == "waste"){
                        string content = "move waste " + lineArray[2] + "\n\n";
                        int destPileNum = 0;
                        stringstream sDestNum(lineArray[2]);
                        sDestNum >> destPileNum;
                        writeFile(outputFile,content);
                        writeFile(outputFile,moveWaste(destPileNum));    
                    }
                    else if(lineArray[1] == "foundation"){
                        string content = "move foundation " + lineArray[2] + " " + lineArray[3] + "\n\n";
                        int srcFoundNum = 0; int destPileNum = 0;
                        stringstream sSrcFoundNum(lineArray[2]);
                        stringstream sDestPileNum(lineArray[3]);
                        sSrcFoundNum >> srcFoundNum;
                        sDestPileNum >> destPileNum;
                        writeFile(outputFile,content);
                        writeFile(outputFile,moveFoundation(srcFoundNum,destPileNum));
                    }
                    
                }
      
            }
        }
        file.close();
    }
}

