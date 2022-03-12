#include "Commands.h"

Commands::Commands(string fileName){
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
    cout << deck[0];
    GameBoard gameBoardObject(deck);
    gameBoard = &gameBoardObject;

}

Commands::~Commands(){
    delete gameBoard;
}

string Commands::open(int pileNum){
    string output = "";
    gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1].open();
    output += "****************************************\n\n" + gameBoard->displayTable() + "\n";
    return output;
}


string Commands::openFromStock(){
    int n = gameBoard->length(gameBoard->stock,24) - 1;
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
                if(gameBoard->waste[i][j].getName() != ""){
                    isWasteEmpty = false;
                    break;
                }
            }
        }
        if(isWasteEmpty){
            output += "Invalid Move!\n\n****************************************\n\n";
            output += gameBoard->displayTable() + "\n";
            return output;
        }
        else{
            gameBoard->count = 0;
            gameBoard->arrayIndex = 0;
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 3; j++){
                    if(gameBoard->waste[i][j].getName() != ""){
                        gameBoard->stock[m] = gameBoard->waste[i][j];
                        gameBoard->stock[m].flip();
                        gameBoard->waste[i][j] = spam;
                        m++;   
                    }
                }
            }
            output += gameBoard->displayTable() + "\n";
            return output;
        }
    }
    if(gameBoard->count > 0){
        gameBoard->arrayIndex++;
    }   
    gameBoard->count++;
    Card spam;
    for(int i = 0; i < 3; i++){
        gameBoard->stock[i].open();
        gameBoard->waste[gameBoard->arrayIndex][i] = gameBoard->stock[i];   
    }
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < n; j++){
            gameBoard->stock[j] = gameBoard->stock[j+1];
        }    
    }
    
    for(int i = 0; i < 3; i++){
        gameBoard->stock[n-i] = spam;
    }

    output += "****************************************\n\n" + gameBoard->displayTable() + "\n";
    return output;
}

string Commands::moveToFoundationP(int pileNum){
    Card spam;
    string output = "";
    bool isOpen = gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1].getIsOpen();
    char suit = gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1].getSuit();
    switch (suit){
    
    case 'H':
        if(gameBoard->canBeMovedToFound(gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],24)-1],gameBoard->foundationArea[0][gameBoard->length(gameBoard->foundationArea[0],13)-1]) && isOpen){
            gameBoard->foundationArea[0][gameBoard->length(gameBoard->foundationArea[0],13)] = gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1];
            gameBoard->foundationArea[0][gameBoard->length(gameBoard->foundationArea[0],13)].open();
            gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1] = spam;
            if(gameBoard->foundationArea[0][12].getName() == "H13" && gameBoard->foundationArea[1][12].getName() == "D13" && gameBoard->foundationArea[2][12].getName() == "S13" && gameBoard->foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + gameBoard->displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }
            output += "****************************************\n\n" + gameBoard->displayTable() + "\n";
            return output;  
        }
        else{
            output += "Invalid Move!\n\n****************************************\n\n" + gameBoard->displayTable() + "\n";
            return output;
        }
        break;
    case 'D':
        if(gameBoard->canBeMovedToFound(gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1],gameBoard->foundationArea[1][gameBoard->length(gameBoard->foundationArea[1],13)-1]) && isOpen){
            gameBoard->foundationArea[1][gameBoard->length(gameBoard->foundationArea[1],13)] = gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1];
            gameBoard->foundationArea[1][gameBoard->length(gameBoard->foundationArea[1],13)].open();
            gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1] = spam;
            if(gameBoard->foundationArea[0][12].getName() == "H13" && gameBoard->foundationArea[1][12].getName() == "D13" && gameBoard->foundationArea[2][12].getName() == "S13" && gameBoard->foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + gameBoard->displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }

            output += "****************************************\n\n" + gameBoard->displayTable() + "\n"; 
            return output;
        }
        else{
            output += "Invalid Move!\n\n****************************************\n\n" + gameBoard->displayTable() + "\n";
            return output;
        }
        break;


    case 'S':
        if(gameBoard->canBeMovedToFound(gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1],gameBoard->foundationArea[2][gameBoard->length(gameBoard->foundationArea[2],13)-1]) && isOpen){
            gameBoard->foundationArea[2][gameBoard->length(gameBoard->foundationArea[2],13)] = gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1];
            gameBoard->foundationArea[2][gameBoard->length(gameBoard->foundationArea[2],13)].open();
            gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1] = spam;
            if(gameBoard->foundationArea[0][12].getName() == "H13" && gameBoard->foundationArea[1][12].getName() == "D13" && gameBoard->foundationArea[2][12].getName() == "S13" && gameBoard->foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + gameBoard->displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }

            output += "****************************************\n\n" + gameBoard->displayTable() + "\n"; 
            return output;
        }
        else{
            output += "Invalid Move!\n\n****************************************\n\n" + gameBoard->displayTable() + "\n";
            return output;
        }
        break;
    case 'C':
        if(gameBoard->canBeMovedToFound(gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1],gameBoard->foundationArea[3][gameBoard->length(gameBoard->foundationArea[3],13)-1]) && isOpen){
            gameBoard->foundationArea[3][gameBoard->length(gameBoard->foundationArea[3],13)] = gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1];
            gameBoard->foundationArea[3][gameBoard->length(gameBoard->foundationArea[3],13)].open();
            gameBoard->piles[pileNum][gameBoard->length(gameBoard->piles[pileNum],19)-1] = spam;
            if(gameBoard->foundationArea[0][12].getName() == "H13" && gameBoard->foundationArea[1][12].getName() == "D13" && gameBoard->foundationArea[2][12].getName() == "S13" && gameBoard->foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + gameBoard->displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }

            output += "****************************************\n\n" + gameBoard->displayTable() + "\n";
            return output;  
        }
        else{

            output += "Invalid Move!\n\n****************************************\n\n" + gameBoard->displayTable() + "\n";
            return output;
        }
        break;
    default:
        output += "Invalid Move!\n\n****************************************\n\n" + gameBoard->displayTable() + "\n"; 
        return output;
        break;
    }
}

