#ifndef DECK_H_
#define DECK_H_
#include <vector>
#include <iostream>
#include "Card.h"
#include <stdlib.h>
using namespace std;
class Deck {
private:
    vector<Card *> vecDeck;
public:
    Deck(); //empty Constructor
    Deck(string ofCards, int highestValue); //Constructor
    Deck(const Deck &otherDeck); //Copy Constructor
    Deck& operator=(const Deck &otherDeck); // Assignment operator
    Card* fetchCard();   //Returns the top card of the deck and remove it from the deck
    int getNumberOfCards(); // Get the number of cards in the deck
    string toString(); // Return the cards in top-to-bottom order in a single line, cards are separated by a space ex: "12S QD AS 3H"
    virtual ~Deck();
};
#endif