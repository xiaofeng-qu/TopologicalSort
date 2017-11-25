#include "Graph.hpp"
// Default constructor
Graph::Graph(){
    initGraph();
}
// Initialized the Graph
void Graph::initGraph(){
    std::pair<int, float> newPair(-1, 0.0);
    std::list<std::pair<int,float>> newList;
    isDag = true;
    newList.push_back(newPair);
    adjList.assign(101, newList);
    visitArr.assign(101, std::pair<int, bool>(-1, false));
    inDegree.assign(101, std::pair<int, int>(-1, 0));
    numOfNode = 0;
}
// Function to add edge to the adjacency list
void Graph::addEdge(int node1, int node2, float weight){
    int index = hashf(node1);
    if(adjList[index].front().first == node1){
        addEdgeHelper(index, node2, weight);
    }
    else{
        adjList[index].front().first = node1;
        visitArr[index].first = node1;
        addEdgeHelper(index, node2, weight);
        inDegree[index].first = node1;
        ++numOfNode;
    }
    index = hashf(node2);
    if(inDegree[index].first == node2){
        ++inDegree[index].second;
    }else{
        inDegree[index].first = node2;
        ++inDegree[index].second;
    }
    if(adjList[index].front().first != node2){
        adjList[index].front().first = node2;
        visitArr[index].first = node2;
        ++numOfNode;
    }
}

// Helper function to add edge to the adjacency list, the edge is insert based on weight
void Graph::addEdgeHelper(int index, int node, float weight){
    std::pair<int, float> newPair(node, weight);
    std::list<std::pair<int, float>>::iterator it;
//    for(it=adjList[index].begin(); it!=adjList[index].end(); ++it){
//        if(it->first == node){
//            it->second = weight;
//        }
//    }
    for(it=adjList[index].begin(); it!=adjList[index].end(); ++it){
        if(it->second >= weight){
            adjList[index].insert(it, newPair);
            return;
        }
    }
    adjList[index].push_back(newPair);
}

// Function to delete an edge
void Graph::delEdge(int node1, int node2){
    int index = hashf(node1);
    std::list<std::pair<int, float>>::iterator it;
    for(it=adjList[index].begin(); it!=adjList[index].end(); ++it){
        if(it->first==node2){
            adjList[index].erase(it);
            return;
        }
    }
}

// Topological sort
void Graph::topologicalSort(){
    if(isDag) std::cout << "Sorting: " << std::endl;
    else{
        std::cout << "The graph is not a DAG. It cannot be sorted." << std::endl;
        return;
    }
    for(int i=1; i<= numOfNode; i++){
        if(inDegree[i].second!=0){
            continue;
        }
        else{
            topologicalSortHelper(adjList[i].front().first);
        }
    }
    while(!tplgcSort.empty()){
        std::cout << tplgcSort.top() << " ";
        tplgcSort.pop();
    }
    std::cout << std::endl;
    visitArr.assign(101, std::pair<int, bool>(-1, false));
}

// Topological sort helper function
void Graph::topologicalSortHelper(int node){
    int index = hashf(node);
    std::list<std::pair<int, float>>::iterator it;
    it = adjList[index].begin();
    visitArr[index].second = true;
    ++it;
    for(; it!=adjList[index].end(); it++){
        if(visitArr[hashf(it->first)].second == true){
            continue;
        }else{
            topologicalSortHelper(it->first);
        }
    }
    tplgcSort.push(node);
}

// Print the graph
void Graph::printGraph(){
    for(int i=1; i<=numOfNode; ++i){
        std::list<std::pair<int, float>>::iterator it;
        for(it=adjList[i].begin(); it!=adjList[i].end();){
            std::cout << it->first;
            if(++it!=adjList[i].end()){
                std::cout << "->";
            }
        }
        std::cout << std::endl;
    }
}

// Cycle detection function
bool Graph::detectCycle(){
    isDag = true;

    for(int i=1; i<= numOfNode; i++){
        detectCycleHelper(adjList[i].front().first);
    }
    cycleDetector.clear();
    visitArr.assign(101, std::pair<int, bool>(-1, false));
    return !isDag;
}

// Cycle detection helper function
void Graph::detectCycleHelper(int node){
    cycleDetector.push_back(node);
    int index = hashf(node);
    std::list<std::pair<int, float>>::iterator it;
    it = adjList[index].begin();
    visitArr[index].second = true;
    ++it;
    for(; it!=adjList[index].end(); it++){
        if(visitArr[hashf(it->first)].second == true){
            std::list<int>::iterator intit;
            intit = std::find(cycleDetector.begin(), cycleDetector.end(), it->first);
            if(intit!=cycleDetector.end()){
                isDag = false;
                std::cout << "Cycle is found: ";
                for(;intit!=cycleDetector.end();++intit){
                    std::cout << *intit << " ";
                }
                std::cout << it->first << std::endl;
            }
        }else{
            detectCycleHelper(it->first);
        }
    }
    cycleDetector.pop_back();
}
