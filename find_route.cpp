#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <array>
#include <vector>
#include <set>
#include <queue>
#include "myFunctionsAndClasses.cpp"




//  -------------------------------------------------------------------

int main (int argc, char *argv[]) {

    std::string place1 = argv[2];
    std::string place2 = argv[3];
    std::string file_Name = argv[1];
    std::string x;
    if (argc == 5) {
        x = argv[4];        
    }

    // std::string inputFileName = enterFileName();
    // std::string inputFileName = argv[3];
    std::string inputFileName = file_Name;
    
    std::set<std::string> s;
    s = listOfAllPlaces(inputFileName);

    std::map<std::string, std::map<std::string, float>> finalDS;
    finalDS = _openFile_Read_ReturnDataStructure(inputFileName, s);



    // std::string willHeuristicBeThere;
    // std::cout << "Would you like to enter a heuristic txt file? (Y/N) ";
    // std::cin >> willHeuristicBeThere;

    // std::cout << willHeuristicBeThere;

    if (argc == 5) {
        std::map<std::string, float> heuristic = read_txt_andReturnHeuristic(x);
        heuristicSearch(place1, place2, finalDS, heuristic);        
    } else {
        uniformCostSearch(place1, place2, finalDS);
    }

    std::cout << "\n";



    return 0;

}

//  -------------------------------------------------------------------
