#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>

using namespace std;

class Graph {
public:
    int contentProvider;
    unordered_map<int, vector<int>> graph;
    unordered_map<int, unordered_set<int>> graph_set;
    Graph(int graphStartNode, unordered_map<int, vector<int>> inputGraph, unordered_map<int, unordered_set<int>> inputGraph_set) {
        contentProvider = graphStartNode;
        graph = inputGraph;
        graph_set = inputGraph_set;
    }
};
#endif
