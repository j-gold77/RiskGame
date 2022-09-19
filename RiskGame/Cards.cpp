/*
 Created by jgold on 2021-10-04.
 Assignment 1: Part 4 Cards.
 Class Comp 345 winter term 2021.
*/

/*
 * This is the Card cpp file which writes all the functionality of the declared methods in the Card.h file
 */

#include "Cards.h"
#include "Orders.h"
#include "Player.h"
#include <iostream>
#include <vector>
using namespace std;

///Card class begins here ..................................................


///card default constructor
Card ::Card() {
    cardType = nullptr;
    id = 0;
}

///card initializer constructor
Card ::Card(string newCardType, int newId) {
    cardType = newCardType;
    id = newId;

}


///returns card type
string Card::getCardType() const {

    return cardType;
}

///returns id for card
int Card::getId() const {

    return id;
}

/// =operator overload
Card& Card::operator=(const Card& card){
    this->cardType = card.cardType;
    this->id = card.id;
    return *this;
}
///copy constructor
Card::Card(const Card& card) {
    this->cardType = card.cardType;
    this->id = card.id;
}


///out stream overload for card object
ostream &operator<<(ostream &outs, const Card &theObject) {
    return outs <<"Id: "<< theObject.id<<" and name is: "<< theObject.cardType << endl;
}

///equal operator overloaded for card class
bool operator ==(const Card& card1, const Card& card2) {
    return (card1.cardType == card2.cardType && card1.id == card2.id);
}
///destructor for card
Card::~Card() {

}

///end of card class




///Deck class begins here...........................................


///deck default constructor
Deck :: Deck() {
    size =0;
}

///Deck initializer
Deck::Deck(vector<Card*> theCards,int thesize) {
    this->cards = theCards; ///creates object for vector of cards
    this->size=thesize;
}

///assignment operator overload
Deck &Deck::operator=(const Deck &deck) {
    this->cards = deck.cards;
    this->size=deck.size;
    return *this;
}

///copy constructor
Deck::Deck(const Deck &deck) : cards() {
    for (auto it = deck.cards.begin();
         it <deck.cards.end(); ++it) {
        cards.push_back(new Card(*(*it)));

    }
    this->size=cards.size();

}

///return size of deck
int Deck::getSize() const {
    return size;
}


///outstream for Deck
ostream& operator <<(ostream& outs, const Deck& theObject) {
    outs << "Deck contains " <<theObject.size<< " cards. They are:  "<< endl;
    for (int i=0; i<theObject.cards.size(); i++){
        outs << *theObject.cards[i];
    }
    return outs<<endl;
}

///shuffles the deck

void Deck::shuffle(vector<Card*> c) {

    cards = c;
    int N = cards.size();
    for (int j = N - 1; j > 0; --j) {
        int r = rand() % (j + 1);
        iter_swap(cards.begin() + r, cards.begin() + j);
    }

}

///drawing a card from the deck. returns a card and removes it from deck
Card Deck::draw() {
    Card *c;
    c= cards.back();
    cards.pop_back();
    size--;
    cout << "Card draw is: "<< *c;
    return *c;
}

///inserts a card back into the back of the deck
void Deck::insert(Card &c) {
    Card *card = new Card(c);
    cards.push_back(card);
    size++;
    cout <<"Card inserted back into deck is " << *card;
    cout << "Deck size is now " << size << endl;
    cout <<endl;

    delete card; ///deletes pointer to card
}



///destructor for cards. clears the vector of deck
Deck::~Deck() {


    ///deleting pointers of cards in the deck
    for (int i=0; i<cards.size(); i++)
    {
        delete cards[i];
    }

    /// vector for deck
    cards.clear();
}

///end of deck class




///Hand class begins here..................................................


///default hand constructor
Hand::Hand() {
    size = 0;
}

///initializer hand constructor
Hand::Hand(vector<Card*> newHand,int theSize) {
    this->theHand = newHand; ///creates new object for vector of cards in hand
    size = theSize;
}

///assignment operator overload
Hand &Hand::operator=(const Hand &hand) {
    this->theHand = hand.theHand;
    this->size = hand.size;
    return *this;
}

///copy constructor
Hand::Hand(const Hand &hand) : theHand() {
    for (auto it = hand.theHand.begin();
         it < hand.theHand.end(); ++it) {
        theHand.push_back(new Card(*(*it)));
        this->size = hand.size;
    }
}

