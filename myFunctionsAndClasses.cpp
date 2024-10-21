#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <array>
#include <vector>
#include <set>
#include <queue>
#include <iostream>



class PrintNode {

    private:

        std::string start;
        std::string end;
        float distance;
    
    public:

        PrintNode (std::string start, std::string end, float distance) {
            this->start = start;
            this->end = end;
            this->distance = distance;
        }

        std::string getStart () {
            return this->start;
        }

        std::string getEnd () {
            this->end;
        }

        float getDistance () {
            return this->distance;
        }

        void printInformation () {
            std::cout << this->start << " to " << this->end << ", " << this->distance << " km " << std::endl;
        }
};



class Node {

    private:
    
        std::string parent;
        std::string currentLocation;
        float distance;
        int slNo = 0;
        float distanceTravelledByParent;
        bool routeCanBeFound;
        bool nodePopped;


    public:

        Node (std::string parent, std::string currentLocation, float distance = 0, float distanceTravelledByParent = 0, bool routeCanBeFound = true, bool nodePopped = false) {
            this->parent = parent;
            this->currentLocation = currentLocation;
            this->distance = distance;
            this->distanceTravelledByParent = distanceTravelledByParent;
            this->routeCanBeFound = true;
            this->nodePopped = false;
        }
        
        void changeParent (std::string newParent) {
            this->parent = newParent;
        }

        std::string getParent () {
            return this->parent;
        }

        void changeLocation (std::string newLocation) {
            this->currentLocation = newLocation;
        }

        void changeDistance (float dist) {
            this->distance = dist;
        }

        void changeDistTravByParent (float dist) {
            this->distanceTravelledByParent = dist;
        }

        void changeNodePoppedStatus (bool x) {
            this->nodePopped = x;
        }

        bool getNodePoppedStatus () {
            return this->nodePopped;
        }



        void currentNodeInformation () {
            std::cout << "\nParent: " << this->parent << std::endl;
            std::cout << "Total Distance Travelled by Parent: " << this->distanceTravelledByParent << std::endl;
            std::cout << "Current Location: " << this->currentLocation << std::endl;
            std::cout << "Total Distance Travelled: " << this->distance << std::endl;
            std::cout << "Can Route be Found: " << this->routeCanBeFound << std::endl;
            std::cout << "Node Popped?: " << this->nodePopped << std::endl << std::endl;
        }

        float getDistance () {
            return this->distance;
        }

        std::string getLocation () {
            return this->currentLocation;
        }

        bool canRouteBeFound () {
            return this->routeCanBeFound;
        }

        float getDistanceTravelledByParent () {
            return this->distanceTravelledByParent;
        }

        void goToNextNode (std::map< std::string , std::map<std::string , float> > dataStructure, std::vector<Node> &fringe, std::vector<Node> &nodesPopped, std::vector<std::string> &nodesExpanded) {

            bool nodeAlreadyExpanded = false;

            
            for (auto i : nodesExpanded) {
                if (this->currentLocation == i) {
                    nodeAlreadyExpanded = true;
                }
            }

            if (!nodeAlreadyExpanded) {


                auto successors = dataStructure[this->currentLocation];

                for (auto i : successors) {
                    Node temp(this->currentLocation , i.first , (this->distance+i.second), this->distance, true);
                    if (fringe.size() == 0) {
                        fringe.push_back(temp);
                    } else {
                        int insertionIndex = 0;
                        for (auto i : fringe) {
                            if (i.getDistance() > temp.getDistance()) {
                                break;
                            }
                            insertionIndex++;
                        }
                        fringe.insert(fringe.begin() + insertionIndex, temp);
                    }
                }

                nodesExpanded.push_back(this->currentLocation);
            }

            this->parent = fringe[slNo+1].parent;
            this->currentLocation = fringe[slNo+1].currentLocation;
            this->distance = fringe[slNo+1].distance;
            this->distanceTravelledByParent = fringe[slNo+1].distanceTravelledByParent;

            this->slNo += 1;

            Node toBeAddedToNodesPopped(this->parent, this->currentLocation, this->distance, this->distanceTravelledByParent);

            nodesPopped.push_back(toBeAddedToNodesPopped);


        }



