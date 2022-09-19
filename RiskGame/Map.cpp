//
// Created by Mohit 2021-10-15
//

#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include "time.h"
#include "PlayerStretegy.h"
#include <cassert>

namespace MMM {




    //*****************************CONTINENT CLASS DEFINITION*******************************************


    //ostream operator definitions
    std::ostream &operator<<(std::ostream &strm, const Continent &c) {
        return strm << "C(continenet name: " << c.continentName << ", id: " << c.continentId << ", army bonus: "
                    << c.armyBonus << ")";
    }

    //istream operator definitions
    istream &operator>>(istream &ins, Continent &c) {
        ins >> c.continentId >> c.continentName >> c.armyBonus;
        return ins;
    }


    //default constructor
    Continent::Continent() : continentId(0), continentName(" "), armyBonus(0), listOfTerritoriesOfContinent(0) {

    }

    //parameterized constructor
    Continent::Continent(int cId, string cName, int aBonus) : continentId(cId), continentName(cName), armyBonus(aBonus),
                                                              listOfTerritoriesOfContinent(0) {
    }

    //copy constructor
    Continent::Continent(const Continent &other) {
        continentId = other.continentId;
        continentName = other.continentName;
        armyBonus = other.armyBonus;
        // not sure if this works
        *this = other;

    }

    //continent accessor methods
    int Continent::getContinentId() {
        return continentId;
    }

    string Continent::getContinentName() {
        return continentName;
    }

    int Continent::getArmyBonus() {
        return armyBonus;
    }

    vector<Territory *> Continent::getListOfContinentOfTerritories() {
        return listOfTerritoriesOfContinent;
    }

    //ads territory to continent list
    void Continent::addTerritoryToContinent(Territory *t) {
        listOfTerritoriesOfContinent.push_back(t);

    }

    // method to display continent and territories
    void Continent::displayContinentTerritories() {

        //cout << "DEBUG: TERRITORY CLASS, displayNeighbours() \n";
        cout << "continents list and size: " << listOfTerritoriesOfContinent.size() << "\n";

        for (int i = 0; i < listOfTerritoriesOfContinent.size(); i++) {
            cout << "territory: " << *listOfTerritoriesOfContinent[i] << "\n";
        }
        cout << "\n";
    }

    bool Map::validateNeighbour(Territory &t1, Territory &t2) {

        for (int i = 0; i < t1.getNeighboursList().size(); i++) {
            for (int j = 0; j < t2.getNeighboursList().size(); j++) {
                if (t1.getNeighboursList()[i] == t2.getNeighboursList()[j]) {
                    return true;
                }
            }
        }
        return false;
    }

    // overloading comtinent assigment operator
    Continent &Continent::operator=(const Continent &rhs) {
        if (this != &rhs)
            // 	iterate through whols list of neighbours and copy each one to the new objects list of neighbours
            for (int i = 0; i < rhs.listOfTerritoriesOfContinent.size(); i++) {
                *listOfTerritoriesOfContinent[i] = *rhs.listOfTerritoriesOfContinent[i];
            }
        return *this;
    }

    // continent deconstructor
    Continent::~Continent() {

    }

    //**************** MAP CLASS ******************


    // map class ostream operator
    std::ostream &operator<<(std::ostream &strm, const Map &t) {

        return strm << "M(" << t.worldName << t.amountOfCountries;
    }

    //map class insertion stream operator
    istream &operator>>(istream &ins, Map &m) {
        ins >> m.worldName >> m.amountOfCountries;
        return ins;

    }


    // default constructor
    Map::Map() : worldName("Unassigned"), amountOfCountries(0) {
    }


    //parameterized constructor
    Map::Map(string worldNameParam) : worldName(worldNameParam), amountOfCountries(0) {
    }

    //copy constructor
    Map::Map(const Map &other) {

        worldName = other.worldName;
        amountOfCountries = other.amountOfCountries;
        *this = other;

    }

    vector<vector<int>> Map::getAdjIntListMap() {
        return adjIntListMap;
    }

