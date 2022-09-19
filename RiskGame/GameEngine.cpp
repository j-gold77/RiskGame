//
// Created by Logan McMullen on 2021-10-11.
//

#include <iostream>
#include "GameEngine.h"
#include <algorithm>
#include <tuple>

using std::make_pair;
using std::vector;
using MMM::MapLoader;

GameEngine::GameEngine() {
    state = "start";
    CommandProcessor* cp = new CommandProcessor();
}

void GameEngine:: readCommand(string filename){
    cp->getCommand(filename);
}

void GameEngine::ProcessCommand(Command* commandPointer) {
    this->state = cp->validate(commandPointer, this->state);
}

string GameEngine::getState(){
    return state;
}
void GameEngine::setState(string state1){
    this->state= state1;
    cout << "State has been changed to \"" << state1 << "\".";
}

GameEngine::GameEngine(const GameEngine &g1){
    this->valid_commands_vector=g1.valid_commands_vector;
    this->state=g1.state;
}

void GameEngine::transition(string state1) {
    setState(state1);
}

void GameEngine::loadMap(string map, bool tMode, vector<string> playerStrats) {
    string file;
    if (map == "") {
        ///loading in map file. it will populate with player
        cout << "************* LOADING MAP PHASE **************\n" << endl;
        cout << "Loading map";

        cout << "In order to start a game please enter a file name.";
        cout << "(You have the choice between arctic and europe, please enter you selection: )" << endl;
        cin >> file;
    }
//        if (file == "arctic") {
//            file = R"(F:\Desktop\RiskGame legit\cmake-build-debug\arctic.map)";
//        }
//        else if (file == "europe") {
//            file = R"(F:\Desktop\RiskGame legit\cmake-build-debug\europe.map)";
//        }
//    }
//    else
//        file = "F:\\Desktop\\RiskGame\\cmake-build-debug\\" + map + ".map";

        this->ml = new MapLoader(file);
        this->ml->loadmap(tMode, playerStrats);

        cout << "************* VALIDATING MAP PHASE **************\n" << endl;
        if (!this->ml->validateMap()) {
            cout << "Map Cannot be validated, and is now being in unloaded" << endl;
            delete this->ml;
            this->ml = nullptr;
        }
        cout << "Your map is loaded & valid and can now be used to play the game " << endl;
    }



void GameEngine::gameStart() {
    ///Using GameStart command
    cout << "************* USING GAMESTART COMMAND PHASE**************\n" << endl;
    cout << "randomly defining order of play" << endl;
    if(this->ml != nullptr){

        playerVector = this->ml->getListOfPlayers();
        cout << playerVector.size();
        int i=1;
        for (Player* players: playerVector){
            this->player_order.emplace_back(players->GetName(), i);
            i++;
        }
        for (int counter = player_order.size() - 1; counter >= 0; counter--) {
            if(!(player_order.at(counter).first=="Neutral")){
                cout << "Player "<< player_order.at(counter).first << " has order of play " << player_order.at(counter).second << endl;
            }
        }
    }
    setState("play");
}




//PART 2
void GameEngine::startupPhase() {
    //1) Map is loaded
    //2) Map is validated
    //3) Players are added and asked for their names
    //4A) Territories fairly distributed
    //4c) give 50 initial armies to the players
    //4d) let each player draw 2 initial cards from the deck using draw() method
    loadMap("", false, *new vector<string>());
    //4b) randomly determined order of play for each player
    //4e) switch the game to the play phase
    gameStart();
    reinforcementPhase();
}

void GameEngine::reinforcementPhase() {
    
    
    for(int i=0; i<playerVector.size(); i++){
        int x = playerVector[i]->getTerrorityList().size();
        int y = x / 3;
        if(y == 0){
            playerVector[i]->addReinforcements(3);
            cout << 3 << " reinforcements added to " << playerVector[i]->GetName() << endl;

        }
        else {
            playerVector[i]->addReinforcements(y);
            cout << y << " reinforcements added to " << playerVector[i]->GetName() << endl;
        }
    }


}



void GameEngine::test() {

    vector<Player*> list_of_players = this->ml->getListOfPlayers();
    vector<Territory*> t = vector<Territory*>();

    for(int i=0; i<list_of_players.size();i++){
        cout << list_of_players[i]->GetName() << " Can attack the following territories" << endl;
        t= list_of_players[i]->toDefend();
        for(int j=0; j<t.size();j++){
            cout << j<<  ") " << *t[j];
        }
    }
}


