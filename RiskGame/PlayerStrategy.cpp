#include "PlayerStretegy.h"
PlayerStrategy::PlayerStrategy() {

}

PlayerStrategy::PlayerStrategy(Player *newPlayer, string type ) {
    p = newPlayer;
    strategyType = type;

}

ostream &operator<<(ostream &str, const PlayerStrategy &p) {
    return str << "Player strategy is " << p.strategyType << endl;
}

void PlayerStrategy::setStrategyType(string strat) {
        strategyType = strat;

}

string PlayerStrategy::getStrategyType() {
    return strategyType;
}

AggressivePlayer::AggressivePlayer(Player *p,string strategyType) : PlayerStrategy(p,strategyType) {

}

vector<Territory*> AggressivePlayer::toDefend() {
    p->territorySorter();
    return p->getTerrorityList();

}

vector<Territory*> AggressivePlayer::toAttack() {
    vector<Territory *> ToBeAttacked = vector<Territory *>();
    for (int i = 0; i < p->getTerrorityList().size(); i++) {
        for (int j = 0; j < p->getTerrorityList()[i]->getNeighboursList().size(); j++) {
            Territory *t = p->getTerrorityList()[i]->getNeighboursList()[j];
            if (find(ToBeAttacked.begin(), ToBeAttacked.end(), t) != ToBeAttacked.end()) {
                continue;
            }
            if (p->validate(t))
                continue;
            else {
                ToBeAttacked.push_back(t);
            }

        }
    }

    sort(ToBeAttacked.begin(), ToBeAttacked.end());

    return ToBeAttacked;
}

    void AggressivePlayer::issueOrder(vector<Player*> players) {
        cout << p->getReinforcements();
        int reinforcementHolder = p->getReinforcements();
        while (reinforcementHolder >= 3) {


            Deploy* d = new Deploy("Deploy",3, *toDefend().back(), *p);
            p->addOrderToList(d);
            reinforcementHolder -= 3;

        }
        //advancing on strongest country

        for (int i = toDefend().size() - 2; i > -1 ; i--) {
            if(p->getTerrorityList().back()==toDefend().back())
                continue;
            else {

                int x = toDefend()[i]->getArmy();

                Advance *a = new Advance("Advance", x, p, p->getTerrorityList().back(), toDefend().back());
                p->addOrderToList(a);
            }


        }

        //advances on ennemy territory


        cout << "Here in aggressive" << endl;

  

     

        //if boxed in send armies to another from to Defend
        bool boxedIn = true;
        int count = toDefend().back()->getNeighboursList().size();
        int x = 0;
        for (int i = 0; i < count; i++) {
            if (toDefend().back()->getNeighboursList()[i]->getPlayer() == p) {


                x++;
            }


        }
        if (x == count ) {
            Advance* a = new Advance("Advance", toDefend().back()->getArmy(), p, toDefend().back(), toDefend().front());
            p->addOrderToList(a);

        }
        else {
           cout << p->GetName() << " Has Issued an Order To Attack :" << *toAttack().front() << endl << "With : " << *toDefend().back();
            for (int i = 0; i < toAttack().size(); i++) {
                if(toDefend().back()==toAttack()[i])
                    continue;
                else {


                    auto *a = new Advance("Advance", toDefend().back()->getArmy(), toAttack()[i]->getPlayer(),
                                          toDefend().back(), toAttack()[i]);
                    p->addOrderToList(a);
                }


            }
//            Advance* a = new Advance("Advance", toDefend().back()->getArmy(), toAttack().front()->getPlayer(), toDefend().back(), toAttack().front());
//            p->addOrderToList(a);


        }


}

AggressivePlayer::AggressivePlayer() {
    strategyType = "Aggressive";
    p = NULL;

}

CheaterPlayer::CheaterPlayer() {
    strategyType = "Cheater";
    p = NULL;

}

HumanPlayer::HumanPlayer()  {
    strategyType = "Human";
    p = NULL;

}

vector<Territory *> HumanPlayer::toDefend() {
    return p->getTerrorityList();
}

