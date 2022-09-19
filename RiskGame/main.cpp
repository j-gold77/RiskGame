/*
 Created by jgold on 2021-11-04.
 Assignment 2: Part 4 Orders.
 Class Comp 345 winter term 2021.
*/

///test driver for Orders class
#include <iostream>
#include "Map.h"
#include "GameEngine.h"
#include "CommandProcessing.h"
#include <string>
#include <vector>
#include <ctime>
using namespace std;

int main() {

    GameEngine g;

    //tournament mode or not
    bool t_mode = false;
    cout << R"(please enter "yes" or "no" to specify whether you want to enter tournament mode or not)" << endl;
    while (true) {
        string y_n = "";
        cin >> y_n;
        if (y_n == "yes") {
            t_mode = true;
            break;
        }
        else if (y_n == "no") {
            t_mode = false;
            break;
        }
        else cout << "Sorry that was not a valid entry. Please try again: " << endl;
    }

    if (t_mode) {
        g.tournamentGame();

    }
    else {

        g.startupPhase();
        g.mainGame();
    }

    return 0;
}

//    using std::cout;
//    using std::cin;
//    using std::endl;
//    using MMM::MapLoader;
//
//    vector<Card *> v; ///vector of cards to be used by deck and hand
//    Hand *h = new Hand(v, 0); ///pointer for hand class
//
//
//    auto *b = new BombCard("Bomb", 1); ///bomb card
//    auto *r = new ReinforcementCard("Reinforcement", 2); ///reinforcement card
//    auto *bl = new BlockadeCard("Blockade", 3); ///blockade card
//    auto *a = new AirliftCard("Airlift", 4); ///airlift card
//    auto *di = new DiplomacyCard("Diplomacy", 5); ///diplomacy card
//
//
//    ///creating deck by running a loop 10 times. each times adds 1 of each specific card type
//    for (int i = 0; i < 10; i++) {
//
//        v.push_back(b);
//        v.push_back(bl);
//        v.push_back(r);
//        v.push_back(a);
//        v.push_back(di);
//    }
//
//    Deck *d = new Deck(v, v.size());
//
//    ///printing deck
//
//    srand(time(0));
//    d->shuffle(v);
//    cout << *d;
//
//
//    ///loading in map file. it will populate with player
//    string file;
//
//    cout << "In order to start a game please enter a file name : ";
//    cin >> file;
//    auto *m = new MapLoader(file);
//    m->loadmap();
//
//
//    if (!m->validateMap()) {
//        cout << "Map Cannot be validated, and is now being in unloaded" << endl;
//        delete m;
//        m = nullptr;
//    }
////
//    cout << "Your map is loaded & valid and can now be used to play the game " << endl;
//
//    ///creating vector of players
//    vector<Player *> players;
//    ///populating vector
//    players = m->getListOfPlayers();
//
//
//
//    ///printing players
//    for (auto &player : players) {
//        cout << *player;
//
//    }
//
//    ///creating 2 terrtories just for testing
//    auto *t = new Territory(20, "Majorca", 4, 50);
//    auto *t2 = new Territory(20, "Canada", 4, 50);
//
//    ///Testing deploy order and validations
//
//    Order *deploOrder = new Deploy("Deploy");
//    Order *ad = new Advance("Advance");
//    Order *bomb = new Bomb("Bomb");
//    Order *air = new Airlift("Airlift");
//    Order *diplomacy = new Negotiate("Negotiate");
//
//    auto *p1 = new Player(*players.front());
//    auto *p2 = new Player(*players.back());
//
//    p1->executeOrder(*deploOrder, *p1, *p1->getTerrorityList().front(), *p1->getTerrorityList().front(), 50);
//}
//



//
//
//
//
//
//    int count =0;
//
////    for(int i=0; i<p1->getTerrorityList().size(); i++){
////        count++;
////        p1->getTerrorityList()[i]->addArmy(count);
////    }
////
////    p1->territorySorter();
////    for(int i=0; i<p1->getTerrorityList().size();i++){
////        cout << *p1->getTerrorityList()[i];
////    }
//
//
//