        void h_goToNextNode (std::map< std::string , std::map<std::string , float> > dataStructure, std::map<std::string, float> heuristic , std::vector<Node> &fringe, std::vector<Node> &nodesPopped, std::vector<std::string> &nodesExpanded) {

            bool nodeAlreadyExpanded = false;
            
            for (auto i : nodesExpanded) {
                if (this->currentLocation == i) {
                    nodeAlreadyExpanded = true;
                }
            }

            if (!nodeAlreadyExpanded) {

                auto successors = dataStructure[this->currentLocation];

                for (auto i : successors) {
                    // std::cout << i.first << " - " << heuristic[i.first] << std::endl;
                    Node temp(this->currentLocation , i.first , (i.second+heuristic[i.first]), this->distance, true);
                    fringe.push_back(temp);
                }

                nodesExpanded.push_back(this->currentLocation);
            }


            Node smallestElement(fringe[0].parent, fringe[0].currentLocation, fringe[0].distance, fringe[0].distanceTravelledByParent, fringe[0].routeCanBeFound, fringe[0].nodePopped);
            
            for (auto i : fringe) {
                if (i.distance < smallestElement.distance) {
                    smallestElement.parent = i.parent;
                    smallestElement.currentLocation = i.currentLocation;
                    smallestElement.distance = i.distance;
                    smallestElement.distanceTravelledByParent = i.distanceTravelledByParent;
                    smallestElement.routeCanBeFound = i.routeCanBeFound;
                    smallestElement.nodePopped = i.nodePopped;
                }
            }

            int indexOfSmallestElement = 0;

            for (auto i : fringe) {
                if (
                    smallestElement.parent == i.parent,
                    smallestElement.currentLocation == i.currentLocation,
                    smallestElement.distance == i.distance,
                    smallestElement.distanceTravelledByParent == i.distanceTravelledByParent,
                    smallestElement.routeCanBeFound == i.routeCanBeFound,
                    smallestElement.nodePopped == i.nodePopped
                ) {
                    break;
                } else {
                    indexOfSmallestElement++;
                }
            }
            
            fringe.erase(fringe.begin() + indexOfSmallestElement);

            
            fringe.insert(fringe.begin(), smallestElement);

            

            this->parent = fringe[0].parent;
            this->currentLocation = fringe[0].currentLocation;
            this->distance = fringe[0].distance;
            this->distanceTravelledByParent = fringe[0].distanceTravelledByParent;
            this->routeCanBeFound = fringe[0].routeCanBeFound;
            this->nodePopped = fringe[0].nodePopped;


            Node toBeAddedToNodesPopped(this->parent, this->currentLocation, this->distance, this->distanceTravelledByParent);

            nodesPopped.push_back(toBeAddedToNodesPopped);

            
        }



};












std::string enterFileName () {
    std::string stg;
    std::cout << "Please Enter The File Name Correctly (with .txt extension)\nExample: input.txt\n-> ";
    std::cin >> stg;
    return stg;
}





void printSuccessor (std::map<std::string, float> small) {
    for (auto i : small) {
        std::cout << i.first << " - " << i.second << std::endl;
    }
}





std::map< std::string , std::map<std::string , float> > _openFile_Read_ReturnDataStructure (std::string inputFileName, std::set<std::string> listOfCities) {
    
    std::map< std::string , std::map<std::string , float> > myMap;

    for (auto i : listOfCities) {
        std::map<std::string , float> m;
        myMap[i] = m;
    }

    std::ifstream inFileHandler(inputFileName);

    std::string stg;
    std::string city1, city2;
    float distance;

    std::map<std::string, float> tempMap;

    while (getline(inFileHandler, stg)) {

        if (stg == "END OF INPUT") {break;}

        std::stringstream ss(stg);
        ss >> city1 >> city2 >> distance;
        
        //  For city 1;
        tempMap = myMap[city1];
        tempMap[city2] = distance;
        myMap[city1] = tempMap;

        //  For City 2;
        tempMap = myMap[city2];
        tempMap[city1] = distance;
        myMap[city2] = tempMap;        

    }

    inFileHandler.close();

    return myMap;

}





void finalsDsPrint (std::map<std::string, std::map<std::string, float>> abc) {
    for (auto i : abc) {
        std::cout << i.first << "\n-----------" << std::endl;
        for (auto j : i.second) {
            std::cout << j.first << " - " << j.second << std::endl;
        }
        std::cout << std::endl;
    }
}










std::set<std::string> listOfAllPlaces (std::string inputFileName) {

    std::set<std::string> mySet;
    std::ifstream inFileHandler(inputFileName);
    std::string stg, c1, c2;
    float distance;

    while (getline(inFileHandler, stg)) {
        if (stg == "END OF INPUT") {break;}
        std::stringstream ss(stg);
        ss >> c1 >> c2 >> distance;
        mySet.insert(c1);
        mySet.insert(c2);
    }

    inFileHandler.close();

    return mySet;

}






