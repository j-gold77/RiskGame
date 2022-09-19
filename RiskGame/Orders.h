#pragma once
#ifndef UNTITLED_ORDER_H
#define UNTITLED_ORDER_H
#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "LogObserver.h"

using namespace std;

///order class
class Order : public Subject, public ILoggable {
protected:
    string type; ///type of order
    Territory * targetterritory;
    int nbarmies;
    Territory* sourceterritory;
    Player *player;
public:
    Order(); ///default constructor
    Order(string type); ///paramtaized construtor
    //Copy constructor
    Order(const Order& o1); ///copy constructor
    Order& operator =(const Order& o); ///assignment overload
    string returnType(); ///gets the type
    virtual void execute(Player& p, Territory& source, Territory& target, int armies) = 0; ///pure virtual execute method
    friend ostream& operator <<(ostream& str, const Order& o); ///ostream
    string getType();
    Territory* getTargetTerritory() ;
    Territory* getSourceTerritory();
    Player *getPlayer();
    int getArmies();
    void attack(Player& p, Territory& source, Territory& target); ///attack
    string stringToLog();
    ~Order();
};

///deploy order class, child class of order
class Deploy : public Order {
private:
    //int priorityOfOrder;
public:
    Deploy(string type,int army,Territory &t,Player &p);
    Deploy(); ///default constructor
    Deploy(string type); ///paramaterized constructor
    Deploy(const Deploy& o1); ///copy constructor
    Deploy& operator =(const Deploy& o); /// assignment overload
    bool validate(Player& p, Territory& t); ///validate
    void execute(Player& p, Territory& source, Territory& target, int armies); ///virtual execute overload
    friend ostream& operator <<(ostream& str, const Deploy& o); ///stream output
    string stringToLog();
    ~Deploy();
};

///advance class derived of order class
class Advance : public Order {
private:
    // int priorityOfOrder;
public:
    Advance(string type, int army, Player* p, Territory* s, Territory* t);
    Advance(); ///default constructor
    Advance(string type); ///paramertized constructor
    Advance(const Advance& o1); /// copy constructor
    Advance& operator =(const Advance& o); /// assignment overload
    bool validateOwnership(Player& p, Territory& source); ///validate ownership of sourve
    bool validateAdjacency(Territory& source, Territory& target); ///validate adjancy of source and target
    void execute(Player& p, Territory& source, Territory& target, int armies); ///virtual overload of execute
    friend ostream& operator <<(ostream& str, const Advance& o); ///ostream output
    string stringToLog();
    ~Advance();
};

///airlift order child of order class
class Airlift : public Order {
private:

    //int priorityOfOrder;
public:
    Airlift( string type,int army, Player* p, Territory* source, Territory* target);
    Airlift(); ///default constructor
    Airlift(string type); ///paramertized constructor
    Airlift(const Airlift& o1); ///copy constructor
    Airlift& operator =(const Airlift& o); ///assignment overload
    bool validateOwnership(Player& p, Territory& source); ///validate ownership of course
    bool validateCardOwnership(Player& p); ///validate ownership of airlift card
    void execute(Player& p, Territory& source, Territory& target, int armies); ///virtual execute overload
    friend ostream& operator <<(ostream& str, const Airlift& o); ///ostream output
    string stringToLog();
    ~Airlift();
};

///bomb class child class of order
class Bomb : public Order {
private:

    // int priorityOfOrder;
public:
    Bomb( string type,Territory* target, Player* p);
    Bomb(); ///default consteuctor
    Bomb(string type); ///paramertized constructor
    Bomb(const Bomb& o1); ///copy constructor
    Bomb& operator =(const Bomb& o); ///assignment overload
    bool validateOwnership(Player& p, Territory& source); ///validate ownership of source
    bool validateCardOwnership(Player& p); ///validate ownership of bomb card
    void execute(Player& p, Territory& source, Territory& target, int armies); ///virutal execute overload
    friend ostream& operator <<(ostream& str, const Bomb& o); ///ostream output
    string stringToLog();
    ~Bomb();
};

///blockade order class child of order class
class Blockade : public Order {
private:

    //int priorityOfOrder;
public:
    Blockade(string type,Player* p,Territory* target);
    Blockade(); ///default constructor
    Blockade(string type); ///paramertized constructor
    Blockade(const Blockade& o1); ///copy constructor
    Blockade& operator =(const Blockade& o); ///assignment overload
    bool validateOwnership(Player& p, Territory& source); ///validate source ownership
    bool validateCardOwnership(Player& p); ///validate blockade card ownership
    void execute(Player& p, Territory& source, Territory& target, int armies); ///virtual execute overload
    friend ostream& operator <<(ostream& str, const Bomb& o); ///ostream output
    string stringToLog();
    ~Blockade();
};

///negotiate order class child of order
class Negotiate : public Order {
private:

    //int priorityOfOrder;
public:
    Negotiate(string type,Player* p); //parametrized constructor
    Negotiate(); ///default constructor
    Negotiate(string type);///paramertized constructor
    Negotiate(const Negotiate& o1); ///copy constructor
    Negotiate& operator =(const Negotiate& o); ///assignment overload
    bool validateOwnership(Player& p, Territory& source); ///validate ownership of source
    bool validateCardOwnership(Player& p); ///validate diplomacy card ownership
    void execute(Player& p, Territory& source, Territory& target, int armies); ///virtual execute overload
    friend ostream& operator <<(ostream& str, const Bomb& o); ///ostream output
    string stringToLog();
    ~Negotiate();
};


///orderlist class
class OrderList : public Subject, ILoggable {
private:
    std::vector<Order*> order_vector; ///contains a vector of orders
public:
    OrderList(); ///default constructor
    OrderList(OrderList& oList); ///paramertized constructor
    void insert(Order* order); ///insert an order
    void move(int current_order_location, int new_order_location); ///move an order
    void remove(int order_location); ///remove an order
    void displayList(); ///display list
    int getLength(); ///get length
    Order* returnOrder(int index); ///return an order
    friend ostream& operator <<(ostream& str, const OrderList& o); ///ostream output
    string stringToLog();

};


#endif //UNTITLED_ORDER_H