//
// Created by Sanchit Batra on 8/14/19.
//

#ifndef ETHICAL_ROUTING_TRAVERSALS_H
#define ETHICAL_ROUTING_TRAVERSALS_H

#include "Graph.h"
#include "Objects.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

//used to determine shorteset possible path
unordered_map<int, int> bfs(const Graph& g, const vector<Client>& c);
//returns shortest path
unordered_map<int, vector<int>> bfs_path(const Graph& g, const vector<Client>& c);

#endif //ETHICAL_ROUTING_TRAVERSALS_H
