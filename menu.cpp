#include "menu.hpp"

menu::menu(){
    filePath = "";
    popMenu();
}

void menu::popMenu(){
    std::cout << "(1) Open input file." << std::endl; /* Prompt the user to enter an external input file name or use default file name. */
    std::cout << "(2) Print the graph." << std::endl;
    std::cout << "(3) Detect Cycle." << std::endl; /* prompt for selection */
    std::cout << "(4) Topological sort." << std::endl; /* prompt for entering new record */
    std::cout << "(5) Quit." << std::endl;

    int menuItem;
    std::cin >> menuItem;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch(menuItem){
        case 1:
                getFilePath();
                initGraph();
                createGraph();
                std::cout << std::endl;
                popMenu();
                break;
        case 2:
                printGraph();
                std::cout << std::endl;
                popMenu();
                break;
        case 3:
                detectCycle();
                std::cout << std::endl;
                popMenu();
                break;
        case 4:
                topologicalSort();
                std::cout << std::endl;
                popMenu();
                break;
        case 5:
                exit(0);
        default:
                std::cout << "No such option. Please choose from 1-5.\n" << std::endl;
                menu();
                break;
    }
}

void menu::getFilePath(){
    std::cout << "Please input your text file path: ";
    getline(std::cin, filePath);
}

void menu::initGraph(){
    newGraph.initGraph();
}

void menu::createGraph(){
    int node1, node2;
    float weight;
    std::ifstream infile(filePath);
    while(infile >> node1 >> node2 >> weight){
//        std::cout << node1 << " " << node2 << " " << weight << std::endl;
        newGraph.addEdge(node1, node2, weight);
    }
    infile.close();
}

void menu::detectCycle(){
    bool hasCycle = newGraph.detectCycle();
    if(!hasCycle) std::cout << "No Cycle" << std::endl;
}

void menu::topologicalSort(){
    newGraph.topologicalSort();
}

void menu::printGraph(){
    newGraph.printGraph();
    std::cout << std::endl;
}
