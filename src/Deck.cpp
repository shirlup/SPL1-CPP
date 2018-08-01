#include "Deck.h"

//Empty Constructor
Deck::Deck(): vecDeck(){}

//constructor
Deck::Deck(string ofCards, int highestValue) : vecDeck() {
    vector<string> auxVec; //creating auxiliary  vec

    //divide input string to strings
    for(unsigned int i = 0 ; i < ofCards.length() ; i++){
        string s = ""; //create string on stack
        while(i < ofCards.length() && ofCards.at(i) != ' ' ){
            s += ofCards.at(i);
            i++;
        }
        auxVec.push_back(s);
    }
    //go over auxVec to create cards to be
    for(unsigned i = 0 ; i < auxVec.size() ; i++ ){
        string oneCard = auxVec[i]; //refer to the string that auxVec[i] points
        //auxVec.erase(auxVe);
        string leftVal = oneCard.substr(0,oneCard.length() -1 ); // maybe -2 ?
        char rightVal = oneCard.at( oneCard.length() -1 );
        int number = 0;
        Figure figure;
        Shape shape;
        if( leftVal == "J"||leftVal == "Q"|| leftVal == "K"|| leftVal == "A"){
            if(leftVal == "J") figure = Jack;
            else if (leftVal == "Q") figure = Queen;
            else if (leftVal == "K") figure = King;
            else figure = Ace;
        }
        else number = atoi(leftVal.c_str());
        if(rightVal == 'D') shape = Diamond;
        else if (rightVal == 'C') shape = Club;
        else if (rightVal == 'H') shape = Heart;
        else shape = Spade;
        //Card* toAdd;
        if( number != 0 ) {
            NumericCard * toAdd = new NumericCard(number, shape,highestValue,false);
            vecDeck.push_back(toAdd);
        }
        else {
            FigureCard * toAdd = new FigureCard(figure, shape, highestValue,true);
            vecDeck.push_back(toAdd);
        }

    }
}
//Copy Constructor
Deck::Deck(const Deck &otherDeck):vecDeck() {
    for(unsigned int i = 0 ; i < otherDeck.vecDeck.size() ; i++ ){
        if (otherDeck.vecDeck.at(i)->isFigureCard ) {
            this->vecDeck.push_back(new FigureCard(dynamic_cast<FigureCard &>(*otherDeck.vecDeck[i])));
        }
        else
            this->vecDeck.push_back(new NumericCard(dynamic_cast<NumericCard &>(*otherDeck.vecDeck[i])));
    }
}

//assignment operator
Deck& Deck :: operator=(const Deck &otherDeck){
    //cout<< "assignment operator Deck" <<endl;
    
      if (this != &otherDeck){
    for (unsigned int i = 0; i < this->vecDeck.size(); i++) {
       
        delete this->vecDeck[i];
        
    }
    this->vecDeck.clear();
    //  cout << vecDeck.size() << endl;

        for(unsigned int i = 0 ; i<otherDeck.vecDeck.size() ; i++ ){
            if (otherDeck.vecDeck.at(i)->isFigureCard ){
                this->vecDeck.push_back (new FigureCard(dynamic_cast<FigureCard &>(*otherDeck.vecDeck[i])));
                //delete(otherDeck.vecDeck[i]);
            }
                else{
                this->vecDeck.push_back(new NumericCard(dynamic_cast<NumericCard &>(*otherDeck.vecDeck[i])));
                //otherDeck.vecDeck.clean();
                }
            //delete (Card*)vecDeck[i];
        }
      } 
       
        return *this;
    }


//Returns the top card of the deck and removes it from the deck
Card* Deck::fetchCard() {
    if (!vecDeck.empty()) {
        Card *tempCard = vecDeck.at(0);
        vecDeck.erase(vecDeck.begin());
        return tempCard;
    }
    else return nullptr;
}
//destructor
Deck::~Deck() {
    
    for (unsigned int i = 0; i < vecDeck.size(); i++) {
       
        delete vecDeck[i];
        
    }
     vecDeck.clear();
    //  cout << vecDeck.size() << endl;
}
// Get the number of cards in the deck
int Deck::getNumberOfCards() {
    return vecDeck.size();
}
// Return the cards in top-to-bottom order in a single line, cards are separated by a space ex: "12S QD AS 3H"
string Deck:: toString(){
    ostringstream ss;
    ss << this->getNumberOfCards();
    string numberOfCards = ss.str() + " ";
    string str = "" ;
    for(unsigned int i = 0; i < vecDeck.size() ; i++ )
        if(i != vecDeck.size()-1)
            str += vecDeck[i]->toString()+ " ";
        else str+= vecDeck[i]->toString();
    return str;
}