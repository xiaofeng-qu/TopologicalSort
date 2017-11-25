#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <stdlib.h>
#include "Graph.hpp"
class menu{
private:
    std::string filePath;
    Graph newGraph;

public:
    menu();
    void popMenu();
    void getFilePath();
    void initGraph();
    void createGraph();
    void detectCycle();
    void topologicalSort();
    void printGraph();
};

#endif // MENU_HPP_INCLUDED