///returns size of the hand
int Hand::getSize() const{
    return size;
}

///inserts a card from the deck into the hand
void Hand::insert(const Card &c) {
    setThehand(const_cast<Card &>(c));
}
///removes a card from the hand
void Hand::remove(const Card &c) {
    Card *card = new Card(c);
    for (int i=0; i<theHand.size(); i++){
        if (*theHand[i]==*card){
            swap(theHand[i],theHand.back());
            theHand.pop_back();
            size--;
            break;
        }
    }
    delete card; ///deletes pointer to card
}

///gets the first card in the hand

Card Hand::getCard () const {
    return *theHand.back();
}


///out stream overload for hand object
ostream& operator <<(ostream& outs, const Hand& theObject) {

    if (theObject.theHand.empty())
        outs << "The hand is empty"<<endl;
    else {
        outs << "The hand contains cards " << endl;

        for (int i = 0; i < theObject.theHand.size(); i++) {
            outs << *theObject.theHand[i];
        }
    }
    return outs<<endl;
}

///returns the hand vector
vector<Card *> const &Hand::getTheHand() const {
    return theHand;
}

///sets a card to the hand
void Hand::setThehand(Card &c) {
    theHand.push_back(&c);
    size++;
}

///Hand destructor
Hand::~Hand(){

    ///deleting pointers of cards in the hand
    for (int i=0; i<theHand.size(); i++)
    {
        delete theHand[i];
    }
    theHand.clear();
}





///end of hand class



///Bomb class child of Card begins here....................................

///Bomb card default constructor
BombCard ::BombCard() : Card() {
    name = nullptr;
    id = 1;
}

///Bomb card intializer constructor
BombCard::BombCard(string theName, int theId) : Card(theName,theId) {
    name = theName;
    id = theId;

}

/// =operator overload
BombCard& BombCard::operator=(const BombCard& card){
    Card::operator= (card);
    this->name = card.name;
    this->id = card.id;
    return *this;
}
///copy constructor
BombCard::BombCard(const BombCard& card) {
    this->name = card.name;
    this->id = card.id;
}

///play function of card. Takes in a card, the hand, the deck and the player playing the card.
///removes the card from the hand
///adds the card to the deck
///adds the bomb order to the players list of orders
//void BombCard::play(Card c, Hand &h, Deck &d,Player &p) {
//
//    Order *o = new Order("BombOrder");
//    p.addOrder(o);
//    delete o;
//    h.remove(c);
//    d.insert(c);
//    cout<< "You are now Bombing an enemies territory"<<endl;
//}


///out stream overload for Bomb card
ostream &operator<<(ostream &outs,const BombCard &theObject) {
    return outs <<"Id: "<< theObject.id<<" and name is: "<< theObject.name << endl;
}

///destructor for bomb card
BombCard::~BombCard(){}

///end of bomb class



///Reinforcement card child class of Card begins here.....................................


///Reinforcement card default constructor
ReinforcementCard ::ReinforcementCard() : Card() {
    name = nullptr;
    id = 2;
}

///Reinforcement card initializer constructor
ReinforcementCard::ReinforcementCard(string theName, int theId) : Card(theName,theId) {
    name = theName;
    id = theId;

}

/// =operator overload
ReinforcementCard& ReinforcementCard::operator=(const ReinforcementCard& card){
    Card::operator= (card);
    this->name = card.name;
    this->id = card.id;
    return *this;
}
///copy constructor
ReinforcementCard::ReinforcementCard(const ReinforcementCard& card) {
    this->name = card.name;
    this->id = card.id;
}

///play function of card. Takes in a card, the hand, the deck and the player playing the card.
///removes the card from the hand
///adds the card to the deck
///adds the reinforcement order to the players list of orders
//void ReinforcementCard::play(Card c, Hand &h, Deck &d,Player &p) {
//
//    Order *o = new Order("ReinforcementOrder");
//    p.addOrder(o);
//    delete o;
//    h.remove(c);
//    d.insert(c);
//    cout<< "You are now Reinforcing your Territory"<<endl;
//}

///out stream overload for Reinforcement card
ostream &operator<<(ostream &outs,const ReinforcementCard &theObject) {
    return outs <<"Id: "<< theObject.id<<" and name is: "<< theObject.name << endl;
}
///destructor for reinforcement card
ReinforcementCard::~ReinforcementCard() {}

bool operator==(const ReinforcementCard &card1, const ReinforcementCard &card2) {
    return (card1.name == card2.name);
}