string Commands::moveToFoundationW(){
    string output = "";
    Card spam;
    char suit = gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1].getSuit();
    switch (suit){
    
    case 'H':
        if(gameBoard->canBeMovedToFound(gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1],gameBoard->foundationArea[0][gameBoard->length(gameBoard->foundationArea[0],13)-1])){
            gameBoard->foundationArea[0][gameBoard->length(gameBoard->foundationArea[0],13)] = gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1];
            gameBoard->foundationArea[0][gameBoard->length(gameBoard->foundationArea[0],13)].open();
            gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1] = spam;
            
            if(gameBoard->foundationArea[0][12].getName() == "H13" && gameBoard->foundationArea[1][12].getName() == "D13" && gameBoard->foundationArea[2][12].getName() == "S13" && gameBoard->foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + gameBoard->displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }
            
            output += "****************************************\n\n" + gameBoard->displayTable() + "\n"; 
            return output; 
        }
        else{
            output += "Invalid Move!\n\n****************************************\n" + gameBoard->displayTable() + "\n";
            return output;
        }
        break;
    case 'D':
        if(gameBoard->canBeMovedToFound(gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1],gameBoard->foundationArea[1][gameBoard->length(gameBoard->foundationArea[1],13)-1])){
            gameBoard->foundationArea[1][gameBoard->length(gameBoard->foundationArea[1],13)] = gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1];
            gameBoard->foundationArea[1][gameBoard->length(gameBoard->foundationArea[1],13)].open();
            gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1] = spam;
            if(gameBoard->foundationArea[0][12].getName() == "H13" && gameBoard->foundationArea[1][12].getName() == "D13" && gameBoard->foundationArea[2][12].getName() == "S13" && gameBoard->foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + gameBoard->displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }

            output += "****************************************\n\n" + gameBoard->displayTable() + "\n"; 
            return output; 
        }
        else{
            output += "Invalid Move!\n\n****************************************\n\n" + gameBoard->displayTable() + "\n"; 
            return output;
        }
        break;


    case 'S':
        if(gameBoard->canBeMovedToFound(gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1],gameBoard->foundationArea[2][gameBoard->length(gameBoard->foundationArea[2],13)-1])){
            gameBoard->foundationArea[2][gameBoard->length(gameBoard->foundationArea[2],13)] = gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1];
            gameBoard->foundationArea[2][gameBoard->length(gameBoard->foundationArea[2],13)].open();
            gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1] = spam;
            if(gameBoard->foundationArea[0][12].getName() == "H13" && gameBoard->foundationArea[1][12].getName() == "D13" && gameBoard->foundationArea[2][12].getName() == "S13" && gameBoard->foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + gameBoard->displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }
            output += "****************************************\n\n" + gameBoard->displayTable() + "\n"; 
            return output;   
        }
        else{
            output += "Invalid Move!\n\n****************************************\n\n" + gameBoard->displayTable() + "\n"; 
            return output;

        }
        break;
    case 'C':
        if(gameBoard->canBeMovedToFound(gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1],gameBoard->foundationArea[3][gameBoard->length(gameBoard->foundationArea[3],13)-1])){
            gameBoard->foundationArea[3][gameBoard->length(gameBoard->foundationArea[3],13)] = gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1];
            gameBoard->foundationArea[3][gameBoard->length(gameBoard->foundationArea[3],13)].open();
            gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1] = spam;
            if(gameBoard->foundationArea[0][12].getName() == "H13" && gameBoard->foundationArea[1][12].getName() == "D13" && gameBoard->foundationArea[2][12].getName() == "S13" && gameBoard->foundationArea[3][12].getName() == "C13"){
                output += "****************************************\n\n" + gameBoard->displayTable() + "\n" + "\n";
                output += "****************************************\n\nYou Win!\n\nGame Over!\n";
                return output;
            }
            output += "****************************************\n\n" + gameBoard->displayTable() + "\n";
            return output;
        }
        else{
            output += "Invalid Move!\n\n****************************************\n\n" + gameBoard->displayTable() + "\n";
            return output;
        }
        break;
    default:
        output += "Invalid Move!\n\n****************************************\n\n" + gameBoard->displayTable() + "\n";
        return output;
        break;
    }
}

