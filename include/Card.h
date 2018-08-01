#ifndef CARD_H_
#define CARD_H_

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

enum Shape {
    Club ,
    Diamond,
    Heart,
    Spade
};

enum Figure {
    Jack ,
    Queen,
    King,
    Ace
};

class Card {
private:
    Shape shape;

public:
    int highestValue;
    Card(Shape shape , int highestValue, bool isFigureCard);
    Shape getShape() const;
    int getHighestValue() const;
    void setShape(Shape OtherShape);
    void setHighestValue(int OtherHighestValue);
    virtual string toString() = 0; //Returns the string representation of the card "<value><shape>" exp: "12S" or "QD"
    virtual ~Card(); //destructor
    bool isFigureCard;

};

class FigureCard : public Card {
private:
    Figure figure;
public:
    FigureCard(Figure figure, Shape shape, int highestValue, bool isFigureCard); //constructor
    FigureCard(const FigureCard &otherFigureCard); //copy constructor
    Figure getFigure() const ;
    FigureCard& operator=(const FigureCard &otherFigureCard); //Assignment operator
    virtual string toString() override;
    virtual ~FigureCard();
    
};

class NumericCard : public Card {
private:
    int number;
public:
    int getNumber() const ;
    NumericCard(int number, Shape shape, int highestValue, bool isFigureCard); //constructor
    NumericCard(const NumericCard &otherNumericCard); //copy constructor
    NumericCard& operator=(const NumericCard &otherNumericCard); //Assignment operator
    virtual string toString() override;
    virtual ~NumericCard();

};

#endif