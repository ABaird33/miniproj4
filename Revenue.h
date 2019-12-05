//
// Created by Sanchit Batra on 8/14/19.
// Updated by Veronica Vitale on 30 Aug 2019
//

#ifndef ETHICAL_ROUTING_REVENUE_H
#define ETHICAL_ROUTING_REVENUE_H
#include "Objects.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>

using namespace std;

int bandwidth_increase(vector<int>& old_bandwidths, vector<int>& new_bandwidths, int increase_amt);
int pen_1(Graph& input, vector<Client>& clients, unordered_map<int, int>& delays, unordered_map<string,
        pair<float, int>>& fine_info);
int pen_0(Graph& input, vector<Client>& clients, unordered_map<int, int>& calc_delays, bool count_rural, bool five);
#endif //ETHICAL_ROUTING_REVENUE_H