void printSet (std::set<std::string> mySet) {
    for (std::string i : mySet) {
        std::cout << i << std::endl;
    }
}





bool compareSmallest (float a, float b) {
    return a < b;
}




void printFringe (auto x) {
    for (auto i : x) {
        i.currentNodeInformation();
    }
}





void uniformCostSearch (std::string start, std::string end, std::map< std::string , std::map<std::string , float> > dataStructure) {

    std::cout << "\n";

    std::vector<Node> nodesPopped;
    std::vector<std::string> nodesExpanded;
    std::vector<Node> fringe;
    

    Node node("None", start, 0, 0);

    fringe.push_back(node);

    bool route = true;

    while (true) {
        
        node.goToNextNode(dataStructure, fringe, nodesPopped, nodesExpanded);

        if (node.getLocation() == end){
            break;
        } 
        else if (nodesPopped.size() == fringe.size()) {
            route = false;
            break;
        }
    }

    if (route == true) {        
        std::cout << "Number of Nodes Popped: " << (nodesPopped.size()+1) << std::endl;
        std::cout << "Number of Nodes Expanded: " << nodesExpanded.size() << std::endl;
        std::cout << "Number of Nodes Generated: " << fringe.size() << std::endl;
        std::cout << "Distance: " << node.getDistance() << " km" << std::endl;
        std::cout << "Route: " << std::endl;

        //  Backtracking
        std::vector<PrintNode> routeInfoStorage;

        Node reverseNode(node.getParent(), node.getLocation(), node.getDistance(), node.getDistanceTravelledByParent());

        PrintNode q(reverseNode.getParent(), reverseNode.getLocation(), (reverseNode.getDistance() - reverseNode.getDistanceTravelledByParent()));
        routeInfoStorage.insert(routeInfoStorage.begin(), q);

        while (reverseNode.getParent() != start && reverseNode.getDistanceTravelledByParent() != 0) {
            for (auto i : fringe) {
                if (i.getLocation() == reverseNode.getParent() && i.getDistance() == reverseNode.getDistanceTravelledByParent()) {
                    reverseNode.changeParent(i.getParent());
                    reverseNode.changeLocation(i.getLocation());
                    reverseNode.changeDistance(i.getDistance());
                    reverseNode.changeDistTravByParent(i.getDistanceTravelledByParent());


                    PrintNode p(reverseNode.getParent(), reverseNode.getLocation(), (reverseNode.getDistance() - reverseNode.getDistanceTravelledByParent()));
                    routeInfoStorage.insert(routeInfoStorage.begin(), p);
                    
                    break;
                }
            }
        }
        
        for (auto i : routeInfoStorage) {
            i.printInformation();
        }
    } else {
        std::cout << "Number of Nodes Popped: " << nodesPopped.size() << std::endl;
        std::cout << "Number of Nodes Expanded: " << nodesExpanded.size() << std::endl;
        std::cout << "Number of Nodes Generated: " << fringe.size() << std::endl;
        std::cout << "Distance: " << "Infinite" << std::endl;
        std::cout << "Route: None" << std::endl;
    }


    // std::cout << "\n\n\nPrinting Fringe\n\n\n";
    
    // for (auto i : fringe) {
    //     std::cout << i.getLocation() << " : " << i.getDistance() << std::endl;
    // }

}















































































//  --------------------------------------------------------------------------------



std::map<std::string, float> read_txt_andReturnHeuristic (std::string x) {

    std::string heuristicFileName = x;
    

    std::ifstream heuristicFileHandler(heuristicFileName);

    std::string stg;
    std::map<std::string, float> parsedHeuristic;
    std::string city;
    float heuristicValue;

    while (getline(heuristicFileHandler , stg)) {
        if (stg == "END OF INPUT") {
            break;
        }
        std::stringstream ss(stg);
        ss >> city >> heuristicValue;
        parsedHeuristic[city] = heuristicValue;
    }

    return parsedHeuristic;

}