    //Map deconstrctor calls delete on the pointers of listofCountries and ListOfContinents
    Map::~Map() {
        for (int i = 0; i < listOfContinents.size(); i++) {
            //deletes value at pointers
            delete listOfContinents[i];
            //points pointer to 0 avoiding dangling pointers
            listOfContinents[i] = 0;
        }

        for (int i = 0; i < listOfCountries.size(); i++) {
            delete listOfCountries[i];
            listOfCountries[i] = 0;
        }


    }

    // returns continent list
    vector<Continent *> Map::getContinentList() {
        return listOfContinents;
    }

    // get amount of countries in list of countries
    int Map::getAmountOfCountries() {
        int size = listOfCountries.size();
        return size;
    }


    // adds territories to listOfCountries
    void Map::addToTerritoriesList(int id, string name, int continentId, int armyBonus) {
        Territory *t = new Territory(id, name, continentId, armyBonus);

        listOfCountries.push_back(t);
    }

    // adds territories to subgraph
    void Map::addContinentToSubGraph(int id, string name, int armyBonus) {
        Continent *c = new Continent(id, name, armyBonus);
        listOfContinents.push_back(c);
    }

    // displays continents and its territories
    void Map::displayContinentsAndItsTerritories() {

        for (int i = 0; i < listOfContinents.size(); i++) {
            cout << "THE CONTINENT TO BE AND ITS COUNTRIES ARE: " << *listOfContinents[i] << "\n";
            listOfContinents[i]->displayContinentTerritories();

        }
    }

    // display just list of countries
    void Map::displayListOfCountries() {
        for (int i = 0; i < listOfCountries.size(); i++) {
            cout << *listOfCountries[i] << "\n";

        }

    }

    // display list of countries and its neighbours
    void Map::displayListOfCountriesAndNeighbours() {
        for (int i = 0; i < listOfCountries.size(); i++) {
            cout << "BORDERS OF COUNTRY WITH ID:" << i + 1 << " :" << *listOfCountries[i] << "\n";

            listOfCountries[i]->displayNeighbours();

        }

    }


    //get territory refrence by ID
    Territory *Map::getReferenceTerritoryById(int id) {
        for (int i = 0; i < listOfCountries.size(); i++) {

            if (listOfCountries[i]->getId() == id) {

                return listOfCountries[i];
            }
        }


    }

    // get territory value by id
    Territory Map::getTerritoryById(int id) {

        for (int i = 0; i < listOfCountries.size(); i++) {

            if (listOfCountries[i]->getId() == id) {

                return *listOfCountries[i];
            }
        }
    }

    //add border to territory
    void Map::addBorderToTerritory(int borderId, int territoryId) {
        for (int i = 0; i < listOfCountries.size(); i++) {

            if (listOfCountries[i]->getId() == territoryId) {
                //cout << "DEBUG: MAP CLASS, addBorderToTerritory() in if statement \n";
                listOfCountries[i]->addNeighbours(getReferenceTerritoryById(borderId));
            }
        }

    }

    void Map::addTerritoryToAdjList(int borderTerritoryCounter, int borderNumberHolder) {

        adjIntListMap[borderTerritoryCounter].push_back(borderNumberHolder);

    }

    void Map::addVectorToAdjList() {
        vector<int> v;
        adjIntListMap.push_back(v);
    }

    //add territory to continent list
    void Map::addTerritoryToContinentList() {
        for (int i = 0; i < listOfContinents.size(); i++) {
            //	cout << "DEBUG: MAP CLASS, addTerritoryToContinentList() ";

            for (int k = 0; k < listOfCountries.size(); k++) {

                if (listOfCountries[k]->getCId() == listOfContinents[i]->getContinentId()) {
                    //cout << "DEBUG: MAP CLASS, addTerritoryToContinentList() in if statement \n";
                    listOfContinents[i]->addTerritoryToContinent(listOfCountries[k]);

                }
            }
        }


    }


    //main map validate method
    bool Map::validateMap() {

        //	cout << "COUT DEBUG : Map::validateMap() -> at begininng of methode" << endl;

        int boolSize = getAmountOfCountries() + 1;
        vector<bool> visited(boolSize, false);

        bool validateFinale = validate(visited);

        // cout << "COUT DEBUG : Map::validateMap() after whole map validate before subvalidate"<< endl;

        if (validateFinale) {
            int sizeC = getContinentList().size();

            for (int i = 0; i < sizeC; i++) {
                validateFinale = validateSub(visited, *getContinentList()[i]);
                if (validateFinale == false) { break; }
            }

        }


        if (validateFinale) {

            cout << "MAP IS VALID \n";
            return true;

        } else {
            cout << "MAP IS INVALID \n";
            return false;
        }
    }

