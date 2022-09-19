#ifndef  MAP_H
#define MAP_H
#include <string>
#include <vector>
#include <fstream>
#include "Player.h"


using namespace std;
namespace MMM{

    // Dummy Player Class Declaration
    class PlayerDummy {

    private :

        string name;

    public:

    };




    // Continent Class Declaration
    class Continent {
    private:
        int continentId;
        string continentName;
        int armyBonus;
        vector<Territory*> listOfTerritoriesOfContinent;

        //stream insurtion operator
        friend std::ostream& operator<<(std::ostream& strm, const Continent& t);
        friend istream& operator >>(istream& ins, Continent& t);

    public:

        //default constructor declaration
        Continent();

        //parameterized constructor declaration
        Continent(int cId, string cName, int aBonus);

        // copy constructor declaration
        Continent(const Continent& other);

        //Accessor Methods

        int getContinentId();

        string getContinentName();

        int getArmyBonus();

        vector<Territory*> getListOfContinentOfTerritories();



        //destructor declaration
        ~Continent();

        // adds territory to continent
        void addTerritoryToContinent(Territory* t);

        void displayContinentTerritories();

        // assignement operator overload
        Continent& operator = (const Continent& rhs);




    };

    // Map Class Declaration
    class Map {
    private:
        string worldName;
        vector<Territory*> listOfCountries;
        vector<Continent*> listOfContinents;
        vector<vector<int>> adjIntListMap;


        int amountOfCountries;
        vector<Player*>listOfPlayers;

        //why would I need stream insurtion operator
        friend std::ostream& operator<<(std::ostream& strm, const Map& t);
        friend istream& operator >>(istream& ins, Map& t);

    public:
        //default constrcutor
        Map();

        //parametirzedconstrcutor
        Map(string worldName);

        //copy constructor
        Map(const Map& other);

        //Accessor Methods
        string getWorldName();

        vector<Territory*> getListOfCountries();

        vector<vector<int>> getAdjIntListMap();






        //Mutator Methods

        //destructor
        ~Map();

        vector<Continent*> getContinentList();
        int getAmountOfCountries();

        //Add newly created territory to list
        void addToTerritoriesList(int id, string name, int continentId,int amryBonus);

        //Add territory to correct Continent
        void addContinentToSubGraph(int id, string name, int armybonus);

        //Add territory id to adjencyList
        void addTerritoryToAdjList(int borderTerritoryCounter, int borderNumberHolder);

        //add vector to adjencyList
        void addVectorToAdjList();

        //displays continents and its territories
        void displayContinentsAndItsTerritories();

        //display territories in a list
        void displayListOfCountries();

        void displayListOfCountriesAndNeighbours();
        bool validateNeighbour(Territory &t1, Territory&t2);

        Territory* getReferenceTerritoryById(int id);

        Territory getTerritoryById(int id);

        void addBorderToTerritory(int borderId, int territoryId);

        void addTerritoryToContinentList();

        //validate method for my whole map
        bool validateMap();

        //validates if from starting node we can reach all other nodes in Map
        void dfs(int start, vector<bool>& visited);

        //validates if from starting node we can reach all other nodes in subGraph
        void dfsSub(int start,vector<bool>& visited, Continent& c);

        // verifies if map is valid
        bool  validate( vector<bool>& visited);

        // verifies if subGraph is valid
        bool validateSub(vector<bool>& visited, Continent& c);

        //assignment operator
        Map& operator = (const Map& rhs);
        vector<Player*> addPlayer(bool, vector<string>);
        vector<Player*> getListOfPlayers();




    };

    // MapLoader Class Declaration
    class MapLoader {

    private:

        //private members
        Map * graph;
        string fileName;
        fstream myFile;
        bool isMapValid = true;


        friend std::ostream& operator<<(std::ostream& strm, const MapLoader& t);
        friend istream& operator >>(istream& ins, MapLoader& t);


    public:

        //default constructor
        MapLoader();

        //parametrized constructor
        MapLoader(string filenameParam);

        //copy constructor

        //destructor
        ~MapLoader();

        vector<Player*> getListOfPlayers();
        bool validationOfNeighbours(Territory &t1,Territory &t2);

        //Accessor
        Map* getMap();
        bool getIsMapValid();

        //loads map into play
        void loadmap(bool, vector<string>);

        //displays subgraph
        void displaySubGraph();

        //display list of coutries
        void displayListOfCountries();

        //display list of coutries and their borders
        void displayCountriesAndItsBorders();



        bool validateMap();
    };
}// end of MMM


#endif // end of MAP_H
