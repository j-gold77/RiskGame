//
// Created by jgold on 2021-11-26.
//

using namespace std;
#include <iostream>
#include <utility>
#include <algorithm>
#include "string"
#include "CommandProcessing.h"
#include <tuple>

Command::Command(std::string the_command) {
    setCommand(the_command);
};

void Command::setCommand(std::string command1) {
    this->command = command1;
}

void Command::setEffect(std::string effect1){
    this->effect = effect1;
}

string Command::getCommandString(){
    return this->command;
}

string Command::getEffectString(){
    return this->effect;
}







CommandProcessor::CommandProcessor(){
    possible_valid_commands_vector = {"loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit"};
    valid_commands_and_their_transitions_vector.emplace_back("start", make_pair("loadmap", "maploaded"));
    valid_commands_and_their_transitions_vector.emplace_back("maploaded", make_pair("loadmap", "maploaded"));
    valid_commands_and_their_transitions_vector.emplace_back("maploaded", make_pair("validatemap", "mapvalidated"));
    valid_commands_and_their_transitions_vector.emplace_back("mapvalidated", make_pair("addplayer", "playersadded"));
    valid_commands_and_their_transitions_vector.emplace_back("playersadded", make_pair("addplayer", "playersadded"));
    valid_commands_and_their_transitions_vector.emplace_back("playersadded", make_pair("gamestart", "assignreinforcement"));
    valid_commands_and_their_transitions_vector.emplace_back("assignreinforcement", make_pair("issueorder", "issueorders"));
    valid_commands_and_their_transitions_vector.emplace_back("issueorders", make_pair("issueorder", "issueorders"));
    valid_commands_and_their_transitions_vector.emplace_back("issueorders", make_pair("endissueorders", "executeorders"));
    valid_commands_and_their_transitions_vector.emplace_back("executeorders", make_pair("execorder", "executeorders"));
    valid_commands_and_their_transitions_vector.emplace_back("executeorders", make_pair("endexecorders", "assignreinforcement"));
    valid_commands_and_their_transitions_vector.emplace_back("executeorders", make_pair("win", "win"));
    valid_commands_and_their_transitions_vector.emplace_back("win", make_pair("replay", "start"));
    valid_commands_and_their_transitions_vector.emplace_back("win", make_pair("quit", "exit program"));
}

vector<Command*> CommandProcessor::readCommand() {
    vector<Command*> local_commands_vector;
    string temp_str;
    cout << "Please enter commands one after the other. When you are finished please enter in all caps \"END\"" << endl;
    while(true){
        cin >> temp_str;
        if(temp_str=="END"){
            break;
        }
        if (find(possible_valid_commands_vector.begin(), possible_valid_commands_vector.end(), temp_str) != possible_valid_commands_vector.end()){
            local_commands_vector.emplace_back(new Command(temp_str));
            cout << "Valid command. Successfully entered." << endl;
        }
        else {
            cout << "The command that you entered was an invalid command. Please enter another command or type \"END\" once finished." << endl;
        }
    }
    return local_commands_vector;
}

void CommandProcessor::getCommand(string filename) {
    //read from console
    if (filename.empty()){
        vector<Command*> local_commands_pointer_vector = readCommand();
        saveCommand(local_commands_pointer_vector);
        cout << "All entered commands successfully saved";
    }
        //read from filename
    else{
        auto* adapter = new FileCommandProcessorAdapter();
        vector<Command*> local_commands_pointer_vector = adapter->readCommand(filename);
        saveCommand(local_commands_pointer_vector);
        cout << "Finished with " << filename << endl;
    }
}

void CommandProcessor::saveCommand(vector<Command *> local_commands_vector){
    for (Command *command: local_commands_vector){
        commands_vector.emplace_back(command);
        cout << "Saved " << command->getCommandString() << std::endl;
    }
}

//returns state that it transitions to given current state and command that was entered (if it transitions to a different state)
string CommandProcessor::validate(Command* command1, string state) {
    std::vector<pair<string, string>> value_vector;
    for(auto it = valid_commands_and_their_transitions_vector.begin(); it != valid_commands_and_their_transitions_vector.end(); ++it){
        if(it->first==state){
            value_vector.emplace_back(it->second);
        }
    }
    for(auto it = value_vector.begin(); it != value_vector.end(); ++it){
        if(it->first==command1->getCommandString()){
            cout << "Command " << command1 << " has been validated.\nState has been changed to "<< it->second << endl;
            state = it->second;
            //ALSO NEED TO SAVE EFFECT HERE
            return state;
        }
        else {
            cout << "Command" << command1 << " could not be validated, state has not changed" << endl;
            return state;
        }
    }
    cout << "ERROR\nThe command could not be validated. State has not changed. Please try again with a different command" << endl;
    return state;
}


