#ifndef GAME_H_
#define GAME_H_
#include <fstream>
#include <iostream>
#include "Player.h"
#include "Deck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include<sstream>
using namespace std;
class Game {
private:
    vector<Player *> players;  //The list of the players
    Deck deck;                 //The deck of the game
    int highestValue;
    void addToOtherPlayer(Player* otherPlayer,unsigned int numberToAdd);
    void toDoNext(Player* currPlayer ,Player* otherPlayer, unsigned int numberToAdd);
public:
    int numberOfWinners;
    string verbal;
    int turns;
    bool gameIsOver;
    string winner;
    string winner2;
    Game(const Game &otherGame); // copy constructor
    Game& operator=(const Game &otherGame) ;// assignment operator
    Game(char* configurationFile); //constructor
    virtual ~Game(); //destructor
    void init();
    void play();
    void printState();        //Print the state of the game as described in the assignment.
    void printWinner();       //Print the winner of the game as describe in the assignment.
    void printNumberOfTurns(); //Print the number of played turns at any given time.
    Player* getPlayerWithMostNumberOfCards(Player *mePlay);
    Player* getPlayerWithLeastNumberOfCards(Player *mePlay);
};
#endif