void heuristicSearch (std::string start, std::string end, std::map< std::string , std::map<std::string , float> > dataStructure, std::map<std::string, float> heuristic) {

    std::cout << "\n";

    Node element("None", start, 0, 0, 1, 0);

    std::vector<Node> nodesPoppedVector;
    std::vector<std::string> nodesExpandedVector;
    std::vector<Node> fringe;

    int looper = 0;

    while (element.getLocation() != end || nodesExpandedVector.size() == fringe.size()) {
       
       //  Task 1 - Nodes Popped
        nodesPoppedVector.push_back(element);

        //  Task 2 - Nodes Expanded
        bool elementAlreadyExpanded = false;
        for (auto i : nodesExpandedVector) {
            if (i == element.getLocation()) {
                elementAlreadyExpanded = true;
            }
        }
        if (!elementAlreadyExpanded) {
            nodesExpandedVector.push_back(element.getLocation());
        }

        //  Task 3 - Fringe
        if (!elementAlreadyExpanded) {    
            // std::cout << element.getLocation() << std::endl;
            for (auto i : dataStructure[element.getLocation()]) {
                Node temp(element.getLocation(), i.first, (element.getDistanceTravelledByParent() + i.second+heuristic[i.first]), element.getDistance(), true, false);
                // Node temp(element.getLocation(), i.first, (i.second+heuristic[i.first]), element.getDistance(), true, false);
                fringe.push_back(temp);
            }
        }
        if ((nodesPoppedVector.size()) == (fringe.size()+1)) {
            // std::cout << "Route can not be found\n";
            break;
        }

        //  Task 4 - Next Element
        //  Find the index of the element with the smallest distance in the fringe
        int targetIndex = 0;
        int smallTarget = 0;

        for (int i = 0; i < fringe.size(); i++) {
            if (fringe[i].getNodePoppedStatus() == false) {
                smallTarget = i;
                break;
            }
        }

        Node elementWithSmallestDistance(fringe[smallTarget].getParent(), fringe[smallTarget].getLocation(), fringe[smallTarget].getDistance(), fringe[smallTarget].getDistanceTravelledByParent(), fringe[smallTarget].canRouteBeFound(), fringe[smallTarget].getNodePoppedStatus());
        
        for (int i = 0; i < fringe.size(); i++) {
            if (fringe[i].getNodePoppedStatus() == true) {
                // targetIndex = i+1;
                // elementWithSmallestDistance.changeDistance(fringe[i+1].getDistance());
                continue;
            }
            if (fringe[i].getDistance() <= elementWithSmallestDistance.getDistance()){
                targetIndex = i;
                elementWithSmallestDistance.changeDistance(fringe[i].getDistance());
            }
        }
        
        fringe[targetIndex].changeNodePoppedStatus(true);
        
        element.changeParent(fringe[targetIndex].getParent());
        element.changeLocation(fringe[targetIndex].getLocation());
        element.changeDistance(fringe[targetIndex].getDistance());
        element.changeDistTravByParent(fringe[targetIndex].getDistanceTravelledByParent());

        
        if (element.getLocation() == end) {
            // std::cout << "Task Unit Bruiser\n";
        }

    }

    if ((nodesPoppedVector.size()) != (fringe.size()+1)) {
        nodesPoppedVector.push_back(element);

        float distance = 0;

        Node reverseGear(element.getParent(), element.getLocation(), element.getDistance(), element.getDistanceTravelledByParent());

        Node element2("None", start, 0, 0, 1, 0);
        fringe.insert(fringe.begin(), element2);

        std::vector<PrintNode> routeStorageVector;


        do {
            PrintNode p(reverseGear.getParent(), reverseGear.getLocation(), dataStructure[reverseGear.getParent()][reverseGear.getLocation()]);
            routeStorageVector.insert(routeStorageVector.begin(), p);
            distance += dataStructure[reverseGear.getParent()][reverseGear.getLocation()];

            for (auto i : fringe) {
                if (i.getDistance() == reverseGear.getDistanceTravelledByParent() && i.getLocation() == reverseGear.getParent()) {
                    reverseGear.changeParent(i.getParent());
                    reverseGear.changeLocation(i.getLocation());
                    reverseGear.changeDistance(reverseGear.getDistance());
                    reverseGear.changeDistTravByParent(i.getDistanceTravelledByParent());
                }
            }
        } while (reverseGear.getLocation() != start);


        std::cout << "Nodes Popped: " << (nodesPoppedVector.size()) << std::endl;
        std::cout << "Nodes Expanded: " << nodesExpandedVector.size() << std::endl;
        std::cout << "Nodes Generated: " << (fringe.size()) << std::endl;
        std::cout << "Distance: " << distance << " Km"<< std::endl;
        std::cout << "Route: \n";
        for (auto i : routeStorageVector) {
            i.printInformation();
        }
    } else {
        std::cout << "Nodes Popped: " << (nodesPoppedVector.size()) << std::endl;
        std::cout << "Nodes Expanded: " << nodesExpandedVector.size() << std::endl;
        std::cout << "Nodes Generated: " << (fringe.size()+1) << std::endl;
        std::cout << "Distance: Infinite\n";
        std::cout << "Route: None\n";
    }

}