#include "Game.h"
//Constructor
Game::Game(char *configurationFile):players(), deck(),highestValue(0),numberOfWinners(0),verbal(""),turns(0) ,gameIsOver(false),winner(""), winner2("") {

    int numLine = 0;
    string configFile = configurationFile;
    string currLine = "";
    ifstream input_file(configFile);
    gameIsOver = false;
    int playerType;
    string playerName;

    if (input_file.is_open()){
        while(getline(input_file,currLine)){

            if ((currLine != "") && (currLine.at(0)!='#')){
                numLine++;
                switch (numLine){
                    case 1:
                        verbal = currLine;
                        break;
                    case 2:
                        highestValue= atoi(currLine.c_str());
                        break;
                    case 3:
                        deck = Deck(currLine, highestValue);
                        break;
                    default:
                        playerType = currLine.back() - 48;
                        playerName = currLine.substr(0, currLine.size() - 2);
                        switch (playerType){
                            case 1: players.push_back(new PlayerType1(playerName,1));
                                break;
                            case 2: players.push_back(new PlayerType2(playerName,2));
                                break;
                            case 3: players.push_back(new PlayerType3(playerName,3,0));
                                break;
                            default: players.push_back(new PlayerType4(playerName,4,0));
                        }

                }
            }
        }

    }

}

//copy constructor
Game::Game(const Game &otherGame):players(), deck(Deck(otherGame.deck)),highestValue(otherGame.highestValue),numberOfWinners(otherGame.numberOfWinners),verbal(otherGame.verbal),turns(otherGame.turns) ,gameIsOver(otherGame.gameIsOver),winner(otherGame.winner), winner2(otherGame.winner2){

    for(unsigned int i = 0 ; i < otherGame.players.size() ; i++) {

        Player *playerToInsert = otherGame.players.at(i);
        switch(playerToInsert->strategy){
      
            case 1: players.push_back(new PlayerType1(dynamic_cast<PlayerType1 &> (*playerToInsert)));
                break;
            case 2: players.push_back(new PlayerType2(dynamic_cast<PlayerType2 &> (*playerToInsert)));
                break;
            case 3: players.push_back(new PlayerType3(dynamic_cast<PlayerType3 &> (*playerToInsert)));
                break;
            default: players.push_back(new PlayerType4(dynamic_cast<PlayerType4 &> (*playerToInsert)));
        }
    }
}

//Assignment operator
Game& Game::operator=(const Game &otherGame){

    if (this != &otherGame)
    {
        for(unsigned int i = 0 ; i < otherGame.players.size() ; i++ ){
            switch(otherGame.players[i]->strategy){
                case 1:this->players.push_back(new Player(dynamic_cast<PlayerType1 &>(*otherGame.players[i])));
                    break;
                case 2:this->players.push_back(new Player(dynamic_cast<PlayerType2 &>(*otherGame.players[i])));
                    break;
                case 3:this->players.push_back(new Player(dynamic_cast<PlayerType3 &>(*otherGame.players[i])));
                    break;
                default:this->players.push_back(new Player(dynamic_cast<PlayerType4 &>(*otherGame.players[i])));
            }
        }
        
        verbal = otherGame.verbal;
        highestValue = otherGame.highestValue;
        turns = otherGame.turns;
        gameIsOver = otherGame.gameIsOver;
        string winner = otherGame. winner;
        string winner2 = otherGame.winner2;
    }
    return *this;
}

//destructor
Game::~Game() {
    for (unsigned int i = 0; i < players.size(); i++){
        delete players[i];
}
    players.clear();
}


//Return the Player with the highest number of cards
Player* Game::getPlayerWithMostNumberOfCards(Player *mePlay){
    int maxNumOfCards = 0;
    Player *maxPlayer;
    for(unsigned int i = 0 ; i < players.size() ; i++){
        if ((maxNumOfCards <= players[i]->getNumberOfCards()) && (players[i] != mePlay) ) {
            maxNumOfCards = players[i]->getNumberOfCards();
            maxPlayer = players[i];
        }
    }
    return maxPlayer;
}

//This method applys the init of the game, each member of the game gets seven cards
void Game::init(){
    for(unsigned int i = 0 ; i < players.size() ; i++ ){
        for(unsigned int j = 0 ; j < 7 ; j++ ) {
            Card *toAdd = deck.fetchCard();
            players[i]->addCard(*toAdd);
        }
    }
}

