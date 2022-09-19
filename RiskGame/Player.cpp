//
// Created by jgold on 2021-11-10.
//

#include<iostream>
#include<vector>
#include<string>
#include"Player.h"
#include "Orders.h"
#include <algorithm>
#include <string>




using namespace std;


class PlayerStrategy;
// Class Player begins here

//default constructor
Player::Player() {
    PlayerName = "";
    territories2 = vector<Territory*>();
    gameHand = vector<Card*>();
    reinforcements=0;
    hasDiplomacy = vector<Player*>();
    orderList = vector<Order*>();
    ps = NULL;

}
//parametrized constructor
Player::Player(string name) {
    PlayerName = name;
    territories2 = vector<Territory*>();
    gameHand = vector<Card*>();
    reinforcements=0;
    hasDiplomacy = vector<Player*>();
    orderList = vector<Order*>();
    ps = NULL;

}

//parametrized constructor
Player::Player(vector<Territory*> t,  vector<Card*> h, string name, int reinforcements, vector<Order*> ol,vector<Player*> hasDip, PlayerStrategy *ps) {
    territories2 = t;
    for (int i = 0; i < territories2.size(); i++) {
        territories2.at(i) = t.at(i);

    }

    orderList = ol;
    hasDiplomacy = hasDip;
    gameHand = h;
    PlayerName = name;
    this->reinforcements=reinforcements;
    this->ps = ps;
}

//destructor
Player::~Player() {
//    for (int i = 0; i < territories2.size(); i++) {
//        delete territories2[i];
//    }
    territories2.clear();

//    for (int i = 0; i < Orders.size(); i++) {
//        delete Orders[i];
//    }

}


//returns players territories
vector<Territory*> Player::getPlayerTerritories() {
    return territories2;
}

//returns players name
string Player::GetName(){
    return PlayerName;
}

//// returns players list of orders
//vector<OrdersList*> Player::getOrdersList() {
//    return Orders;
//}


vector<Card*> Player::getHand() {
    return gameHand;
}

void Player::addTerritory(Territory *territory) {
    territories2.push_back(territory);

}

vector<Order*> Player::getOrders(){
    return orderList;
}
//copy constructor
Player::Player(Player &another) {
    PlayerName = another.PlayerName;
    territories2 = another.territories2;
    for (int i = 0; i < territories2.size(); i++) {
        territories2[i] = another.territories2[i];
    }

    gameHand = another.gameHand;
    reinforcements = another.reinforcements;

}
//assignment operator
Player& Player:: operator=(const Player& other){
    PlayerName = other.PlayerName;
    territories2 = other.territories2;
    gameHand = other.gameHand;
    return *this;
}

//returns a verctor of players territories
vector<Territory*>Player:: getTerritory() {
    return territories2;

}

//stream insertion operator
ostream&  operator <<(ostream &str, const Player &p) {
    str << "Players name is: " << endl;
    str << p.PlayerName << endl;
    str << "Player owns the following territories: " << endl;
    for (int i=0; i<p.territories2.size();i++){
        str << *p.territories2.at(i) << endl;
    }
    str << "Player has " << p.reinforcements << " reinforcements size." << endl;
    if (p.gameHand.empty())
        str << "The hand is empty"<<endl;
    else {
        str << " \n players hand contains cards: " << endl;
        for (int i = 0; i < p.gameHand.size(); i++) {
            str << *p.gameHand[i];
        }
    }
    if (p.orderList.empty())
        str << "The Order List is empty"<<endl;
    else {
        str << " \n players order list contains orders: " << endl;
        for (int i = 0; i < p.orderList.size(); i++) {
            str << *p.orderList[i];
        }
    }

    return str;

}

//string Player::addOrder(Order *o) {
//    Orders.push_back(reinterpret_cast<OrdersList *const>(o));
//}

void Player::addReinforcements(int x) {
    this->reinforcements = x + reinforcements;
}

int Player::getReinforcements() {
    return reinforcements;
}

void Player::insertCardToHand(Card &c) {
    gameHand.push_back(&c);
}

vector<Territory *> Player::getTerrorityList() {

    return territories2;
}

Territory Player::getFrontTerritory() {
    return *territories2.front();
}

void Player::removeReinforcement(int x) {
    if(reinforcements - x < 0)
    {
        this->reinforcements = 0;
    }
    else {
        this->reinforcements = reinforcements - x;
    }
}

void Player::removeTerritory(Territory *t) {
    territories2.erase(std::remove(territories2.begin(), territories2.end(), t), territories2.end());


}

void Player::removeCard(Card *c) {

    gameHand.erase(std::remove(gameHand.begin(), gameHand.end(), c),gameHand.end());

}

