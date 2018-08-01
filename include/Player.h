#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include "Hand.h"
#include <vector>
#include "Card.h"
#include "Deck.h"
using namespace std;
class Player : public Hand {
private:
    const string name;
public:
    int strategy; 
    Player(string name, int strategy); //constructor
    virtual ~Player(); //destructor
    Player(const Player &otherPlayer); //copy constructor
    Player& operator=(const Player &otherPlayer); //Assignment operator
    string getName() const ;   //Returns the name of the player
    vector<Card*> Search(Card& card);
    Card* cardToAsk (int strategy);
    unsigned int answerToPlayer(Player* player,Card* card );
private:
};
class PlayerType1 : public Player { //For strategy 1
public:
    PlayerType1(string name,int strategy);//constructor
    PlayerType1(const PlayerType1 &otherPlayer1);//copy constructor
    PlayerType1& operator=(const PlayerType1 &otherPlayer1);//assignment operator
    Player* playerToAsk();
    unsigned int askFromPlayer(Player* player);
    virtual ~PlayerType1(); //destructor
};
class PlayerType2 : public Player {  //For strategy 2
public:
    PlayerType2(string name,int strategy);
    PlayerType2(const PlayerType2 &otherPlayer2);//copy constructor
    PlayerType2& operator=(const PlayerType2 &otherPlayer2);//assignment operator
    Player* playerToAsk();
    unsigned int askFromPlayer(Player* player);
    virtual ~PlayerType2(); //destructor
};
class PlayerType3 : public Player {  //For strategy 3
public:
    int counter;
    PlayerType3(string name,int strategy,int counter);
    PlayerType3(const PlayerType3 &otherPlayer3);//copy constructor
    PlayerType3& operator=(const PlayerType3 &otherPlayer3);//assignment operator
    Player* playerToAsk();
    unsigned int askFromPlayer(Player* player);
    virtual ~PlayerType3(); //destructor
};
class PlayerType4 : public Player {  //For strategy 4
public:
    int counter;
    PlayerType4(string name,int strategy,int counter);
    PlayerType4(const PlayerType4 &otherPlayer4);//copy constructor
    PlayerType4& operator=(const PlayerType4 &otherPlayer4);//assignment operator
    Player* playerToAsk();
    unsigned int askFromPlayer(Player* player);
    virtual ~PlayerType4(); //destructor
};
#endif