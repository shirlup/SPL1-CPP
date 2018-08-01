#include "Player.h"


//Constructor
Player::Player(string name,int strategy):name(name),strategy(strategy) {}

//Copy Constructor
Player::Player(const Player &otherPlayer):Hand(otherPlayer),name(otherPlayer.getName()),strategy(otherPlayer.strategy){}

//Assignment operator
Player& Player::operator=(const Player &otherPlayer){
    if (this != &otherPlayer)
    {
        Hand::operator=(otherPlayer);
    }
    return *this;
}

//destructor
Player::~Player() {}

string Player:: getName() const {
    return name;
}

//this method gets a reference to a card and returns a vector of card with the same value
vector<Card*> Player::Search(Card& card){
  
    int number;
    int n = card.getHighestValue();
    vector<Card*> vecToReturn;
    map<int, Card*>::iterator it ;
    if (card.isFigureCard) {

        if (dynamic_cast<FigureCard &>(card).getFigure() == Jack) number = n + 1;
        else if (dynamic_cast<FigureCard &>(card).getFigure() == Queen) number = n + 2;
        else if (dynamic_cast<FigureCard &>(card).getFigure() == King) number = n + 3;
        else number =  n + 4; //ace
    }
    else {
        number = (dynamic_cast<NumericCard &>(card)).getNumber();  // numeric

    }
    for(int i = 1 ; i < 5  ; i++){
        it = mapOfCards.find((number-1)*4-i);
        if (it != mapOfCards.end() ){//means we found card{
            vecToReturn.push_back(it->second);
        } //if
    }
    return vecToReturn;
}
/*this method returns the number of cards the answering player gave to the asking player,
 * in addition it takes care of adding and removing cards */
unsigned int Player::answerToPlayer(Player* player ,Card* card ){
    vector<Card*> auxVec = Search(*card);
    int size = auxVec.size();
    if( !(auxVec.empty())) {

        for (unsigned int i = 0 ; i < auxVec.size() ; i++){

            removeCard(*auxVec.at(i));
            player->addCard(*auxVec.at(i));
            

        }
    }
    return size;

}

/*this methond examens all the other players strategies and returns a card the player should ask from another player
according to his strategy*/
Card* Player :: cardToAsk (int strategy){
    Card* toAsk ;
    map<int, Card*>::iterator iter;
    map<int, Card*>::reverse_iterator rit;
    bool stopSearching = false;
    switch(strategy){
        case 1: // ask the card he has the most with highest value
            for( int i = 0; (i < 4) && (!(stopSearching)) ; i++ ) {
                if(mapOfCards.find(((hasTheMostOf() -2)*4)+i) != mapOfCards.end()) {
                    toAsk = mapOfCards[((hasTheMostOf() - 2) * 4) + i];
                    stopSearching = true;
                }
            }
            break;
        case 2: // ask the card he has the most with lowest value

            for( int i = 0; (i < 4) && !stopSearching ; i++ ) {
                if(mapOfCards.find(((hasTheLeastOf() -2)*4)+i) != mapOfCards.end()) {
                    toAsk = mapOfCards[((hasTheLeastOf() - 2) * 4) + i];
                    stopSearching = true;
                }
            }
            break;
        case 3:
            rit = mapOfCards.rbegin();
            toAsk = rit->second;
            break;
        default:
            iter = mapOfCards.begin();
            toAsk = iter->second;
    }

    return toAsk;
}

//Constructor player type 1
PlayerType1::PlayerType1(string name,int strategy): Player::Player(name,strategy){
    
}

//copy constructor player type 1
PlayerType1::PlayerType1(const PlayerType1 &otherPlayer1): Player::Player(otherPlayer1){

}

//assignment operator player type 1
PlayerType1& PlayerType1 :: operator=(const PlayerType1 &otherPlayer1){
    if (this != &otherPlayer1){
        Player:: operator=(otherPlayer1);
        this->strategy = otherPlayer1.strategy;
    }
    return *this;
}

//Player type 1 ask a card from another player
unsigned int PlayerType1:: askFromPlayer(Player* player){

    return player->answerToPlayer(this,cardToAsk(1));
}

//destructor
PlayerType1::~PlayerType1(){}

//Constructor player type 2
PlayerType2::PlayerType2(string name,int strategy): Player::Player(name,strategy){}

//copy constructor player type 2
PlayerType2::PlayerType2(const PlayerType2 &otherPlayer2): Player::Player(otherPlayer2){}

//assignment operator player type 2
PlayerType2& PlayerType2 :: operator=(const PlayerType2 &otherPlayer2){
    if (this != &otherPlayer2){
        Player:: operator=(otherPlayer2);
        this->strategy = otherPlayer2.strategy;
    }
    return *this;
}

//player type 2 ask for a card from another player
unsigned int PlayerType2:: askFromPlayer(Player* player){
  return player->answerToPlayer(this,cardToAsk(2));
}
//destructor
PlayerType2::~PlayerType2(){}

//Constructor player type 3
PlayerType3::PlayerType3(string name,int strategy,int counter): Player::Player(name,strategy),counter(counter){
    
}
//copy constructor player type 3
PlayerType3::PlayerType3(const PlayerType3 &otherPlayer3): Player::Player(otherPlayer3),counter(otherPlayer3.counter){}

//assignment operator player type 3
PlayerType3& PlayerType3 :: operator=(const PlayerType3 &otherPlayer3){
    if (this != &otherPlayer3){
        Player:: operator=(otherPlayer3);
        this->strategy = otherPlayer3.strategy;
        this->counter = otherPlayer3.counter;
    }
    return *this;
}

//player type 3 ask for a card from another player
unsigned int PlayerType3:: askFromPlayer(Player* player){
   return player->answerToPlayer(this,cardToAsk(3));
}

//destructor
PlayerType3::~PlayerType3(){}

//Constructor player type 4
PlayerType4::PlayerType4(string name,int strategy,int counter): Player::Player(name,strategy),counter(0){
    
}

//copy constructor player type 4
PlayerType4::PlayerType4(const PlayerType4 &otherPlayer4): Player::Player(otherPlayer4),counter(otherPlayer4.counter){}

//assignment operator player type 4
PlayerType4& PlayerType4 :: operator=(const PlayerType4 &otherPlayer4){
    if (this != &otherPlayer4){
        Player:: operator=(otherPlayer4);
        this->strategy = otherPlayer4.strategy;
        this->counter = otherPlayer4.counter;
    }
    return *this;
}

//player type 4 ask for a card from another player
unsigned int PlayerType4:: askFromPlayer(Player* player){
    return player->answerToPlayer(this,cardToAsk(4));
}

//destructor
PlayerType4::~PlayerType4(){}