void Player::executeOrder(Order &o,Player &p,Territory &source, Territory &target, int army) {
    if (o.returnType() == "Deploy") {
        cout << source;
        if (this->validateOwnership(source)) {
            auto *d = new Deploy("Deploy");
            o.execute(p, source, target, army);
            this->removeReinforcement(army);
            cout << endl << army << " Armies removed from player reinforcements. Player now has "
                 << this->getReinforcements() << " Reinforcements" << endl;


        } else
            cout << "Deployment failed. Sorry you do not have that territory to deploy to." << endl;
    }
    if (o.returnType() == "Airlift") {
        if (!validateAirLiftCardOwnership()) {
            cout << "Validation fail. You do not have the airlift card." << endl;
        }
        if (!validateOwnership(source) || !validateOwnership(target)) {
            cout << "Validation Fail. You do not own one of these territories" << endl;
        }
        if (validateOwnership(source) && validateOwnership(target) && validateAirLiftCardOwnership()) {
            auto *al = new Airlift("Airlift");

            o.execute(p, source, target, army);
            auto *a = new AirliftCard("Airlift", 4);
            this->removeCard(a);
            delete a;
            cout << "Airlift order successful" << endl;
        }
    }
    if (o.returnType() == "Bomb") {
        if (validateOwnership(target))
            cout << "Validation Fail. You cannot bomb your own territory" << endl;
        if (!validateBombCardOwnership()) {
            cout << "Validation fail. You do not have the bomb card." << endl;
        }
        if (validateBombCardOwnership() && !validateOwnership(target)) {
            auto *b = new Bomb("Bomb");
            o.execute(p, source, target, army);
            auto *bomb = new BombCard("Bomb", 1);
            this->removeCard(bomb);
            cout << "Bomb order Successful!" << endl;
        }
    }
    if (o.returnType() == "Negotiate") {
        if (!validateDiplomacyCardOwnership()) {
            cout << "Validation fail. You do not have the Diplomacy card." << endl;
        }
        if (!validateOwnership(target)) {
            cout << "That target you are creating a diplomacy with is your Territory. Validation failed!" << endl;
        }
        if (validateDiplomacyCardOwnership() && validateOwnership(source)) {
            auto *n = new Negotiate("Negotiate");

            o.execute(p, source, target, army);
            auto *d = new DiplomacyCard("Diplomacy", 5);
            this->removeCard(d);
            this->addPlayerDiplomacy(&p);
            cout << "Negotiate order Successful!" << endl;
        }
    }
    if (o.returnType() == "Blockade") {
        if (!validateBlockadeCardOwnership()) {
            cout << "Validation fail. You do not have the blockade card." << endl;
        }
        if (!validateOwnership(target)) {
            cout << "That target you are blockading is not your Territory. Validation failed!" << endl;
        }
        if (validateBlockadeCardOwnership() && validateOwnership(source)) {
            auto *b = new Blockade("Blockade");

            auto *blockade = new BlockadeCard("Blockade", 3);
            this->removeCard(blockade);
            o.execute(p, source, target, army);
            cout << "Blockade Order Successful" << endl;
        }
    }
    if (o.returnType() == "Advance") {

        if (this->ps->getStrategyType() == "Cheater") {

            if (target.getPlayer()->getPlayerStrategy() == "Neutral") {


                Player* pHolder = &p;

                PlayerStrategy* a = new AggressivePlayer(pHolder, "Aggressive");

                p.setStrategy(a);

                cout << "Player Strat Changed to Aggressive: " << pHolder->getPlayerStrategy() << endl;


            }

           cout << this->attack(p, source, target) <<endl;
            cout << "Advance Order Successful" << endl;
            cout << "DEBUG"<<*this->getTerrorityList().back();


        } else {

            if (!this->validateOwnership(source))
                cout << "Validation Fail. You do not own this territory" << endl;
            if (validateOwnership(source) && validateOwnership(target) && validateAdjancency(source, target)) {
                auto *a = new Advance("Advance");

                o.execute(p, source, target, army);
                cout << "Advance Order Successful" << endl;
            }
            if (validateOwnership(source) && validateAdjancency(source, target) && !validateOwnership(target)) {
                cout << "This is an Attack" << endl;
              
                if (target.getPlayer()->getPlayerStrategy() == "Neutral") {


                    Player* pHolder = &p;

                    PlayerStrategy* a = new AggressivePlayer(pHolder, "Aggressive");

                    p.setStrategy(a);
                    cout << "Player Strat Changed to Aggressive: " << pHolder->getPlayerStrategy() << endl;


                }
               cout << this->attack(p, source, target) <<endl;
                cout << "Advance Order Successful" << endl;
            }
        }
    }
}


bool Player::validateOwnership(Territory &t) {
    vector<Territory *> te = this->getTerrorityList();

    for (int i = 0; i < te.size(); i++) {
        if (*te[i] == t)
            return true;
    }
    return false;
}

bool Player::validateBlockadeCardOwnership() {
    BlockadeCard *bl = new BlockadeCard("Blockade",3);

    for (int i=0; i<this->getHand().size(); i++) {
        if(*this->getHand()[i]==*bl) {
            return true;
        }
    }
    return false;
}

bool Player::validateDiplomacyCardOwnership() {
    DiplomacyCard *d = new DiplomacyCard("Diplomacy",5);

    for (int i=0; i<this->getHand().size(); i++) {
        if(*this->getHand()[i]==*d) {
            return true;
        }
    }
    return false;
}


