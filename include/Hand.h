#ifndef HAND_H_
#define HAND_H_
#include <iostream>
#include <map>
#include "Card.h"
#include <vector>
using namespace std;
class Hand {
private:
    int returnsPlace(Card &card);
    int returnValueOfCard(Card &card);
    void eraseReviiya(int valueToErase);
public: 
    map<int ,Card *> mapOfCards;
    map<int ,int> mapCounter; //map<value,counter>
    Hand(); //empty Constructor
    Hand(const Hand &OtherHand); //Copy Constructor
    Hand& operator=(const Hand &otherHand); //Assignment operator
    virtual ~Hand(); //destructor
    bool addCard(Card &card);
    bool removeCard(Card &card);
    int getNumberOfCards(); // Get the number of cards in hand
    string toString(); // Return a list of the cards, separated by space, in one line
    int hasTheLeastOf();
    int hasTheMostOf();
};
#endif