//This method runs the game
void Game::play(){

    unsigned  int i;
    unsigned  int j;
    unsigned int k;
    while (!(gameIsOver)){
        i = turns%players.size();
        
       
        turns++;
        
        if (verbal == "1" ) {
            cout << " " << endl;
            cout << "Turn " << turns << endl;
            this->printState();
        }

        Player &player = *players.at(i);
        Player* playerToAsk ;
        Card* cardAsk;
        string cardAskToString;
        unsigned int answerFromPlayer;

        switch (players.at(i)->strategy){
            case 1:
            //player number one asks the player who has the most cards if he has a spacific value of card
                playerToAsk = getPlayerWithMostNumberOfCards(&player);
                cardAsk = player.cardToAsk(1);
                cardAskToString = cardAsk->toString();
                answerFromPlayer = dynamic_cast<PlayerType1 &>(player).askFromPlayer(playerToAsk);

                if((answerFromPlayer > 0) || (playerToAsk->mapOfCards.size() == 0) )
                    toDoNext(&player,playerToAsk,answerFromPlayer);

                break;

            case 2:
            //player number two asks the player who has the most cards if he has a spacific value of card
                playerToAsk = getPlayerWithMostNumberOfCards(&player);
                cardAsk = player.cardToAsk(2);
                cardAskToString = cardAsk->toString();
                answerFromPlayer = dynamic_cast<PlayerType2 &>(player).askFromPlayer(playerToAsk);
                if((answerFromPlayer > 0) || (playerToAsk->mapOfCards.size() == 0) )
                        toDoNext(&player,playerToAsk,answerFromPlayer);
                break;
            case 3:
            //player number three asks the other players in order of input if he has a spacific value of card
                j = (dynamic_cast<PlayerType3 &>(player).counter)%players.size();
                cardAsk = player.cardToAsk(3);
                cardAskToString = cardAsk->toString();
                //as means the player doesnt ask himself
                if(i != j) {
                    playerToAsk = players.at(j);
                    answerFromPlayer = dynamic_cast<PlayerType3 &>(player).askFromPlayer(playerToAsk);
                    dynamic_cast<PlayerType3 &>(player).counter++;
                    if((answerFromPlayer > 0) || (playerToAsk->mapOfCards.size() == 0) )
                         toDoNext(&player, playerToAsk, answerFromPlayer);
                }
                else {
                //this section take care that player number three will ask the right player
                    playerToAsk = players[(j+1)%(players.size())];
                    answerFromPlayer = dynamic_cast<PlayerType3 &>(player).askFromPlayer(playerToAsk);
                    dynamic_cast<PlayerType3 &>(player).counter = dynamic_cast<PlayerType3 &>(player).counter + 2;
                    if((answerFromPlayer > 0) || (playerToAsk->mapOfCards.size() == 0) )
                        toDoNext(&player,playerToAsk,answerFromPlayer);
                }
                break;
            default:
            //player number four asks the other players in order of input if he has a specific value of card
                k = (dynamic_cast<PlayerType4 &>(player).counter)%players.size();
                cardAsk = player.cardToAsk(4);
                cardAskToString = cardAsk->toString();
                if(i != k){
                 //as means the player doesnt ask himself
                    playerToAsk = players.at(k);
                    answerFromPlayer = dynamic_cast<PlayerType4 &>(player).askFromPlayer(playerToAsk);
                    dynamic_cast<PlayerType4 &>(player).counter++;
                    if((answerFromPlayer > 0) || (playerToAsk->mapOfCards.size() == 0) )
                        toDoNext(&player,playerToAsk,answerFromPlayer);
                }
                else{
                //this section take care that player number three will ask the right player
                    playerToAsk = players[(k+1)%(players.size())];
                    answerFromPlayer = dynamic_cast<PlayerType4 &>(player).askFromPlayer(playerToAsk);
                    dynamic_cast<PlayerType4 &>(player).counter = dynamic_cast<PlayerType4 &>(player).counter + 2;
                    if((answerFromPlayer > 0) || (playerToAsk->mapOfCards.size() == 0) )
                        toDoNext(&player,playerToAsk,answerFromPlayer);
                }
        }
        
        //means the other player doesnt have the card which the current player asked him
        if(answerFromPlayer == 0 ) {
            if(deck.getNumberOfCards() > 0 ) {
                Card *toAdd = deck.fetchCard();
                player.addCard(*toAdd);
            }
        }
        
        //prints in every single turn the name of the player which card he asked and from who he asked
        if (verbal == "1" ) {
            cout << player.getName() << " asked " << playerToAsk->getName() << " for the value " << cardAskToString.substr(0,cardAskToString.length()-1)           << endl;
        }
        i++;
    }
 
}

//in this method the other player takes cards from the deck, if it has cards in it
void Game:: addToOtherPlayer(Player* otherPlayer, unsigned int numberToAdd){

    for(unsigned int x = 0 ; x < numberToAdd && (deck.getNumberOfCards() > 0 ) ; x++){
        Card* toAddToHim = deck.fetchCard();
        otherPlayer->addCard(*toAddToHim);
    }
}

//after the other player answers the currnt player there are several steps he need to do next
void Game:: toDoNext(Player* currPlayer ,Player* otherPlayer, unsigned int numberToAdd){

    //if the number of cards the other player gave to the current player if greater then zero
    if(numberToAdd > 0 ) {
        addToOtherPlayer(otherPlayer, numberToAdd);
        //checks if the current player has cards in his pile, if he has not than he is declared as the winner
        if (currPlayer->mapOfCards.size() == 0) {
            winner2 += currPlayer->getName();
            numberOfWinners++;
            }
            //checks if after all the other player "fetch card" moves he has cards in his pile, if not then there are two winners
            if(otherPlayer->mapOfCards.size() == 0 ) {
                numberOfWinners = numberOfWinners + 1;
                winner += otherPlayer->getName();
            }
        
    }
    //if the number of cards the other player gave to the currnt player is zero
    else {
    
    //declare the other player as the winner
        winner += otherPlayer->getName();
        numberOfWinners++;
        //checks if the current player has cards as well
        if (currPlayer->mapOfCards.size() == 0){
            winner2 += currPlayer->getName();
            numberOfWinners++;
        }

    }
    
    //declares when the game is OVER
    if(numberOfWinners > 0)
        gameIsOver = true;
}
//Print the state of the game as described in the assignment.
void Game::printState(){
    cout << "Deck: " << deck.toString() << endl;
    for(unsigned int i = 0 ; i < players.size() ; i++ ){
        cout << players[i]->getName() << ": " << players[i]->toString() << endl;
    }
}
//Print the winner of the game as describe in the assignment.
void Game::printWinner(){
    if (numberOfWinners == 1){
        cout << "*** The Winner is: " << winner2 << winner << " ***" << endl;
    }
    else {
        cout << "*** The winners are: " << winner << " and " << winner2 << " ***" << endl;
    }
}
//Print the number of played turns at any given time.
void Game::printNumberOfTurns(){
    cout << "Number of turns:"<< this->turns << endl;
}