//
// Created by jgold on 2021-11-29.
//

#include "Player.h"

#ifndef RISKGAME_PLAYERSTRETEGY_H
#define RISKGAME_PLAYERSTRETEGY_H

class PlayerStrategy{
protected:
    string strategyType;
    Player *p;
public:
    virtual vector<Territory*> toDefend()=0;
    virtual vector<Territory*> toAttack()=0;
    virtual void issueOrder(vector<Player*> players)=0;

    PlayerStrategy();
    PlayerStrategy(Player *p, string strategyType);

    string getStrategyType();
    friend ostream& operator <<(ostream& str, const PlayerStrategy& p);
    void setStrategyType(string strat);
};

class AggressivePlayer : public PlayerStrategy {
private:

public:

    AggressivePlayer();
    AggressivePlayer(Player* pHolder, string strategyType);
    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    void issueOrder(vector<Player*> players);
};


class CheaterPlayer : public PlayerStrategy {
private:
public:
    //default
    CheaterPlayer();
    CheaterPlayer(Player* pHolder,string strategyType);
    vector<Territory*> toDefend();
    void issueOrder(vector<Player*> players);
    vector<Territory*> toAttack();
    string getStrategyType();
};

class NeutralPlayer : public PlayerStrategy {
private:
public:
    //default
    NeutralPlayer();
    NeutralPlayer(Player* pHolder,string strategyType);
    vector<Territory*> toDefend();
    void issueOrder(vector<Player*> players);
    vector<Territory*> toAttack();
    string getStrategyType();
};

class HumanPlayer : public PlayerStrategy {
private:
public:
    //default
    HumanPlayer();
    HumanPlayer(Player* pHolder,string strategyType);
    vector<Territory*> toDefend();
    void issueOrder(vector<Player*> players);
    vector<Territory*> toAttack();
    string getStrategyType();
    bool validate(Territory *t);
};

class BenevolentPlayer : public PlayerStrategy {
private:
public:
    //default
    BenevolentPlayer();
    BenevolentPlayer(Player* pHolder,string strategyType);
    vector<Territory*> toDefend();
    void issueOrder(vector<Player*> players);
    vector<Territory*> toAttack();
    string getStrategyType();
};
#endif //RISKGAME_PLAYERSTRETEGY_H
