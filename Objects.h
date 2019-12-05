//
// Created by Sanchit Batra on 8/14/19.
// Updated by Veronica Vitale on 8/30/19
//

#ifndef ETHICAL_ROUTING_OBJECTS_H
#define ETHICAL_ROUTING_OBJECTS_H

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Client{
public:
    int id; //clients id, matches their node in the graph
    float alpha; // alpha value
    float beta; //beta alue
    int payment; // client's payment
    bool is_rural; // true if the client is from a rural area
    bool is_fcc; //true if the client is a part of the fcc subset
    int priority;
    Client(int t_id, float t_alpha, float t_beta, int t_payment, bool rural, bool fcc, int priority):
    id(t_id), alpha(t_alpha), beta(t_beta), payment(t_payment), is_rural(rural), is_fcc(fcc), priority(priority)
    {
        priority = 0;
    }

};

class Solution_Object{
public:

    unordered_map<int, vector<int>> paths; //path for each client
    unordered_map<int, int> priorities; // priority for each client
    vector<int> bandwidths; // bandwidths for each node in the graph

    Solution_Object(){
        paths = unordered_map<int, vector<int>>();
        priorities = unordered_map<int, int>();
        bandwidths = vector<int>();

    }

    Solution_Object(unordered_map<int, vector<int>> t_paths, vector<int> t_bandwidths, unordered_map<int, int> t_priorities):
    paths(t_paths), priorities(t_priorities), bandwidths(t_bandwidths)
    {

    }


};

#endif /*ETHICAL_ROUTING_OBJECTS_H*/
