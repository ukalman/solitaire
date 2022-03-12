#ifndef CARD_H_
#define CARD_H_
#include <iostream>

using namespace std;

class Card{
    private:
        string name;
        char suit;
        int value;
        bool isOpen;

    public:
        Card(string name,char suit,int value);
        Card();
        void open();
        void flip();
        string show();
        string getName();
        void setName(string name);
        char getSuit();
        void setSuit(char suit);
        int getValue();
        void setValue(int value);
        bool getIsOpen();


};

#endif /* CARD_H_ */