string Commands::movePile(int srcPileNum,int srcPileCardIndex, int destPileNum){
    string output = "";
    Card spam;
    int lenghtOfSrc = gameBoard->length(gameBoard->piles[srcPileNum],19);
    int lengthOfDest = gameBoard->length(gameBoard->piles[destPileNum],19);
    if(gameBoard->canBeMovedToPile(gameBoard->piles[srcPileNum][lenghtOfSrc-(srcPileCardIndex+1)],gameBoard->piles[destPileNum][lengthOfDest-1])){
        for(int i = 0; i < srcPileCardIndex + 1; i++){
            gameBoard->piles[destPileNum][lengthOfDest+i] = gameBoard->piles[srcPileNum][lenghtOfSrc -(srcPileCardIndex+1) + i];
            gameBoard->piles[srcPileNum][lenghtOfSrc-(srcPileCardIndex+1) + i] = spam;
           
        }    
        output += "****************************************\n\n";
    }
    else{
        output += "Invalid Move!\n\n****************************************\n\n";
    }
    output += gameBoard->displayTable() + "\n";
    return output;
}

string Commands::moveWaste(int destPileNum){
    string output = "";
    Card spam;

    if(gameBoard->canBeMovedToPile(gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1],gameBoard->piles[destPileNum][gameBoard->length(gameBoard->piles[destPileNum],19)-1])){
        gameBoard->piles[destPileNum][gameBoard->length(gameBoard->piles[destPileNum],19)] = gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1];
        gameBoard->waste[gameBoard->arrayIndex][gameBoard->length(gameBoard->waste[gameBoard->arrayIndex],3)-1] = spam; 
        output += "****************************************\n\n";
    }
    else{
        output += "Invalid Move!\n\n****************************************\n\n";
    }
    
    output += gameBoard->displayTable() + "\n";
    return output;

}

string Commands::moveFoundation(int srcFoundationNum, int destPileNum){
    string output = "";
    Card spam;
    if(gameBoard->canBeMovedToPile(gameBoard->foundationArea[srcFoundationNum][gameBoard->length(gameBoard->foundationArea[srcFoundationNum],13)-1],gameBoard->piles[destPileNum][gameBoard->length(gameBoard->piles[destPileNum],19)-1])){
        gameBoard->piles[destPileNum][gameBoard->length(gameBoard->piles[destPileNum],19)] = gameBoard->foundationArea[srcFoundationNum][gameBoard->length(gameBoard->foundationArea[srcFoundationNum],13)-1];
        gameBoard->foundationArea[srcFoundationNum][gameBoard->length(gameBoard->foundationArea[srcFoundationNum],13)-1] = spam;   
        output += "****************************************\n\n";
    }
    else{
        output += "Invalid Move\n\n****************************************\n\n";
    }
    output +=  gameBoard->displayTable() + "\n";
    return output;
}

string Commands::exit(){
    string output = "exit\n\n****************************************\n\nGame Over!\n";
    return output;
}

void Commands::writeFile(string fileName, string content){
    ofstream myfile;
    myfile.open(fileName,ios_base::app);
    myfile << content;
    myfile.close();

}

void Commands::readFileAndExecuteCommands(string inputFile,string outputFile){
    writeFile(outputFile,gameBoard->displayTable() + "\n");
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

/*
int main(int argc, char* argv[]){
    string file1 = argv[1]; string file2 = argv[2]; string file3 = argv[3];
    Commands commands(file1);
    commands.readFileAndExecuteCommands(file2,file3);
    return 0;
}
*/