    //dfs traversal
    void Map::dfs(int start, vector<bool> &visited) {
        stack<int> stack;

        stack.push(start);
        visited[start] = true;

        while (!stack.empty()) {
            int node = stack.top();
            stack.pop();


            for (int neighbour : adjIntListMap[node]) {
                if (!visited[neighbour]) {
                    stack.push(neighbour);
                    visited[neighbour] = true;
                }

            }

        }

    }

    //dfs traversal
    void Map::dfsSub(int start, vector<bool> &visited, Continent &c) {
        stack<int> stack;

        stack.push(start);
        visited[start] = true;

        while (!stack.empty()) {
            int node = stack.top();
            stack.pop();


            for (int neighbour : adjIntListMap[node]) {

                if (!visited[neighbour]) {
                    for (int i = 0; i < c.getListOfContinentOfTerritories().size(); i++) {
                        if (neighbour == c.getListOfContinentOfTerritories()[i]->getId()) {
                            stack.push(neighbour);
                            visited[neighbour] = true;
                        } else continue;
                    }
                }

            }

        }

    }

    // validate method of Map Loader
    bool Map::validate(vector<bool> &visited) {
        int territoryCounter = getAmountOfCountries() + 1;
        cout << "COUT DEBUG, in Map:: validate() -> territory counter = " << territoryCounter << endl;

        for (int i = 1; i < territoryCounter; i++) {
            dfs(i, visited);

            cout << "After dfs on i= " << i << endl;
            for (int j = 1; j < territoryCounter; j++) {

                if (!visited[j]) {
                    cout << "territory with id " << i << " was unconnected \n";
                    return false;
                }


            }


            for (int j = 1; j < territoryCounter; j++) {

                visited[j] = false;
            }


        }
        return true;
    }

    // validate method of Map Loader
    bool Map::validateSub(vector<bool> &visited, Continent &c) {
        int territoryCounter = getAmountOfCountries() + 1;

        for (int i = 1; i < territoryCounter; i++) {

            for (int k = 0; k < c.getListOfContinentOfTerritories().size(); k++) {
                if (c.getListOfContinentOfTerritories()[k]->getId() == i) {
                    dfsSub(i, visited, c);
                } else continue;


                for (int j = 1; j < territoryCounter; j++) {
                    for (int i = 0; i < c.getListOfContinentOfTerritories().size(); i++) {

                        if (c.getListOfContinentOfTerritories()[i]->getId() == j) {
                            if (!visited[j]) {
                                cout << "territory with id " << i << " was unconnected \n";
                                return false;
                            }
                        }
                    }
                }
            }

            for (int j = 1; j < territoryCounter; j++) {

                visited[j] = false;
            }


        }
        return true;
    }


    Map &Map::operator=(const Map &rhs) {
        if (this != &rhs) {
            // 	iterate through whols list of countries and copy each one to the new objects list of neighbours
            for (int i = 0; i < rhs.listOfCountries.size(); i++) {
                *listOfCountries[i] = *rhs.listOfCountries[i];
            }

            for (int i = 0; i < rhs.listOfContinents.size(); i++) {
                *listOfContinents[i] = *rhs.listOfContinents[i];
            }

        }

        return *this;
    }

    vector<Player *> Map::getListOfPlayers() {
        return listOfPlayers;
    }





    // MAP LOADER CLASS DEFINITIONS



    //default contrcutor
    MapLoader::MapLoader() : fileName(" "), graph(new Map()) {
        cout << "Map Loader default constructor invoked \n";
    }

    //parametrized constrcutor
    MapLoader::MapLoader(string filenameParam) : fileName(filenameParam), graph(new Map("World Map")) {
        cout << "Map Loader parameterized constructor invoked \n";
    }

    std::ostream &operator<<(std::ostream &strm, const MapLoader &t) {
        return strm << "ML(" << "File Name: " << t.fileName << "File Validity" << t.isMapValid;
    }

