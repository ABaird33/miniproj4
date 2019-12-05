//
// Created by Sanchit Batra on 8/14/19.
// Updated by Veronica Vitale on 1 September 2019
//

#include "Simulator.h"
#include "Objects.h"
#include "Traversals.h"
#include <algorithm>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <iostream>

using namespace std;

void printVec(vector<Client>* clients, unordered_map<int, int>& delays) {
  for (auto it = clients->begin(); it != clients->end(); ++it) {
    auto c = *it;
    cout<<"For client ID("<<c.id<<"), alpha="<<c.alpha<<", priority: " << c.priority
    << ", delays: " << delays[c.id] << "\n";
  }
}
//runs the simulation
unordered_map<int, int> Simulator(Graph& g, Solution_Object& sol, const vector<Client>& clients_vec) {
    // for students who have a "better" path than the shortest path
    unordered_map<int, int> shortestDistances = bfs(g, clients_vec);

    vector<Client>* clients = new vector<Client>();
    // copy over the clients first
    for (const Client& c : clients_vec) {
      clients->push_back(Client(c.id, c.alpha, c.beta, c.payment, c.is_rural, c.is_fcc, 0));
    }

    // sort clients based on priorities
    if(!sol.priorities.empty()){
        for(auto it = clients->begin(); it != clients->end(); ++it) {
          Client& c = *it;
            c.priority = sol.priorities[c.id];
        }
        sort(clients->begin(), clients->end(), comparePrio);
    }
    //index of path for each client ; where the packet is
    unordered_map<int, int> locations;
    //list to be used to make iterating through clients easier
    list<Client> client_list;
    //map of calculated delays
    unordered_map<int, int> calc_delays;
    // packet delays for clients
    unordered_map<int, int> packet_delay;

    for(auto it = clients->begin(); it != clients->end(); ++it) {
        const Client& c = *it;
      //  cout << "client: " << c.id << endl;
        packet_delay[c.id] = 0;
        // if the client doesnt have a path or doesnt have the correct start node we rage
        if(sol.paths.at(c.id).empty()){

           calc_delays[c.id] = -1;
        }else if(sol.paths.at(c.id).at(0) != g.contentProvider){

            calc_delays[c.id] = -1;
        }else {
            // set up for locations and list
            locations[c.id] = 0;
            client_list.push_back(Client(c.id, c.alpha, c.beta, c.payment, c.is_rural, c.is_fcc, c.priority));
        }

    }

    vector<int> current_bandwidths(sol.bandwidths.begin(), sol.bandwidths.end());
    while (!client_list.empty()){
      unordered_set<int> active;
        //bandwidths for current iteration
      auto c = client_list.begin();
      while (c != client_list.end()) {
          //checks if client has reached destination
          int current_node = sol.paths.at((*c).id).at(locations.at((*c).id));
          // if it is the correct client set the delay to packet delay otherwise inf
          int path_size = sol.paths.at(c->id).size();
          if(!path_size || locations[c->id] == (path_size -1)) {
            calc_delays[c->id] = current_node == c->id ? packet_delay[current_node] : -1;
            // for students doing "better" than the shortest path
            if ((path_size - 1) < shortestDistances[c->id]) {
              calc_delays[c->id] = -1;
            }
            client_list.erase(c++);
            continue;
          }
          // increment packet delay here
          packet_delay[c->id] += 1;
          // if current_node has positive bandwith
          if (current_bandwidths.at(current_node) > 0) {
            if(!isValid(g, sol.paths.at((*c).id).at(locations.at((*c).id)), sol.paths.at((*c).id).at(locations.at((*c).id) +1))){
              calc_delays[(*c).id] = -1;
              client_list.erase(c++);
              continue;
            }
            // decrease current_node's bandwidth
            current_bandwidths[current_node] -= 1;
            // increment packet bandwidth
            locations[c->id] += 1;
            active.emplace(current_node);
          }
          ++c;
      }
      for (int node : active) {
        current_bandwidths[node] = sol.bandwidths.at(node);
      }
    }
    delete clients;
    return calc_delays;
}

// comparator for sorting clients based on priorities in descending order
inline bool comparePrio(const Client& a, const Client& b){
    if (a.priority == b. priority) {
      return a.id < b.id;
    }
    return a.priority > b.priority;
}
//determines if a location is valid
inline bool isValid(const Graph& g, const int a, const int b){
    return g.graph_set.at(a).find(b) != g.graph_set.at(a).end();
}