///end of reinforcement class

///Blockade class child of card class begins here......................................................

///Blockade card default constructor
BlockadeCard ::BlockadeCard() : Card() {
    name = nullptr;
    id = 3;
}

///Blockade card initializer constructor
BlockadeCard::BlockadeCard(string theName, int theId) : Card(theName,theId) {
    name = theName;
    id = theId;

}

/// =operator overload
BlockadeCard& BlockadeCard::operator=(const BlockadeCard& card){
    this->name = card.name;
    this->id = card.id;
    return *this;
}
///copy constructor
BlockadeCard::BlockadeCard(const BlockadeCard& card) {
    Card::operator= (card);
    this->name = card.name;
    this->id = card.id;
}
/////play function of card. Takes in a card, the hand, the deck and the player playing the card.
/////removes the card from the hand
/////adds the card to the deck
/////adds the Blockade order to the players list of orders
//void BlockadeCard::play(Card c, Hand &h, Deck &d,Player &p) {
//
//    Order *o = new Order("BlockadeOrder");
//    p.addOrder(o);
//    delete o;
//    h.remove(c);
//    d.insert(c);
//    cout<< "You are now creating a blockade for an enemy Territory"<<endl;
//}

///out stream overload for Blockade card
ostream &operator<<(ostream &outs,const BlockadeCard &theObject) {
    return outs <<"Id: "<< theObject.id<<" and name is: "<< theObject.name << endl;
}

///destructor for blockade card
BlockadeCard::~BlockadeCard() {}

bool operator==(const BlockadeCard &card1, const BlockadeCard &card2) {
    return (card1.name == card2.name);
}

///end of blockade class



///Airlift class child of Card class begins here.........................................................



///Airlift card default constructor
AirliftCard::AirliftCard(): Card() {
    name = nullptr;
    id = 4;
}

///Airlift card initializer destructor
AirliftCard::AirliftCard(string theName, int theId) : Card(theName,theId) {
    name = theName;
    id = theId;

}

/// =operator overload
AirliftCard& AirliftCard::operator=(const AirliftCard& card){
    Card::operator= (card);
    this->name = card.name;
    this->id = card.id;
    return *this;
}
///copy constructor
AirliftCard::AirliftCard(const AirliftCard& card) {
    this->name = card.name;
    this->id = card.id;
}

///play function of card. Takes in a card, the hand, the deck and the player playing the card.
///removes the card from the hand
///adds the card to the deck
///adds the Blockade order to the players list of orders
//void AirliftCard::play(Card c, Hand &h, Deck &d,Player &p) {
//
//    Order *o = new Order("AirliftOrder");
//    p.addOrder(o);
//    delete o;
//    h.remove(c);
//    d.insert(c);
//    cout<< "You are now creating an Airlift for your troops"<<endl;
//}

///out stream overload for Air lift card
ostream &operator<<(ostream &outs,const AirliftCard &theObject) {
    return outs <<"Id: "<< theObject.id<<" and name is: "<< theObject.name << endl;
}

bool operator==(const AirliftCard &card1, const AirliftCard &card2) {


    return (card1.name == card2.name);
}

///destructor for Airlift card
AirliftCard::~AirliftCard() {}





///end of air lift class





///Diplomacy class child of Card class begins here...........................................

///Diplomacy card default constructor
DiplomacyCard::DiplomacyCard() : Card() {
    name = nullptr;
    id =5;
}

///Diplmacy card intializer constructor
DiplomacyCard::DiplomacyCard(string theName, int theId) : Card(theName,theId) {
    name = theName;
    id = theId;

}

/// =operator overload
DiplomacyCard& DiplomacyCard::operator=(const DiplomacyCard& card){
    Card::operator= (card);
    this->name = card.name;
    this->id = card.id;
    return *this;
}
///copy constructor
DiplomacyCard::DiplomacyCard(const DiplomacyCard& card) {
    this->name = card.name;
    this->id = card.id;
}

///play function of card. Takes in a card, the hand, the deck and the player playing the card.
///removes the card from the hand
///adds the card to the deck
///adds the Diplomacy order to the players list of orders
//void DiplomacyCard::play(Card c, Hand &h, Deck &d,Player &p) {
//
//    Order *o = new Order("DiplomacyOrder");
//    p.addOrder(o);
//    delete o;
//    h.remove(c);
//    d.insert(c);
//    cout<< "You are now creating a Diplomacy with an enemy territory"<<endl;
//}
///out stream overload for Diplomacy card
ostream &operator<<(ostream &outs,const DiplomacyCard &theObject) {
    return outs <<"Id: "<< theObject.id<<" and name is: "<< theObject.name << endl;
}

