#include "Card.h"

Card::Card(string name,char suit, int value){
    this->name = name;
    this->suit = suit;
    this->value = value;
    this->isOpen = false;
}

Card::Card(){
    this->name = "";
    this->suit = '-';
    this->value = 0;
    this->isOpen = false;
}

void Card::open(){
    this->isOpen = true;
}

void Card::flip(){
    this->isOpen = false;
}
string Card::show(){
    if(isOpen){
        return this->name;
    }
    return "@@@";
}


string Card::getName(){
    return this->name;
}

char Card::getSuit(){
    return this->suit;
}

int Card::getValue(){
    return this->value;
}

bool Card::getIsOpen(){
    return this->isOpen;
}