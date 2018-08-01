#include "Hand.h"
using namespace std;

//Constructor
Hand::Hand(): mapOfCards(),mapCounter(){}

//Copy Constructor
Hand::Hand(const Hand &otherHand):mapOfCards(),mapCounter(){

 for(map<int,Card*>::const_iterator iter = otherHand.mapOfCards.begin() ; iter != otherHand.mapOfCards.end() ; iter++ ){
            if(iter->second->isFigureCard)
                mapOfCards.insert(pair<int,Card*>(iter->first, new FigureCard(dynamic_cast<FigureCard &>(*iter->second))));
            else
                mapOfCards.insert(pair<int,Card*>(iter->first, new NumericCard(dynamic_cast<NumericCard &>(*iter->second))));
        }
        
  for(map<int,int>::const_iterator iter2 = otherHand.mapCounter.begin() ; iter2 != otherHand.mapCounter.end() ; iter2++ ){
        mapCounter.insert(pair<int,int>(iter2->first,iter2->second));
  }
   
}

//Assignment operator
Hand& Hand::operator=(const Hand &otherHand){
    if (this != &otherHand) {
        for(map<int,Card*>::const_iterator iter = otherHand.mapOfCards.begin() ; iter != otherHand.mapOfCards.end() ; iter++ ){
            if(iter->second->isFigureCard)
                mapOfCards.insert(pair<int,Card*>(iter->first, new FigureCard(dynamic_cast<FigureCard &>(*iter->second))));
            else
                mapOfCards.insert(pair<int,Card*>(iter->first, new NumericCard(dynamic_cast<NumericCard &>(*iter->second))));
        }
    
    
     for(map<int,int>::const_iterator iter2 = otherHand.mapCounter.begin() ; iter2 != otherHand.mapCounter.end() ; iter2++ ){
        mapCounter.insert(pair<int,int>(iter2->first,iter2->second));
     }
  }
  return *this;
}

//destructor
Hand::~Hand() {
    map<int,Card*>::iterator it;
    for (it = mapOfCards.begin(); it != mapOfCards.end() ; it++)
        delete it->second;
    mapOfCards.clear();
}

//This method returns True if a card has been added to the deck
bool Hand::addCard(Card &card) {
    int orderNumber = returnsPlace(card);

    if (mapOfCards.find(orderNumber) == mapOfCards.end()) {
        mapOfCards[orderNumber] = &card;
        int value = returnValueOfCard(card);
        mapCounter[value]++;
        if (mapCounter[value] == 4){
            int valueToErase = value; // if counter is 4
            mapCounter.erase(value);  //clean the map
            eraseReviiya(valueToErase); //erase from  a player's Hand
        }

        return true;
    }

    return false;
}
//in case the number of cards from a specific value is equal to four we erase all four cards
void Hand:: eraseReviiya(int valueToErase){
    for(int i = 0 ; i < 4 ; i++){
        Card *toDelete;
       toDelete =  mapOfCards[((valueToErase-2)*4 + i)];
        
        mapOfCards.erase((valueToErase-2)*4 + i);
        delete(toDelete);
        
    }
    
}
//this method returns true if a card has been removed
bool Hand::removeCard(Card &card) {
    int indexToDelete = returnsPlace(card);
    if (mapOfCards.find(indexToDelete) != mapOfCards.end()){
        mapOfCards.erase(indexToDelete);
        int value = returnValueOfCard(card);
        mapCounter[value]--;
        if ( mapCounter[value] == 0 ) {
            mapCounter.erase(value);
        }

        return true;
    }
    return false;
}

// Get the number of cards in hand
int Hand::getNumberOfCards() {
    return mapOfCards.size();
}

// Return a list of the cards
string Hand::toString() {
    map<int, Card*>::iterator it = mapOfCards.begin();
    string stringToReturn;
    while (it != mapOfCards.end()){
        stringToReturn += it->second->toString() + " ";
        it++;
    } //while
    return stringToReturn;
}

//this method returns the specific key of a card over the map
int Hand::returnsPlace(Card &card) {
    if (card.isFigureCard) {
        if (dynamic_cast<FigureCard &>(card).getFigure() == Jack) return (card.getHighestValue() - 1) * 4 + card.getShape();
        else if (dynamic_cast<FigureCard &>(card).getFigure() == Queen) return (card.getHighestValue()) * 4 + card.getShape();
        else if (dynamic_cast<FigureCard &>(card).getFigure() == King) return (card.getHighestValue() + 1) * 4 + card.getShape();
        else return (card.getHighestValue() + 2) * 4 + card.getShape();
    }
    else return (dynamic_cast<NumericCard &>(card).getNumber() -2)*4 + card.getShape() ;
}

//this method returns only the value of a card, without it shape
int Hand:: returnValueOfCard(Card &card){
    if (card.isFigureCard) {
        if (dynamic_cast<FigureCard &>(card).getFigure() == Jack) return (card.getHighestValue()+1);
        else if (dynamic_cast<FigureCard &>(card).getFigure() == Queen) return (card.getHighestValue()+2);
        else if (dynamic_cast<FigureCard &>(card).getFigure() == King) return (card.getHighestValue()+3);
        else return (card.getHighestValue()+4); //ace
    }
    else return  (dynamic_cast<NumericCard &>(card)).getNumber();  // numeric
}

//this method returns the key of a card which the player has the most of it
int Hand:: hasTheMostOf() {
    map<int, int>::reverse_iterator rit = mapCounter.rbegin();
    int maxKey = rit->first;
    int maxValue = rit->second;
    for (rit = mapCounter.rbegin() ; rit!= mapCounter.rend();rit++) {
        if (maxValue < rit->second) {
            maxValue = rit->second;
            maxKey = rit->first;
            if (maxValue == 3)
                return maxKey;
        }
    }
    return maxKey;
}

//this method returns the key of a card which the player has the least of it
int Hand:: hasTheLeastOf() {
    map<int, int>::iterator it = mapCounter.begin();
    int minKey = it->first;
    int minValue = it->second;
    for (it = mapCounter.begin() ; it!= mapCounter.end();it++) {
        if(minValue > it->second ) {
            minValue = it->second;
            minKey = it->first;
            if(minValue == 1)
                return minKey;
        }
    }
    return minKey;
}