///destructor for diplomacy card
DiplomacyCard::~DiplomacyCard(){}

bool operator==(const DiplomacyCard &card1, const DiplomacyCard &card2) {
    return (card1.name == card2.name);
}

///end of diplomacy class

Territory::Territory() : id(0), territoryContinentId(0), army(0), name(" "), neighboursList(0), p(NULL)
{

}
//parameterized constructor
Territory::Territory(int idParam, string nameParam, int continentIdParam, int armyParam) : id(idParam), territoryContinentId(continentIdParam), army(armyParam), name(nameParam), neighboursList(0),p(new Player())
{

}
//copy constructor
Territory::Territory(const Territory& other)
{

    id = other.id;
    territoryContinentId = other.territoryContinentId;
    army = other.army;
    name = other.name;
    for (int i=0; i<neighboursList.size(); i++){
        neighboursList[i] = new Territory (*(other.neighboursList[i]));
    }
}

//territory destructor
Territory::~Territory()
{

}

// accessor methods
string Territory::getName()
{
    return name;
}

int Territory::getId()
{
    return id;
}

int Territory::getCId()
{
    return territoryContinentId;
}

int Territory::getArmy()
{
    return army;
}

vector<Territory*> Territory::getNeighboursList()
{
    return neighboursList;
}

//mutator methods
void Territory::setId(int id)
{
    this->id = id;
}

void Territory::setContinentId(int cId)
{
    this->territoryContinentId = cId;
}

void Territory::setArmy(int army)
{
    this->army = army;
}

void Territory::setName(string name)
{
    this->name = name;
}



// adds a pointer to a neighbours in teeritories list
void Territory::addNeighbours(Territory* t)
{
    neighboursList.push_back(t);
}

//displays said territories neighbours
void Territory::displayNeighbours()
{
    //cout << "DEBUG: TERRITORY CLASS, displayNeighbours() \n";
    cout << "neighbour list size: " << neighboursList.size() << "\n";

    for (int i = 0; i < neighboursList.size(); i++) {
        cout << "Border: " << *neighboursList[i] << "\n";
    }
    cout << "\n";

}
// assigment operators
Territory& Territory::operator = (const Territory& rhs)
{


    if (this != &rhs){


        id = rhs.id;
        territoryContinentId = rhs.territoryContinentId;
        army = rhs.army;
        name = rhs.name;

        // 	iterate through whols list of neighbours and copy each one to the new objects list of neighbours
        for (int i = 0; i < rhs.neighboursList.size(); i++) {
            *neighboursList[i] = *rhs.neighboursList[i];
        }
    }
    return *this;

}
// territory extraction operator
std::ostream& operator<<(std::ostream& strm, const Territory& t) {
   return strm << "Territory: (name: " << t.name << ", id: " << t.id << ", continent id: " << t.territoryContinentId <<  ", Army size: "<< t.army<<")" << endl;

}

//territory insurtion operator
istream& operator>>(istream& ins, Territory& t)
{
    ins >> t.id >> t.name >> t.army >> t.territoryContinentId;
    return ins;
}

bool operator==(const Territory &t1, const Territory &t2){
    return (t1.territoryContinentId==t2.territoryContinentId
            && t1.id == t2.id
            && t1.name == t2.name);
}

bool Territory::validationOfNeighbours(Territory &t1, Territory &t2) {
    for(int i=0; i<t1.getNeighboursList().size(); i++){
        for (int j=0; j<t2.getNeighboursList().size(); j++){
            if (t1.getNeighboursList()[i]==t2.getNeighboursList()[j]){
                return true;
            }
        }
    }
    return false;
}

void Territory::addArmy(int x) {
    this->army = army + x;

}

void Territory::removeArmy(int x) {
    if (army-x < 0)
        army = 0;
    else
        this->army = army - x;
}

bool Territory::sort_funct(const Territory &t, const Territory &other) {
        return (t.army<other.army);
}

void Territory::setPlayer(Player *player) {
    this->p = player;
}

Player* Territory::getPlayer() {
    return p;
}

//void Territory::sort(vector<Territory *> &t) {
//    sort(t.begin(),t.end(),sort_funct)
//
//}





