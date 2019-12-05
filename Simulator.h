//
// Created by Sanchit Batra on 8/14/19.
//

#ifndef ETHICAL_ROUTING_SIMULATOR_H
#define ETHICAL_ROUTING_SIMULATOR_H

#include "Objects.h"
#include "Graph.h"
#include <vector>

//runs the simulation
unordered_map<int, int> Simulator(Graph& g, Solution_Object& sol, const vector<Client>& clients);

//determines if a location is valid
bool isValid(const Graph& g, int a, int b);

//sorts by priority
bool comparePrio(const Client& a, const Client& b);

#endif //ETHICAL_ROUTING_SIMULATOR_H