    istream &operator>>(istream &ins, MapLoader &t) {
        ins >> t.fileName;
        return ins;
    }


    //destructor
    MapLoader::~MapLoader() {

        graph->~Map();
        delete graph;
        graph = 0;

    }

    Map *MapLoader::getMap() {
        return graph;
    }

    // once load map is called returns bool if map is valid or false
    bool MapLoader::getIsMapValid() {
        return isMapValid;
    }


    //MapLoader load function that reads in the file and creates territoriesobject addig them to the map
    void MapLoader::loadmap(bool t_mode, vector<string> playerStrats) {
        cout << "*********LOADING THE MAP***********";

        myFile.open(fileName, ios::in);
        if (myFile.is_open()) {

            // booleans to verifiy if we are in the correct sections;
            bool continentSection = false;
            bool territorySection = false;
            bool borderSection = false;
            bool validateFinale = true;
            std::vector<std::vector<int>> adjIntList;

            int continentCounter = 1;
            int territoryCounter = 1;
            int borderTerritoryCounter = 1;

            string holder;
            while (getline(myFile, holder)) {

                //if checks to skip lines that are only comments in the map file and to determine what section we're in the map file

                if (holder.find(";") != std::string::npos || holder.find(".") != std::string::npos || holder.empty()) {
                    continue; // dont really need this u just need an elf system.
                }

                //in continent section
                if (holder.find("[continents]") != std::string::npos) {
                    continentSection = true;
                    territorySection = false;
                    borderSection = false;
                    cout << "found Conti \n";

                    continue;
                }
                    //in countrie section
                else if (holder.find("[countries]") != std::string::npos) {
                    continentSection = false;
                    territorySection = true;
                    borderSection = false;
                    cout << "found Terri \n";
                    continue;
                }
                    // in border section
                else if (holder.find("[borders]") != std::string::npos) {
                    continentSection = false;
                    territorySection = false;
                    borderSection = true;
                    cout << "Border time \n";
                    continue;
                }

                    // assining continents to subgraph
                else if (continentSection == true) {

                    string arr[3];
                    int i = 0;
                    stringstream ssin(holder);
                    while (ssin.good() && i < 3) {
                        ssin >> arr[i];
                        ++i;
                    }

                    int armyBonus = std::stoi(arr[1]);


                    graph->addContinentToSubGraph(continentCounter, arr[0], armyBonus);
                    continentCounter++;

                } else if (territorySection == true) {
                    string arr[5];
                    int i = 0;
                    stringstream ssin(holder);
                    while (ssin.good() && i < 5) {
                        ssin >> arr[i];
                        ++i;
                    }


                    int continentIdHolder = std::stoi(arr[2]);

                    graph->addToTerritoriesList(territoryCounter, arr[1], continentIdHolder, 0);

                    territoryCounter++;

                } else if (borderSection == true) {
                    // push vectors of int to the amount of teeritores +1 because we will start index at one
                    for (int i = 0; i < territoryCounter; i++) {
                        vector<int> v;
                        graph->addVectorToAdjList();

                        adjIntList.push_back(v);

                    }


                    string space_delimiter = " ";
                    vector<string> words;

                    size_t pos = 0;
                    while ((pos = holder.find(space_delimiter)) != string::npos) {
                        words.push_back(holder.substr(0, pos));
                        holder.erase(0, pos + space_delimiter.length());
                    }
                    words.push_back(holder);


                    for (const auto &str : words) {


                        int borderNumberHolder = std::stoi(str);
                        if (borderNumberHolder == borderTerritoryCounter) {

                            continue;
                        } else {

                            graph->addBorderToTerritory(borderNumberHolder, borderTerritoryCounter);
                            graph->addTerritoryToAdjList(borderTerritoryCounter, borderNumberHolder);
                        }


                    }


                    borderTerritoryCounter++;

                }


            }

            graph->addTerritoryToContinentList();
            displaySubGraph();
            //displayListOfCountries();
            displayCountriesAndItsBorders();
            graph->addPlayer(t_mode, playerStrats);


        } else {
            cout << "file wont open";
        }

    }


