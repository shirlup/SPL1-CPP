#include "Card.h"
using namespace std;

//Constructor
Card::Card(Shape shape , int highestValue, bool isFigureCard):shape(shape), highestValue(highestValue),isFigureCard(isFigureCard){}

//Getter
Shape Card:: getShape()const {
    return shape;
}

//getter
int Card:: getHighestValue() const{
    return highestValue;
}

//Setter
void Card:: setShape(Shape OtherShape){
    shape = OtherShape;
}

//Setter
void Card:: setHighestValue(int OtherHighestValue){
    highestValue = highestValue;
}

//destructor
Card::~Card() {}

//Constructor
FigureCard::FigureCard(Figure figure, Shape shape, int highestValue, bool isFigureCard): Card::Card(shape,highestValue,isFigureCard), figure(figure){
    
}

//Copy Constructor
FigureCard::FigureCard(const FigureCard &otherFigureCard): Card(otherFigureCard),figure(otherFigureCard.getFigure()) {
}

//assignment operator
FigureCard& FigureCard::operator=(const FigureCard &otherFigureCard){
    if (this != &otherFigureCard)
    {
        figure = otherFigureCard.getFigure();
        this->setShape(otherFigureCard.getShape());
        this->setHighestValue(otherFigureCard.getHighestValue());
        isFigureCard = true;
    }
    return *this;
}

//Getter
Figure FigureCard::getFigure() const {
    return figure;
}

//destructor
FigureCard::~FigureCard() {}
//toString
string FigureCard::toString(){
    string str = "";
    switch(getFigure()){
        case Jack:
            str+= "J";
            break;
        case Queen:
            str+= "Q";
            break;
        case King:
            str+= "K";
            break;
        default:
            str+= "A";
    }
    switch(getShape()){
        case Club:
            str+= "C";
            break;
        case Diamond:
            str+= "D";
            break;
        case Heart:
            str+= "H";
            break;
        default:
            str+= "S";
            break;
    }
    return str;
}

//Constructor
NumericCard::NumericCard(int number, Shape shape, int highestValue, bool isFigureCard): Card::Card(shape, highestValue,isFigureCard) , number(number){
    
}

//Copy Constructor
NumericCard::NumericCard(const NumericCard &otherNumericCard): Card(otherNumericCard),number(otherNumericCard.getNumber()) {}

//assignment operator
NumericCard& NumericCard::operator=(const NumericCard &otherNumericCard){
    if (this != &otherNumericCard)
    {
        number = otherNumericCard.getNumber();
        this->setShape(otherNumericCard.getShape());
        this->setHighestValue(otherNumericCard.getHighestValue());
        isFigureCard = true;
    }
    return *this;
}

//destructor
NumericCard::~NumericCard() {}
int NumericCard::getNumber()const {
    return number;
}

//toString
string  NumericCard:: toString() {
    ostringstream ss;
    ss << number;
    string str = ss.str();
    switch (getShape()) {
        case Club:
            str += "C";
            break;
        case Diamond:
            str += "D";
            break;
        case Heart:
            str += "H";
            break;
        default:
            str += "S";
            break;
    }
    return str;
}