void GameEngine::executionPhase() {

    

    for(int i=0; i<playerVector.size();i++){
        for(int j=0; j<playerVector[i]->getOrders().size();j++){
            playerVector[i]->executeOrder(*playerVector[i]->getOrders()[j],
                                             *playerVector[i]->getOrders()[j]->getPlayer(),
                                             *playerVector[i]->getOrders()[j]->getSourceTerritory(),
                                             *playerVector[i]->getOrders()[j]->getTargetTerritory(),
                                             playerVector[i]->getOrders()[j]->getArmies());
        }
    }

}

void GameEngine::issueOrderPhase() {
   

    for(int i=0;i<playerVector.size();i++){
        playerVector[i]->issueOrder(playerVector);
    }
}

bool GameEngine::playerWon(){
    
    cout << "DEBUG IN playerWon() -> LIST OF PLAYERS SIZE:  " << playerVector.size() << endl;
    for (int i = 0; i < playerVector.size(); i++) {

        cout << playerVector[i]->GetName() << endl;


    }

    if(playerVector.size()==1) {
        cout << playerVector.front()->GetName() << " Has won!!!!!";
        return true;
    }
    else
        cout <<  "Game Goes On" << endl;
        return false;
}


void GameEngine::tournamentGame() {
    std::tuple<vector<string>, vector<string>, int, int> tempTuple = cp->tournamentMode();
    vector<PlayerStrategy*> psVector;

    //first column containing blank space and the maps
    vector<vector<string>> resultsColumns;
    vector<string> tempVector;
    tempVector.emplace_back("");
    for (string typeMap : std::get<0>(tempTuple)) {
        tempVector.emplace_back(typeMap);
    }
    resultsColumns.emplace_back(tempVector);

    //How many games per map
    for (int j = 0; j < std::get<2>(tempTuple); ++j) {
        vector<string> tempVector2;
        //builing the results column
        tempVector2.emplace_back("Game " + to_string(j + 1));

        //how many maps
        for (string typeMap : std::get<0>(tempTuple)) {
            loadMap(typeMap, true, std::get<1>(tempTuple));
            gameStart();
            reinforcementPhase();

            //how many players on each map
            int k = 0;
            for (string typeStrat : std::get<1>(tempTuple)) {
                if (typeStrat == "aggresive") {
                    psVector.emplace_back(new AggressivePlayer(playerVector.back(), "Aggressive"));
                };
                if (typeStrat == "benevolent") {
                    psVector.emplace_back(new BenevolentPlayer(playerVector.back(), "Benevolent"));
                };
                if (typeStrat == "cheater") {
                    psVector.emplace_back(new CheaterPlayer(playerVector.back(), "Cheater"));
                };
                if (typeStrat == "neutral") {
                    psVector.emplace_back(new NeutralPlayer(playerVector.back(), "Neutral"));
                };
                playerVector.at(k)->setStrategy(psVector.back());
                cout << playerVector.at(k)->getPlayerStrategy() << endl;
                ++k;
            }

            int count = 0;
            cout << "COUNT = " << std::get<3>(tempTuple) << endl;
            while (!playerWon() || count > std::get<3>(tempTuple)) {
                cout << "COUNT = " << count << "legit " << endl;
                for (int i = 0; i < playerVector.size(); i++) {

                    playerVector[i]->setPlayerDiplomacyNull();
                    playerVector[i]->setOrdersToEmpty();
                }
                cout << "*********************************Turn : " << count << " begins now ***********************************" << endl;
                cout << "************************************ ISSUING ORDER PHASE*****************************************" << endl;
                cout << "Numbers of Players in Game: " << playerVector.size() << endl;
                for (int i = 0; i < playerVector.size(); i++) {

                    cout << "Player " << playerVector[i]->GetName() << " Will begin Issuing Order: " << endl;
                    cout << playerVector[i]->GetName() << "HERE";
                    playerVector[i]->issueOrder(playerVector);
                }
                cout << "************************************ EXECUTING ORDER PHASE*****************************************" << endl;
                for (int i = 0; i < playerVector.size(); i++) {
                    cout << "Player " << playerVector[i]->GetName() << " Will begin Executing Order: " << endl;
                    for (int j = 0; j < playerVector[i]->getOrders().size(); j++) {
                        playerVector[i]->executeOrder(*playerVector[i]->getOrders()[j],
                            *playerVector[i]->getOrders()[j]->getPlayer(),
                            *playerVector[i]->getOrders()[j]->getSourceTerritory(),
                            *playerVector[i]->getOrders()[j]->getTargetTerritory(),
                            playerVector[i]->getOrders()[j]->getArmies());
                    }
                }
                cout << "************************************ REINFORCEMENT PHASE*****************************************" << endl;
                reinforcementPhase();
                count++;
                eliminatePlayers();

            }
            cout << "Winner: " << playerVector[0]->GetName() << endl;
            tempVector2.emplace_back(playerVector[0]->GetName());
        }
        resultsColumns.emplace_back(tempVector2);
    }

    //output to file results of tournament
    ofstream myfile;
    myfile.open("F:\\Desktop\\RiskGame legit\\cmake-build-debug\\gameLog.txt");

    myfile << "Tournament mode:" << endl << "M: ";
    for (string typeMap : std::get<0>(tempTuple)) {
        myfile << typeMap << ", ";
    }
    myfile << endl << "P: ";
    for (string typeStrat : std::get<1>(tempTuple)) {
        myfile << typeStrat << ", ";
    }
    myfile << endl << "G: " << std::get<2>(tempTuple) << endl;
    myfile << "D: " << std::get<3>(tempTuple) << endl << endl;

    myfile << "Results" << endl;
    int i = 0;
    myfile << "\t\t";
    for (int j = 0; j < resultsColumns.at(0).size(); j++) {
        for (int i = 0; i < resultsColumns.size();i++) {
            myfile << resultsColumns.at(i).at(j) << " | " << "\t";
        }
        myfile << endl << "----------------------------------------------------------------" << endl;

    }
    myfile.close();

}



