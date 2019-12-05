//
// Created by Sanchit Batra on 8/14/19.
//
// Edited by Veronica
// Thanks to C++ TAs for the help with bfs

#include "Traversals.h"
#include "Objects.h"
#include <algorithm>
#include <climits>
#include <list>
#include <deque>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
// returns length of shortest path

unordered_map<int, int> bfs(const Graph& graph, const vector<Client>& clients){
    vector<int> distances (graph.graph.size(), -1);
    distances[graph.contentProvider] = 0;
    deque<int> searchQueue(1, graph.contentProvider);
    while (!searchQueue.empty()) {
      int node = searchQueue.front();
      searchQueue.pop_front();
      for (int neighbor: graph.graph.at(node)) {
        if (distances[neighbor] == -1) {
          distances[neighbor] = distances[node] + 1;
          searchQueue.push_back(neighbor);
        }
      }
    }
    unordered_map<int, int> client_distances;
    for (const Client& client : clients) {
      client_distances[client.id] = distances[client.id];
    }
    return client_distances;
}

//returns shortest path
unordered_map<int, vector<int>> bfs_path(const Graph& g, const vector<Client>& c){
    unordered_map<int, vector<int>> paths = unordered_map<int, vector<int>>();

    size_t graphSize = g.graph.size();
    vector<int> priors = vector<int>(graphSize, -1);
    //finds the parents
    deque<int> searchQueue (1, g.contentProvider);
    while(!searchQueue.empty()) {
      int node = searchQueue.front();
      searchQueue.pop_front();
      for (int neighbor : g.graph.at(node)) {
        if (priors[neighbor] == -1 && neighbor != g.contentProvider) {
          priors[neighbor] = node;
          searchQueue.push_back(neighbor);
        }
      }
    }

    //finds paths

    for(Client client: c){
        //finds path for given client
        vector<int> path = vector<int>();
        int current_node = client.id;
        while (current_node != -1) {
            path.push_back(current_node);
            current_node = priors[current_node];
        }
        //pushes back path
         reverse(path.begin(), path.end());

        paths[client.id] = path;
    }

    return paths;
}
