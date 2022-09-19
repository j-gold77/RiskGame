

#ifndef RISKGAME_CARDS_H
#define RISKGAME_CARDS_H

/*
 Created by jgold on 2021-10-04.
 Assignment 1: Part 4 Cards.
 Class Comp 345 winter term 2021.
*/

/*
 * This is the Card h file that will declare all classes and member functions to be used in the Card.cpp file
 */


#include <iostream>
#include <vector>
using namespace std;

///Card class
class Player;
class Card{
public:
    Card(); ///default constructor
    Card(string CardType, int id); ///intiializer
    Card(const Card &card); /// copy constructor
    Card& operator =(const Card& e); ///assignment overload
    string getCardType () const; ///gets the card
    int getId () const; ///gets the id
    ~Card(); ///destructor
    friend ostream& operator <<(ostream& outs, const Card& theObject); ///instream overload
    friend bool operator ==(const Card& card1,
                            const Card& card2); ///equal overload

private:
    string cardType; ///name of the card
    int id; ///id of the card
};

//Hand class
class Hand{

public:
    Hand(); ///default construcot
    Hand(vector<Card*> theHand,int size); ///initializer
    Hand(const Hand &hand); //copy constructor
    Hand& operator =(const Hand& hand); ///assignment overload
    void insert(const Card &c); ///inserts a card into the deck
    void remove(const Card &c); ///removes a card from the deck
    void setThehand(Card &c); ///sets a card into the hand. similar to the inser function
    int getSize() const; ///returns size of the hand
    Card getCard() const; ///returns the front card fo the hand
    vector<Card*> const &getTheHand () const; ///returns the hand
    friend ostream &operator<<(ostream &outs, const Hand &theObject); ///instream overload
    ~Hand(); ///destructor


private:
    vector<Card*> theHand; ///cards in the hand
    int size; ///size of the hand

};


//Deck class
class Deck {
public:
    Deck(); ///constructr
    Deck(vector <Card*> cards,int size); ///intiializer
    Deck& operator =(const Deck& deck); ///assignment overload
    Deck(const Deck &cards); ///copy constructor
    int getSize() const; ///returns the size of the deck
    void shuffle(vector<Card*> cards); ///shuffles the cards in the deck
    void insert(Card &c); ///inserts a card to the back of the deck
    Card draw(); ///draws a card
    ~Deck(); ///destructor
    friend ostream &operator<<(ostream &outs, const Deck &theObject); ///instream overload

private:
    vector<Card*> cards; ///vector of card classes
    int size; ///size of the deck

};



//Bomb card class which is a card
class BombCard : public Card{
public:
    BombCard(); ///constructor
    BombCard(string name,  int id); ///intiializer
    BombCard(const BombCard &card); ///copy
    BombCard& operator =(const BombCard& e); ///assignment overload
    void play(Card b, Hand &h, Deck &d,Player &p); ///players a card and creates an order
    friend ostream &operator<<(ostream &outs, const BombCard &theObject); ///instream overload
    ~BombCard(); ///destructor




private:
    string name;
    int id;
};

//Reinforcement card class which is a card
class ReinforcementCard : public Card{
public:
    ReinforcementCard(); ///intiializer
    ReinforcementCard(string name,  int id);
    ReinforcementCard(const ReinforcementCard &card);
    ReinforcementCard& operator =(const ReinforcementCard& e);
    void play(Card c, Hand &h, Deck &d, Player &p);
    ~ReinforcementCard();
    friend ostream &operator<<(ostream &outs, const ReinforcementCard &theObject);
    friend bool operator ==(const ReinforcementCard& card1,
                            const ReinforcementCard& card2); ///equal overload



private:
    string name;
    int id;


};

//Blockade card class which is a card
class BlockadeCard : public Card {
public:
    BlockadeCard();
    BlockadeCard(string name, int id);
    BlockadeCard(const BlockadeCard &card);
    BlockadeCard& operator =(const BlockadeCard& e);
    void play(Card c, Hand &h, Deck &d, Player &p);
    friend ostream &operator<<(ostream &outs, const BlockadeCard &theObject);
    friend bool operator ==(const BlockadeCard& card1,
                            const BlockadeCard& card2); ///equal overload
    ~BlockadeCard();

private:
    string name;
    int id;
};


//Airlift card class which is a card
class AirliftCard : public Card{
public:
    AirliftCard();
    AirliftCard(string name,  int id);
    AirliftCard(const AirliftCard &card);
    AirliftCard& operator =(const AirliftCard& e);
    void play(Card c, Hand &h, Deck &d, Player &p);
    friend ostream &operator<<(ostream &outs, const AirliftCard &theObject);
    friend bool operator ==(const AirliftCard& card1,
                            const AirliftCard& card2); ///equal overload

    ~AirliftCard();


private:
    string name;
    int id;
};

//Diplomacy card class which is a card
class DiplomacyCard : public Card{
public:
    DiplomacyCard();
    DiplomacyCard(string name,  int id);
    DiplomacyCard(const DiplomacyCard &card);
    DiplomacyCard& operator =(const DiplomacyCard& e);
    void play(Card c, Hand &h, Deck &d, Player &p);
    friend ostream &operator<<(ostream &outs, const DiplomacyCard &theObject);
    friend bool operator ==(const DiplomacyCard& card1,
                            const DiplomacyCard& card2); ///equal overload
    ~DiplomacyCard();


private:
    string name;
    int id;
};

// Territory Class Declaration
class Territory {

private:
    //private members
    int id;
    Player *p;
    int territoryContinentId;
    int army;
    string name;
    // vector list of poitners to Territory objects
    vector<Territory*> neighboursList;


    //stream insurtion operator
    friend std::ostream& operator<<(std::ostream &strm, const Territory &t);
    friend istream& operator >>(istream& ins,Territory& t);

public:
    //default constructor that intializes id to 0 and name to " ", and neighbourList to null
    Territory();
    // constructor that intializes id to user provided id and name to users provided parameter, and neighbourList to null
    Territory(int id,string name ,int continentId, int army);
    //copy constructor
    Territory(const Territory& other);
    //destructor
    ~Territory();
    //accessor methods :
    string getName();
    int getId();
    int getCId();
    int getArmy();
    void addArmy(int x);
    void removeArmy(int x);

    vector<Territory*> getNeighboursList();
    bool validationOfNeighbours(Territory &t1,Territory &t2);

    //mutator methods(dont think u need setter method for list):


    void setId(int id);

    void setContinentId(int cId);
    void setPlayer(Player *p);
    Player *getPlayer();

    void setArmy(int army);

    void setName(string name);





    // adds new neighbours read from file(border) to list
    void addNeighbours(Territory* t);

    //display neighbours
    void displayNeighbours();

    // assignment operator overload
    Territory& operator = (const Territory& rhs);

    friend bool operator ==(const Territory &t1, const Territory &t2);
    //bool operator< (const cat &other) const {
    //        return age < other.age;
    //    }

    bool operator<(const Territory &other) const{
        return army < other.army;
    }

    bool sort_funct(const Territory &t, const Territory &other);
    void sort(vector<Territory*> &t);










};


//dummy class for player

#endif //RISKGAME_CARDS_H
