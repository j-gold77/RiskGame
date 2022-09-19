#include "Orders.h"

////*****************************ORDER CLASS STARTS HERE***************************
///default constructor
Order::Order() {
    type = "generic order";

}

///paramertized constructor
Order::Order(string theType) : type(theType) {}

///copy constructor
Order::Order(const Order& o1) {
    this->type = o1.type;
}

///return type of order
string Order::returnType() {
    return type;
}

///attack order
void Order::attack(Player& p, Territory& source, Territory& target) {
    bool sourWins = false;
    bool targWins = false;

    for (int i = 0; i < p.getDiplomacyList().size(); i++) {
        if (p.getDiplomacyList()[i])
            cout << "Sorry an attack cannot be made with this player because of a diplomacy";
    }
    cout << "Before attack attack army size of source territory is " << source.getArmy() << endl;
    cout << "Before attack attack army size of target territory is " << target.getArmy() << endl;
    int s = source.getArmy();
    int t = target.getArmy();
    for (int i = 0; i < s; i++) {
        int x = rand() % 100;
        if (x <= 60) {
            if (target.getArmy() == 0) {
                sourWins = true;
                break;

            }
            else
                target.removeArmy(1);
        }
    }

    for (int i = 0; i < t; i++) {
        int x = rand() % 100;
        if (x <= 70) {
            if (source.getArmy() == 0) {
                targWins = true;
                break;


            }
            else
                source.removeArmy(1);
        }
    }

    if (sourWins) {
        cout << "source army is " << source.getArmy() << " after attack" << endl;
        cout << "target army is " << target.getArmy() << " after attack" << endl;
        cout << "Attacking player wins" << endl;
    }
    else if (targWins) {
        cout << "source army is " << source.getArmy() << " after attack" << endl;
        cout << "target army is " << target.getArmy() << " after attack" << endl;
        cout << "Defending player wins" << endl;
    }
}


///outstream for order
ostream& operator<<(ostream& str, const Order& o) {
    str << "Order is " << o.type << endl;
    return str;
}

///assignment operator
Order& Order::operator=(const Order& o) {
    this->type = o.type;
    return *this;
}

string Order::stringToLog()
{
    return "Order execute";
}

///deconstructor
Order::~Order() {

}

string Order::getType() {
    return type;
}


Territory* Order::getSourceTerritory() {
    return sourceterritory;
}

int Order::getArmies() {
    return nbarmies;
}

Player* Order::getPlayer() {
    return player;
}

Territory* Order::getTargetTerritory()  {
    return targetterritory;
}


////*****************************Deploy ORDER CLASS STARTS HERE***************************

///default constructor
Deploy::Deploy() {
    type = "deploy";
}

///paramertized constructor
Deploy::Deploy(string type) : Order(type) {}

Deploy::Deploy(string thisType,int army, Territory& t, Player& p) {
    type = thisType;
    nbarmies = army;
    sourceterritory = &t;
    player = &p;

}

///execute overload returns a string
void Deploy::execute(Player& p, Territory& source, Territory& target, int armies) {

    source.addArmy(armies);
    cout << endl << armies << " Armies added to " << source;
    Notify(this);
}


string Deploy::stringToLog()
{
    string fromOrder = Order::stringToLog();
    fromOrder.append(": ");
    fromOrder.append(type);
    return fromOrder;
}
///outstream output
ostream& operator<<(ostream& str, const Deploy& o) {
    str << "Order is " << o.type;
    return str;
}
///validate source is in player's territories
bool Deploy::validate(Player& p, Territory& t) {
    vector<Territory*> te = p.getPlayerTerritories();

    for (int i = 0; i < te.size(); i++)
    {
        if (*te[i] == t) {
            return true;
        }
        else
            return false;
    }
}
///deploy copy constructor
Deploy::Deploy(const Deploy& o1) {
    this->type = o1.type;
}
///assignment overload
Deploy& Deploy::operator=(const Deploy& o) {
    Order::operator=(o);
    this->type = o.type;
    return *this;
}
///deploy destructor
Deploy::~Deploy() {

}


////*****************************Advance ORDER CLASS STARTS HERE***************************

///default constructor
Advance::Advance() {
    type = "Advance";
}
///paramertized constructor
Advance::Advance(string type) : Order(type) {}

Advance::Advance(string thisType,int army, Player* p, Territory* s, Territory* t) {
    type = thisType;
    nbarmies = army;
    player = p;
    sourceterritory = s;
    targetterritory = t;


}

///virtual execute overload. takes in a player, source territory, target territory and armies. returns a string
void Advance::execute(Player& p, Territory& source, Territory& target, int armies) {


    cout << "Both territories belong to same player and are adjacent." << endl;
    cout << "You are issuing an advance order from " << source << " to " << target << endl;
    if (source.getArmy() == 0) {
        cout << source << " army size is zero. no armies to move.";
    }
    else {
        target.addArmy(armies);
        source.removeArmy(armies);
        cout << armies << " armies added to " << target << endl;
        cout << armies << " armies removed from " << source << endl;
        cout << "Advance order successful" << endl;
        Notify(this);

    }
}





