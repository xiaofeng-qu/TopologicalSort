#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED
#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>

class Graph{
private:
    std::vector<std::list<std::pair<int, float>>> adjList;
    std::vector<std::pair<int, bool>> visitArr;
    std::vector<std::pair<int, int>> inDegree;
    std::stack<int> tplgcSort;
    std::list<int> cycleDetector;
    bool isDag;
    int numOfNode;
public:
    Graph();
    void initGraph();
    void addEdge(int, int, float);
    void addEdgeHelper(int, int, float);
    void delEdge(int, int);
    bool detectCycle();
    void detectCycleHelper(int);
    void topologicalSort();
    void topologicalSortHelper(int);
    void printGraph();
    int hashf(int node){
        return node%101;
    }
};

#endif // GRAPH_HPP_INCLUDED