void GameEngine::mainGame() {
    
    int count = 0;

    PlayerStrategy *ps = new HumanPlayer(playerVector.front(), "Human");
    PlayerStrategy *ps2 = new BenevolentPlayer(playerVector.back(), "Benevolent");
    playerVector.front()->setStrategy(ps);
    playerVector.back()->setStrategy(ps2);

    /*
    if(playerVector.front()->getPlayerStrategy()=="Neutral") {
        PlayerStrategy* ps3 = new NeutralPlayer(playerVector.front(), "Neutral");
        playerVector.front()->setStrategy(ps3);
    }
    */
    //test 
    


    while (!playerWon()){
        for (int i = 0; i < playerVector.size(); i++) {
        
            playerVector[i]->setPlayerDiplomacyNull();
            playerVector[i]->setOrdersToEmpty();
        }
        cout << "*********************************Turn : " << count << " begins now ***********************************" << endl;
        cout << "************************************ ISSUING ORDER PHASE*****************************************" << endl;
        cout << "Numbers of Players in Game: " << playerVector.size() << endl;
        for (int i = 0; i < playerVector.size(); i++) {

            cout << "Player " << playerVector[i]->GetName() << " Will begin Issuing Order: " << endl;
            playerVector[i]->issueOrder(playerVector);
        }



        cout << "************************************ EXECUTING ORDER PHASE*****************************************" << endl;
        for (int i = 0; i < playerVector.size(); i++) {
            cout << "Player " << playerVector[i]->GetName() << " Will begin Executing Order: " << endl;
            for (int j = 0; j < playerVector[i]->getOrders().size(); j++) {
                playerVector[i]->executeOrder(*playerVector[i]->getOrders()[j],
                                                 *playerVector[i]->getOrders()[j]->getPlayer(),
                                                 *playerVector[i]->getOrders()[j]->getSourceTerritory(),
                                                 *playerVector[i]->getOrders()[j]->getTargetTerritory(),
                                                 playerVector[i]->getOrders()[j]->getArmies());
                cout <<  playerVector[i]->GetName()  << " Territories size is : " << playerVector.back()->getTerrorityList().size() << endl;
               
                for (int k = 0; k < playerVector[i]->getTerrorityList().size(); k++) {

                    cout<< "after executing: " << *playerVector[i]->getTerrorityList()[k] << endl;

                }



            }
        }
        cout << "************************************ REINFORCEMENT PHASE*****************************************" << endl;
      reinforcementPhase();
      count++;
        eliminatePlayers();

    


    }




    cout << "Winner: " << playerVector[0]->GetName() << endl;;
}

void GameEngine::eliminatePlayers() {
    


    for(int i=0; i< playerVector.size();i++){
        if(playerVector[i]->getTerrorityList().empty()){
            cout << playerVector[i]->GetName() << " is eliminated!" << endl;
            playerVector.erase(remove(playerVector.begin(),playerVector.end(),playerVector[i]),playerVector.end());

           
        }
    }

  

}