string Advance::stringToLog()
{
    string fromOrder = Order::stringToLog();
    fromOrder.append(": ");
    fromOrder.append(type);
    return fromOrder;
}
///outstream output
ostream& operator<<(ostream& str, const Advance& o) {
    str << "Order is " << o.type;
    return str;
}

///validate ownership of source terrttory
bool Advance::validateOwnership(Player& p, Territory& source) {
    for (int i = 0; i < p.getTerrorityList().size(); i++) {
        if (*p.getTerrorityList()[i] == source)
            return true;
    }
    return false;
}

///validate adjancy of source and target territories
bool Advance::validateAdjacency(Territory& source, Territory& target) {
    if (source.validationOfNeighbours(source, target))
        return true;
    cout << "Validation fail. This source Territory is not adjacent to target Territory";
    return false;
}

///copy constructor
Advance::Advance(const Advance& o1) {
    this->type = o1.type;
}

///assignment overload
Advance& Advance::operator=(const Advance& o) {
    Order::operator=(o);
    this->type = o.type;
    return *this;
}

///deconstructor
Advance::~Advance() {

}

////*****************************Airlift ORDER CLASS STARTS HERE***************************

///default constructor
Airlift::Airlift() {
    type = "Airlift";
}

///paramertized constructor
Airlift::Airlift(string type) : Order(type) {}
Airlift::Airlift(string thisType,int army, Player* p, Territory* source, Territory* target) {
    type = thisType;
    nbarmies = army;
    player = p;
    sourceterritory = source;
    targetterritory = target;
}

///virtual execute overload. takes in a play, source and target territory and armies. returns a string
void Airlift::execute(Player& p, Territory& source, Territory& target, int armies) {


    target.addArmy(armies);
    source.removeArmy(armies);
    cout << armies << " added to " << target;
    cout << armies << " removed from " << source;
    Notify(this);

}

string Airlift::stringToLog()
{
    string fromOrder = Order::stringToLog();
    fromOrder.append(": ");
    fromOrder.append(type);
    return fromOrder;
}

///validate ownership of source territory
bool Airlift::validateOwnership(Player& p, Territory& source) {
    for (int i = 0; i < p.getTerrorityList().size(); i++) {
        if (*p.getTerrorityList()[i] == source)
            return true;
    }
    return false;
}

///validate if player has an airlift card
bool Airlift::validateCardOwnership(Player& p) {
    AirliftCard* a = new AirliftCard("Airlift", 4);

    for (int i = 0; i < p.getHand().size(); i++) {
        if (*p.getHand()[i] == *a) {
            return true;
        }
    }
    return false;
}

///outsream output
ostream& operator<<(ostream& str, const Airlift& o) {
    str << "Order is " << o.type;
    return str;
}
///copy constructor
Airlift::Airlift(const Airlift& o1) {
    this->type = o1.type;
}

///assignment overload
Airlift& Airlift::operator=(const Airlift& o) {
    Order::operator=(o);
    this->type = o.type;
    return *this;
}

///descontructor
Airlift::~Airlift() {

}


////*****************************Bomb ORDER CLASS STARTS HERE***************************

///default constructor
Bomb::Bomb() {
    type = "Airlift";
}

///paramertized constructor
Bomb::Bomb(string type) : Order(type) {}

Bomb::Bomb(string thisType,Territory* target, Player* p) {
    type = thisType;
    targetterritory = target;
    player = p;

}

///virtual execute overload. takes in a player, source and target territory and armies.
void Bomb::execute(Player& p, Territory& source, Territory& target, int armies) {


    cout << "Target armies before bombing is: " << target.getArmy() << endl;
    int x = target.getArmy() / 2;
    target.removeArmy(x);
    cout << target << "Has been bombed! armies halved!" << endl;
    Notify(this);


}


///validate ownership of source territory
bool Bomb::validateOwnership(Player& p, Territory& source) {
    for (int i = 0; i < p.getTerrorityList().size(); i++) {
        if (*p.getTerrorityList()[i] == source)
            return true;
    }
    return false;
}

string Bomb::stringToLog()
{
    string fromOrder = Order::stringToLog();
    fromOrder.append(": ");
    fromOrder.append(type);
    return fromOrder;
}

///validate if player has bomb card
bool Bomb::validateCardOwnership(Player& p) {
    BombCard* b = new BombCard("Bomb", 1);

    for (int i = 0; i < p.getHand().size(); i++) {
        if (*p.getHand()[i] == *b) {
            return true;
        }
    }
    return false;
}

///outstream overload for bomb class
ostream& operator<<(ostream& str, const Bomb& o) {
    str << "Order is " << o.type;
    return str;
}

///copy constructor
Bomb::Bomb(const Bomb& o1) {
    this->type = o1.type;
}

///asignment overload
Bomb& Bomb::operator=(const Bomb& o) {
    Order::operator=(o);
    this->type = o.type;
    return *this;
}

///deconstructor
Bomb::~Bomb() {

}



