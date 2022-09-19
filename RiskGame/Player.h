//
// Created by jgold on 2021-11-10.
//

#ifndef RISKGAME_PLAYER_H
#define RISKGAME_PLAYER_H
#include<iostream>
#include<vector>
#include<string>
#include "Cards.h"
#include "Orders.h"
#include <algorithm>
#include "PlayerStretegy.h"

using namespace std;


class Order;
class Player {

private:

    PlayerStrategy *ps;
    string PlayerName;
    vector<Territory*> territories2;
    vector<Card*> gameHand;
    vector<Player*> hasDiplomacy;
    int reinforcements;
    vector<Order*> orderList;

public:

    //constructors
    Player();
    Player(string name);
    Player(vector<Territory*> t, vector<Card*> h, string name, int reinforcements, vector<Order*> ol, vector<Player*> hasdiplomacy, PlayerStrategy *ps);
    void executeOrder(Order &o,Player &p,Territory &source, Territory &target,int army);
    bool validateOwnership(Territory &t);
    bool validateAdjancency(Territory &source,Territory &targer);
    string attack(Player &p,Territory &source,Territory &targer);
    bool validateAirLiftCardOwnership();
    bool validateBombCardOwnership();
    bool validateBlockadeCardOwnership();
    bool validateDiplomacyCardOwnership();
    friend bool operator ==(const Player &p1, const Player &p2);

    void issueOrder(vector<Player*> players);

    //copy constructor
    Player(Player &another);

    // destructor
    ~Player();

    //assignment operator
    Player& operator=(const Player& other);

    // stream insertion operator
    friend ostream& operator <<(ostream& str, const Player& p);


    //other functions
    void setPlayerDiplomacyNull();
    void addPlayerDiplomacy(Player *p);
    void setOrdersToEmpty();
    vector<Player*> getDiplomacyList();
    bool canAttack(Player &p1,Player &p2);
    vector<Territory*> getPlayerTerritories();
    string GetName();
    vector<Order*> getOrders();
    vector<Territory*> getTerritory();
    vector<Card*> getHand();
    vector<Territory*> getTerrorityList();
    void addOrderToList(Order *o);
    void insertCardToHand(Card &c);
    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    Territory getFrontTerritory();
    void setStrategy(PlayerStrategy *strat);
    string getPlayerStrategy();

//    string addOrder(Order *o);
    int getReinforcements();
    void addTerritory(Territory *territory);
    bool validate(Territory *t);
    void addReinforcements(int x);
    void removeReinforcement(int x);
    void removeTerritory(Territory *t);
    void removeCard(Card *c);
    vector<Territory*>& getTerritoryByReference();


    //    vector< cat > catSorter::SortCatsByAge(){
//        vector< cat > cats_copy = cats;
//        std::sort(cats_copy.begin(), cats_copy.end());
//        return cats_copy;
//    }

    vector<Territory*> territorySorter();

    bool sort_funct(Territory &t, Territory &other);






    };



#endif //RISKGAME_PLAYER_H