std::tuple<std::vector<std::string>, std::vector<std::string>, int, int> CommandProcessor::tournamentMode() {
    vector<string> validMaps = { "europe", "arctic", "haiti"};
    vector <string> validStrategies = { "aggressive", "benevolent", "neutral", "cheater" };
    vector<string> M, P;
    int G, D;

    while (true) {
        cout << "Please enter maps sequentially, seperated by an asterisk \'*\'" << endl;
        cout << "Note: must have between 1 and 5 maps" << endl;
        string maps = "";
        cin.clear();
        cin >> maps;
        std::transform(maps.begin(), maps.end(), maps.begin(), ::tolower);
        int i = 0;
        bool valid = true;

        //parse all of the strats entered seperated by a space
        string delimiter = "*";
        size_t pos = 0;
        std::string token;
        while ((pos = maps.find(delimiter)) != std::string::npos) {
            token = maps.substr(0, pos);
            M.emplace_back(token);
            maps.erase(0, pos + 1);
            cout << token << endl;
            if (!maps.find('*')) {
                M.emplace_back(maps);
            }
        }
        M.emplace_back(maps);

        if (M.size() > 5 || M.size() < 1) {
            cout << "sorry, you have entered too many or too little maps" << endl;
            valid = false;
        }

        else {
            //check to see if its a vaild map
            for (string theMap : M) {
                if (std::find(validMaps.begin(), validMaps.end(), theMap) != validMaps.end()) {
                }
                else {
                    cout << "sorry, map " << theMap << " is not a valid map, please re-enter your maps" << endl;
                    valid = false;
                    break;
                }
            }
        }
        //valid maps, move onto next
        if (valid) {
            cout << "Maps entered are valid" << endl;
            break;
        }
    }

    while (true) {
        //NOW FOR PLAYER STRATEGIES
        cout << "Please enter player strategies sequentially, seperated by an asterisk \'*\'" << endl;
        cout << "Note: must have between 2 and 4 player strategies" << endl;
        string strategies = "";
        cin.clear();
        cin >> strategies;
        std::transform(strategies.begin(), strategies.end(), strategies.begin(), ::tolower);
        int i = 0;
        bool valid = true;

        //parse all of the strats entered seperated by a space
        string delimiter = "*";
        size_t pos = 0;
        std::string token;
        while ((pos = strategies.find(delimiter)) != std::string::npos) {
            token = strategies.substr(0, pos);
            P.emplace_back(token);
            strategies.erase(0, pos + 1);
        }
        P.emplace_back(strategies);

        if (P.size() < 2 || P.size() > 4) {
            cout << "sorry, you have entered too many or too little strategies" << endl;
            valid = false;
        }
        else {
            //check to see if its a vaild strat
            for (string strat : P) {
                if (std::find(validStrategies.begin(), validStrategies.end(), strat) != validStrategies.end()) {
                }
                else {
                    cout << "sorry, player strategy " << strat
                        << " is not a valid strategy, please re-enter your player strategies" << endl;
                    valid = false;
                    break;
                }
            }
        }
        //valid strat, move onto next
        if (valid) {
            break;
        }
    }

    cout << "Please enter an amount of games to be played for each map, must be between 1 to 5 for each" << endl;
    while (true) {
        string temp;
        cin >> temp;
        G = stoi(temp);
        if (G < 1 || G>5) {
            cout << "Please enter a new one number within the boundaries";
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Please enter a max number of turns, must be between 10 and 50:" << endl;
        string temp = "";
        cin >> temp;
        D = stoi(temp);
        if (D < 10 || D>50) {
            cout << "Please enter a new one number within the boundaries";
        }
        else {
            break;
        }
    }

    //all infomation will be in M, P, G, D
    std::tuple<std::vector<std::string>, std::vector<std::string>, int, int> tempTuple = { M, P, G, D };
    return tempTuple;

}





std::vector<Command*> FileCommandProcessorAdapter::readCommand(std::string filename) {
    std::vector<Command*> final_commands;
    possible_valid_commands_vector = {"loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit"};
    std::vector<std::string> potential_commands = flr.readLineFromFile(filename);

    //validating that the commands are correct before returning them to the CommandProcessor, otherwise, skipping the item
    for(std::string str: potential_commands){
        if (find(possible_valid_commands_vector.begin(), possible_valid_commands_vector.end(), str) != possible_valid_commands_vector.end()){
            final_commands.emplace_back(new Command(str));
            std::cout << "Command \"" << str << "\" was valid. It has been successfully entered." << std::endl;
        }
        else{
            std::cout << "Command \"" << str << "\" was not valid. It will be skipped" << std::endl;
        }
    }
    return final_commands;
}



std::vector<std::string> FileLineReader::readLineFromFile(const std::string& filename) {
    std::vector<std::string> local_commands_vector;
    std::ifstream infile(filename);
    std::string line;
    while(std::getline(infile, line)){
        local_commands_vector.emplace_back(line);
    }
    return local_commands_vector;
}