////*****************************Deploy ORDER CLASS STARTS HERE***************************

///default blockade constructor
Blockade::Blockade() {
    type = "Airlift";
}

///paramertized constructor
Blockade::Blockade(string type) : Order(type) {}

Blockade::Blockade(string thisType,Player* p, Territory* target) {
    type = thisType;
    player = p;
    targetterritory = target;
}

///virtual execute overload. take in a player, source and target territory and armies.
void Blockade::execute(Player& p, Territory& source, Territory& target, int armies) {


    cout << "Target armies before blockade is: " << target.getArmy() << endl;
    int x = target.getArmy();
    target.addArmy(x);
    cout << target << "Has been blockaded! armies doubled!" << endl;
    cout << "Territory transferred to neutral player";
    Notify(this);
}


///validates if source territory belongs to player
bool Blockade::validateOwnership(Player& p, Territory& source) {
    for (int i = 0; i < p.getTerrorityList().size(); i++) {
        if (*p.getTerrorityList()[i] == source)
            return true;
    }
    return false;
}

string Blockade::stringToLog()
{
    string fromOrder = Order::stringToLog();
    fromOrder.append(": ");
    fromOrder.append(type);
    return fromOrder;
}
///validates if player has blockade card
bool Blockade::validateCardOwnership(Player& p) {
    BlockadeCard* bl = new BlockadeCard("Blockade", 3);

    for (int i = 0; i < p.getHand().size(); i++) {
        if (*p.getHand()[i] == *bl) {
            return true;
        }
    }
    return false;
}

///copy constructor
Blockade::Blockade(const Blockade& o1) {
    this->type = o1.type;
}

///asignment overload
Blockade& Blockade::operator=(const Blockade& o) {
    Order::operator=(o);
    this->type = o.type;
    return *this;
}

///deconstructor
Blockade::~Blockade() {

}

////*****************************Negotiate ORDER CLASS STARTS HERE***************************


///default constructor
Negotiate::Negotiate() {
    type = "Negoitiate";
}

///paramertized constructor
Negotiate::Negotiate(string type) : Order(type) {}

Negotiate::Negotiate(string thisType,Player* p) {
    type = thisType;
    player = p;
}

///virtual execute overload.
void Negotiate::execute(Player& p, Territory& source, Territory& target, int armies) {



    cout << target << "You have created a diplomacy with another player!" << endl;
    Notify(this);


}

string Negotiate::stringToLog()
{
    string fromOrder = Order::stringToLog();
    fromOrder.append(": ");
    fromOrder.append(type);
    return fromOrder;
}

///validate ownership of source territory
bool Negotiate::validateOwnership(Player& p, Territory& source) {
    for (int i = 0; i < p.getTerrorityList().size(); i++) {
        if (*p.getTerrorityList()[i] == source)
            return true;
    }
    return false;
}

///validate if player has diplomacy card
bool Negotiate::validateCardOwnership(Player& p) {
    DiplomacyCard* d = new DiplomacyCard("Diplomacy", 5);

    for (int i = 0; i < p.getHand().size(); i++) {
        if (*p.getHand()[i] == *d) {
            return true;
        }
    }
    return false;
}



///copy constructor
Negotiate::Negotiate(const Negotiate& o1) {
    this->type = o1.type;
}

///assignment overload
Negotiate& Negotiate::operator=(const Negotiate& o) {
    Order::operator=(o);
    this->type = o.type;
    return *this;
}

///deconstructor
Negotiate::~Negotiate() {

}


////*****************************ORDERLIST CLASS STARTS HERE***************************

///default constructor
OrderList::OrderList() {
    cout << "New OrderList generated \n";
}
///paramertized constructor
OrderList::OrderList(OrderList& oList) {
    this->order_vector = oList.order_vector;
}

///getlength returns int
int OrderList::getLength() {
    return order_vector.size();
}

///returns and order
Order* OrderList::returnOrder(int index) {
    return order_vector.at(index);
}

///inser order
void OrderList::insert(Order* order) {
    cout << "Inserting a new Order onto the end of the orderlist " << endl;
    order_vector.push_back(order);
    Notify(this);
}

///move and order
void OrderList::move(int current_order_location, int new_order_location) {
    cout << "moving order from " << current_order_location << " to " << new_order_location << endl;
    iter_swap(order_vector.begin() + current_order_location, order_vector.begin() + new_order_location);
}

///remove and order
void OrderList::remove(int order_location) {
    cout << "removing order in position " << order_location;
    if (order_vector.empty()) {
        cout << "order list is empty, nothing was removed" << endl;
    }
    else {
        order_vector.erase(order_vector.begin() + order_location);
        cout << "order " << order_location << " was successfully removed from the order list" << endl;
    }
}

///diplayer list
void OrderList::displayList() {
    for (Order* order : order_vector) {
        cout << (*order).returnType() << endl;
    }
}

string OrderList::stringToLog()
{
    string toLog = "OrderList insert :: Order to be added is of type: ";
    toLog.append(order_vector.back()->returnType());

    return toLog;
}