vector<Territory *> HumanPlayer::toAttack() {
    vector<Territory*> ToBeAttacked = vector<Territory*>();
    for(int i=0; i<p->getTerrorityList().size();i++){
        for(int j=0; j<p->getTerrorityList()[i]->getNeighboursList().size();j++){
            Territory *t = p->getTerrorityList()[i]->getNeighboursList()[j];
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

void HumanPlayer::issueOrder(vector<Player*> players) {

    int reinforcementsHolder = p->getReinforcements();
    if (p->getReinforcements() > 0) {


        while (reinforcementsHolder > 0) {
            cout << "You still have reinforcements to deploy. Creating Deploy order for you." << endl;
            cout << "Now pick a territory you would like to move those armies to." << endl;

            int w = -1;
            for (int i = 0; i < p->getTerrorityList().size(); i++) {
                cout << i << ") " << *p->getTerrorityList()[i];
            }
            cin >> w;

            int armiesToAdd = -1;
            cout << "How many Armies would You like to add from your reinforcment pool: " << reinforcementsHolder
                 << endl;

            cin >> armiesToAdd;


            Deploy *d = new Deploy("Deploy", armiesToAdd, *p->getTerrorityList()[w], *p);
            p->addOrderToList(d);
            reinforcementsHolder -= armiesToAdd;

        }
    }


    cout
            << "You can choose 5 different orders to put in your order list. pick an option from 1 to 5. 0 to end turn."
            << endl;
    int x = -1;
    cout << "Option 1: Advance" << endl;
    cout << "Option 2: Bomb" << endl;
    cout << "Option 3: Airlift" << endl;
    cout << "Option 4: Blockade" << endl;
    cout << "Option 5: Negotiate" << endl;
    cout << "Option 0; to End turne" << endl;
    cin >> x;

    while (x != 0) {

        if (x == 1) {
            int y = -1;
            bool isDone = false;
            cout<<"would you like to attack or fortify your own territories. pick 1 for attack and 2 for fortify."<< endl;
            cin >> y;
            if (y == 1) {
                cout
                        << "You have chosen to attack a territory. Please choose which territory you would like to use in this attack. Use the number displayed."
                        << endl;
                for (int i = 0; i < this->p->getTerrorityList().size(); i++) {
                    cout << i << ") " << *p->getTerrorityList()[i];
                }

                int z = -1;
                cin >> z;

                cout<< "Now choose which territory you would like to advance on. Pick the number next to the display"<< endl;
                int w = -1;
                for (int i = 0; i<p->getTerrorityList()[z]->getNeighboursList().size(); i++) {
                    if (*p->getTerrorityList()[z]->getNeighboursList()[i]->getPlayer() == *p)
                        continue;
                    else
                        cout << i << ") " << *p->getTerrorityList()[z]->getNeighboursList()[i]<<endl;
                }
                cin >> w;

                Advance *a = new Advance("Advance", 0, p->getTerrorityList()[z]->getNeighboursList()[w]->getPlayer(),
                                         p->getTerrorityList()[z],
                                         p->getTerrorityList()[z]->getNeighboursList()[w]);
                p->addOrderToList(a);
                cout << "Option 1: Advance" << endl;
                cout << "Option 2: Bomb" << endl;
                cout << "Option 3: Airlift" << endl;
                cout << "Option 4: Blockade" << endl;
                cout << "Option 5: Negotiate" << endl;
                cout << "Option 0; to End turne" << endl;
                cin >> x;

            }
            if (y == 2) {
                cout
                        << "You have chosen to fortify your territories. Please pick a territory from the list below to move armies from."
                        << endl;
                int z = -1;
                for (int i = 0; i < p->getTerrorityList().size(); i++) {
                    cout << i << ") " << *p->getTerrorityList()[i];
                }
                cin >> z;

                cout << "Now pick a territory you would like to move those armies to." << endl;

                int w = -1;
                for (int i = 0; i < p->getTerrorityList().size(); i++) {
                    cout << i << ") " << *p->getTerrorityList()[i];
                }
                cin >> w;

                int r = -1;

                cout << "How many armies would you like to move? Pick" << endl;
                cin >> r;


                Advance *a = new Advance("Advance", r, p, p->getTerrorityList()[z], p->getTerrorityList()[w]);
                p->addOrderToList(a);
                cout << "Option 1: Advance" << endl;
                cout << "Option 2: Bomb" << endl;
                cout << "Option 3: Airlift" << endl;
                cout << "Option 4: Blockade" << endl;
                cout << "Option 5: Negotiate" << endl;
                cout << "Option 0; to End turne" << endl;
                cin >> x;

            }

        }

        if (x == 2) {
            cout << "Choose a territory you would like to bomb. pick a number from the display list please."
                 << endl;
            for (int i = 0; i < p->toAttack().size(); i++) {
                cout << i << ") " << *p->toAttack()[i];
            }
            int y = -1;
            cin >> y;

            Bomb *b = new Bomb("Bomb", p->toAttack()[y], p);
            p->addOrderToList(b);
            cout << "Option 1: Advance" << endl;
            cout << "Option 2: Bomb" << endl;
            cout << "Option 3: Airlift" << endl;
            cout << "Option 4: Blockade" << endl;
            cout << "Option 5: Negotiate" << endl;
            cout << "Option 0; to End turne" << endl;
            cin >> x;

        }

        if (x == 3) {
            cout
                    << "Choose a territory you would like to Airlift troops from. pick a number from the display list please."
                    << endl;
            for (int i = 0; i < this->p->getTerrorityList().size(); i++) {
                cout << i << ") " << *this->p->getTerrorityList()[i];
            }
            int y = -1;
            cin >> y;

            cout
                    << " now Choose a territory you would like to Airlift troops to. pick a number from the display list please."
                    << endl;
            for (int i = 0; i < this->p->getTerrorityList().size(); i++) {
                cout << i << ") " << *this->p->getTerrorityList()[i];
            }
            int z = -1;
            cin >> z;


            int r = -1;
            cout << "How many armies would you like to move?" << endl;
            cin >> r;


            Airlift *a = new Airlift("Airlift", r, p, p->getTerrorityList()[y], p->getTerrorityList()[z]);
            p->addOrderToList(a);
            cout << "Option 1: Advance" << endl;
            cout << "Option 2: Bomb" << endl;
            cout << "Option 3: Airlift" << endl;
            cout << "Option 4: Blockade" << endl;
            cout << "Option 5: Negotiate" << endl;
            cout << "Option 0; to End turne" << endl;
            cin >> x;

        }


        if (x == 4) {
            cout << "Choose a territory you would like to Blockade. pick a number from the display list please."
                 << endl;
            for (int i = 0; i < this->toAttack().size(); i++) {
                cout << i << ") " << *this->toAttack()[i];
            }
            int y = -1;
            cin >> y;

            Blockade *b = new Blockade("Blockade", p, p->toAttack()[y]);
            p->addOrderToList(b);
            cout << "Option 1: Advance" << endl;
            cout << "Option 2: Bomb" << endl;
            cout << "Option 3: Airlift" << endl;
            cout << "Option 4: Blockade" << endl;
            cout << "Option 5: Negotiate" << endl;
            cout << "Option 0; to End turne" << endl;
            cin >> x;

        }

        if (x == 5) {
            cout << "Choose a player you would like to Negotiate with. pick a number from the display list please."
                 << endl;
            for (int i = 0; i < players.size(); i++) {
                cout << i << ") " << players[i]->GetName()<<endl;
            }
            int y = -1;
            cin >> y;

            Negotiate *n = new Negotiate("Negotiate", players[y]);
            p->addOrderToList(n);
            cout << "Option 1: Advance" << endl;
            cout << "Option 2: Bomb" << endl;
            cout << "Option 3: Airlift" << endl;
            cout << "Option 4: Blockade" << endl;
            cout << "Option 5: Negotiate" << endl;
            cout << "Option 0; to End turne" << endl;
            cin >> x;


        }

    }
}

BenevolentPlayer::BenevolentPlayer() {
    strategyType = "Benevolent";
    p = NULL;

}



CheaterPlayer::CheaterPlayer(Player *p,string strategyType) : PlayerStrategy(p,strategyType) {

}

vector<Territory*> CheaterPlayer::toDefend() {
    p->territorySorter();
    return p->getTerrorityList();
}

vector<Territory*> CheaterPlayer::toAttack() {
    vector<Territory*> ToBeAttacked = vector<Territory*>();
    for (int i = 0; i < p->getTerrorityList().size(); i++) {
        for (int j = 0; j < p->getTerrorityList()[i]->getNeighboursList().size(); j++) {
            Territory* t = p->getTerrorityList()[i]->getNeighboursList()[j];
            if (find(ToBeAttacked.begin(), ToBeAttacked.end(), t) != ToBeAttacked.end()) {
                continue;
            }
            if (p->validate(t))
                continue;
            else {
                ToBeAttacked.push_back(t);
            }

        }
    }

    sort(ToBeAttacked.begin(), ToBeAttacked.end());

    return ToBeAttacked;


}


void CheaterPlayer::issueOrder(vector<Player*> players) {

    int reinforcementHolder = p->getReinforcements();

    while (reinforcementHolder >= 3) {


        auto* d = new Deploy("Deploy",3, *toDefend().front(), *p);
        p->addOrderToList(d);
        reinforcementHolder -= 3;

    }


    for (int i = 0; i < toAttack().size(); i++) {

        
        auto* a = new Advance("Advance",toDefend().back()->getArmy(), toAttack()[i]->getPlayer(), toDefend().back(), toAttack()[i]);
        p->addOrderToList(a);


    }




}
string CheaterPlayer::getStrategyType() {
    return strategyType;
}


NeutralPlayer::NeutralPlayer(Player *p,string strategyType) : PlayerStrategy(p,strategyType) {}

vector<Territory*> NeutralPlayer::toAttack() {
    vector<Territory *> t;
    return t;
}


vector<Territory*> NeutralPlayer::toDefend() {
    vector<Territory *> t;
    return t;
}

void NeutralPlayer:: issueOrder(vector<Player*> players){
    cout << "Neutral player does nothing. No orders added to list"<<endl;
}
HumanPlayer::HumanPlayer(Player *p,string strategyType) : PlayerStrategy(p,strategyType){}


 bool HumanPlayer::validate(Territory *t) {
     if (find(p->getTerrorityList().begin(), p->getTerrorityList().end(), t) != p->getTerrorityList().end())
         return true;
     else
         return false;
 }




BenevolentPlayer::BenevolentPlayer(Player *p,string strategyType) : PlayerStrategy(p,strategyType){}
vector<Territory *> BenevolentPlayer::toDefend() {
    p->territorySorter();
    return p->getTerrorityList();
}
vector<Territory *> BenevolentPlayer::toAttack() {
    vector<Territory*> t;
    return t;
}

void BenevolentPlayer::issueOrder(vector<Player*> players) {
    // deploy orders until reinforcment

    int reinforcementHolder = p->getReinforcements();

    while (reinforcementHolder >= 3) {


        Deploy *d = new Deploy("Deploy",3, *toDefend().front(), *p);
        p->addOrderToList(d);
        reinforcementHolder -= 3;

    }


    for (int i = 0; i < p->getTerrorityList().size(); i++) {
        p->territorySorter();
        if (p->getTerrorityList().front()->getArmy() == p->getTerrorityList().back()->getArmy() ||
            p->getTerrorityList().back()->getArmy() - p->getTerrorityList().front()->getArmy() >= 3)
            break;
        else {
            int x = p->getTerrorityList().back()->getArmy() / 2;
            Advance *a = new Advance("Advance",x, p, p->getTerrorityList().back(), p->getTerrorityList().front());
            p->addOrderToList(a);
        }
    }

}