    //displays continents and its territories
    void MapLoader::displaySubGraph() {
        //cout << "DEBUG: MAP LOADER CLASS, displaySubgraph() \n";
        cout << "*********DISPLAYING CONTINENTS AND THEIR COUNTRIES*********** \n";
        graph->displayContinentsAndItsTerritories();
    }

    //displays  all the territories territories
    void MapLoader::displayListOfCountries() {
        //cout << "DEBUG: MAP LOADER CLASS, displayListOfCountries() \n";
        cout << "*********DISPLAYING COUNTRIES*********** \n";
        graph->displayListOfCountries();
    }

    // the countries and their Border
    void MapLoader::displayCountriesAndItsBorders() {
        //cout << "DEBUG: MAP LOADER CLASS, displayListOfCountriesAndItsBorders() \n";
        cout << "*********DISPLAYING COUNTRIES AND THEIR NEIGHBOURS*********** \n";
        graph->displayListOfCountriesAndNeighbours();
    }

    bool MapLoader::validateMap() {
        return graph->validateMap();
    }

    vector<Player *> MapLoader::getListOfPlayers() {
        return graph->getListOfPlayers();
    }

    bool MapLoader::validationOfNeighbours(Territory &t1, Territory &t2) {
        return graph->validateNeighbour(t1, t2);
    }

    vector<Player *> Map::addPlayer(bool t_mode, vector<string> playerStrats) {
        int x = 0;

        if (t_mode) {
            for (string ps : playerStrats) {
                auto* p = new Player(ps);
                p->addReinforcements(50);
                listOfPlayers.push_back(p);
            }
            
        }
        else {
            cout << "How many players would you like to play with?. It must be between 2 and 6." << endl;
            std::cin >> x;
            while (x < 2 | x > 6) {
                cout << "Sorry you must enter a valid player size. Players must be between 2 and 6." << endl;
                cout << "How many players would you like to play with?. It must be between 2 and 6." << endl;
                std::cin >> x;
            }

            for (int i = 0; i < x; i++) {
                string name = "";
                cout << "Please enter player name here as a string.";
                cin >> name;
                auto* p = new Player(name);
                p->addReinforcements(50);
                listOfPlayers.push_back(p);
            }
        }


        while (!listOfCountries.empty()) {

            if (listOfCountries.size() >= listOfPlayers.size()) {
                for (int j = 0; j < listOfPlayers.size(); j++) {
                    Territory *t = listOfCountries.back();
                    listOfPlayers[j]->addTerritory(t);
                    t->setPlayer(listOfPlayers[j]);
                    listOfCountries.pop_back();
                }
            } else {
                cout << listOfCountries.size();
                auto *p = new Player("NeutralPlayer");
                PlayerStrategy *neutral = new NeutralPlayer(p,"Neutral");
                p->setStrategy(neutral);
                for (int i = 0; i < listOfCountries.size(); i++) {
                    p->addTerritory(listOfCountries[i]);
                    listOfCountries[i]->setPlayer(p);
                }
                listOfPlayers.push_back(p);
                break;
            }
        }

        vector<Card *> v; ///vector of cards to be used by deck and hand
        Hand *h = new Hand(v, 0); ///pointer for hand class


        auto *b = new BombCard("Bomb", 1); ///bomb card
        auto *r = new ReinforcementCard("Reinforcement", 2); ///reinforcement card
        auto *bl = new BlockadeCard("Blockade", 3); ///blockade card
        auto *a = new AirliftCard("Airlift", 4); ///airlift card
        auto *di = new DiplomacyCard("Diplomacy", 5); ///diplomacy card


        ///creating deck by running a loop 10 times. each times adds 1 of each specific card type
        for (int i = 0; i < 10; i++) {

            v.push_back(b);
            v.push_back(bl);
            v.push_back(r);
            v.push_back(a);
            v.push_back(di);
        }

        Deck *d = new Deck(v, v.size());

        ///printing deck

        srand(time(0));
        d->shuffle(v);


        for (int i = 0; i < 2; i++) {
            for (int i = 0; i < listOfPlayers.size(); i++) {
                Card *c = new Card(d->draw());
                listOfPlayers[i]->insertCardToHand(*c);
            }
        }


        for (int i = 0; i < listOfPlayers.size(); i++) {
            cout << *listOfPlayers[i];
        }

        return listOfPlayers;

    }
}