bool Player::validateAirLiftCardOwnership() {
    AirliftCard *a = new AirliftCard("Airlift",4);

    for (int i=0; i< this->getHand().size(); i++) {
        if(*this->getHand()[i]==*a) {
            return true;
        }
    }
    return false;
}

string Player::attack(Player &p,Territory &source, Territory &target) {
    bool sourWins = false;
    bool targWins = false;
    bool canContinue = true;
    string msg = "";

//    if (target.getArmy() == 0 && source.getArmy() == 0) {
//       msg = "Nothing to attack here";
//        return msg;
//    }


        for (int i = 0; i < this->getDiplomacyList().size(); i++) {
            if (this->getDiplomacyList()[i] == &p) {
                msg = "Sorry an attack cannot be made with this player because of a diplomacy";
                return msg;
                canContinue = false;
            }
        }


    if (this->ps->getStrategyType() == "Cheater") {
        canContinue = false;
        cout << ps->getStrategyType() <<" is taking " << target << endl;
        this->addTerritory(&target);
        cout << "Check the back " << *this->getTerrorityList().back();
        p.removeTerritory(&target);
        target.setArmy(0);
        msg = "Cheater succesfully took target";
        return msg;


    }
    else if (this->ps->getStrategyType() != "Cheater") {
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

                    } else
                        target.removeArmy(1);
                }
            }

            for (int i = 0; i < t; i++) {
                int x = rand() % 100;
                if (x <= 70) {
                    if (source.getArmy() == 0) {
                        targWins = true;
                        break;


                    } else
                        source.removeArmy(1);
                }
            }

            if (sourWins) {
                cout << "source army is " << source.getArmy() << " after attack" << endl;
                cout << "target army is " << target.getArmy() << " after attack" << endl;
                msg = "Attacking player wins";
                this->addTerritory(&target);
                p.removeTerritory(&target);
                return msg;
            } else if (targWins) {
                cout << "source army is " << source.getArmy() << " after attack" << endl;
                cout << "target army is " << target.getArmy() << " after attack" << endl;
                msg= "Defending player wins";
                p.addTerritory(&source);
                this->removeTerritory(&source);
                return msg;
            } else
                cout << "source army is " << source.getArmy() << " after attack" << endl;
            cout << "target army is " << target.getArmy() << " after attack" << endl;
            msg = "No winner";
        return msg;
        }

    }



void Player::addPlayerDiplomacy(Player *p) {
    hasDiplomacy.push_back(p);
}

void Player::setPlayerDiplomacyNull() {
    hasDiplomacy.clear();

}

void Player::setOrdersToEmpty() {
    orderList.clear();
}

vector<Player *> Player::getDiplomacyList() {
    return hasDiplomacy;
}

bool Player::canAttack(Player &p1, Player &p2) {
    if (p1.hasDiplomacy.size()==0 || p2.hasDiplomacy.size()==0){
        return true;
    }
    for(int j=0; j<p2.hasDiplomacy.size();j++) {
        for (int i = 0; i < p1.hasDiplomacy.size(); i++) {
            if (p1.hasDiplomacy[i] == p2.hasDiplomacy[j])
                return false;
        }
    }
    return true;
}

void Player::addOrderToList(Order *o) {
    orderList.push_back(o);
}


vector<Territory*> Player::toDefend(){
    return this->territories2;
}


vector<Territory*> Player::toAttack() {
    vector<Territory*> ToBeAttacked = vector<Territory*>();
    for(int i=0; i<territories2.size();i++){
        for(int j=0; j<territories2[i]->getNeighboursList().size();j++){
            Territory *t = territories2[i]->getNeighboursList()[j];
            if(find(ToBeAttacked.begin(), ToBeAttacked.end(), t) != ToBeAttacked.end() ){
                continue;
            }
            if(validate(t))
                continue;
            else{
                ToBeAttacked.push_back(t);
            }

        }
    }

    return ToBeAttacked;
}

bool Player::validate(Territory *t) {
    if(find(territories2.begin(),territories2.end(),t) != territories2.end())
        return true;
    else
        return false;
}

bool Player::validateAdjancency(Territory &source,Territory &target) {
    if (source.validationOfNeighbours(source, target))
        return true;
    else{
        cout << source << endl << "and" << target;
        cout << "Validation fail. This source Territory is not adjacent to target Territory";
        return false;
    }

}



bool Player::validateBombCardOwnership() {
    BombCard *b = new BombCard("Bomb",1);

    for (int i=0; i< this->getHand().size(); i++) {
        if(*this->getHand()[i]==*b) {
            return true;
        }
    }
    return false;
}

vector<Territory *> Player::territorySorter() {
   vector<Territory*> t = territories2;
   sort(t.begin(),t.end());
    return t;
}

vector<Territory*>& Player::getTerritoryByReference() {
    return territories2;
}

void Player::setStrategy(PlayerStrategy *strat) {
    this->ps = strat;
}

string Player::getPlayerStrategy() {
    return ps->getStrategyType();
}

void Player::issueOrder(vector<Player*> players) {

    ps->issueOrder(players);



}

bool operator==(const Player &p1, const Player &p2) {
    return (p1.PlayerName == p2.PlayerName);
}





















