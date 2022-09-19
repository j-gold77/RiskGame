//
// Created by Logan McMullen on 2021-10-11.
//

#ifndef UNTITLED_GAMEENGINE_H
#define UNTITLED_GAMEENGINE_H

#include <map>
#include <vector>
#include "CommandProcessing.h"
#include "Player.h"
#include "Map.h"
using std::cout;
using std::string;

class GameEngine {
private:

    MMM::MapLoader* ml;
    MMM::Map* map;
    std::vector<Player*> playerVector;
    std::vector<std::pair<std::string, int>> player_order;
    std::vector<std::pair<std::string, std::pair<std::string, std::string>>> valid_commands_vector;
    std::vector<std::tuple<>> resultsVector;
    string state;
    CommandProcessor* cp = new CommandProcessor();
    void loadMap(string, bool, vector<string>);
    void gameStart();
    void setState(string);
public:
    GameEngine();
    void ProcessCommand(Command*);
    string getState();
    GameEngine(const GameEngine &g1);
    void transition(string);
    void readCommand(string);
    void startupPhase();
    void reinforcementPhase();
    void test();
    void executionPhase();
    void issueOrderPhase();
    void mainGame();
    void eliminatePlayers();
    bool playerWon();
    void tournamentGame();
//    void mainGame(){
//        cout<<"issure order phase;" << endl;
//        if (player.playerstrat == neutral){
//            issueorder(NULL);
//            continue;
//        }
//        if(player.strat == agrressive){
//            issueOrder(advance)
//        }
//    }
};




#endif //UNTITLED_GAMEENGINE_H