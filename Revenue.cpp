//
// Created by Sanchit Batra on 8/14/19.
//


#include <vector>
#include <unordered_map>
#include "Revenue.h"
#include "Objects.h"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <fstream>
#include "Traversals.h"
#include "Graph.h"

using namespace std;

//returns what the customers pay
int pen_0(Graph& input, vector<Client>& clients, unordered_map<int, int>& calc_delays, bool count_rural, bool five){
    int revenue = 0;
    unordered_map<int, int> paths = bfs(input, clients);
    for(Client c: clients){
        if((c.alpha * (double) paths.at(c.id) < (double)calc_delays.at(c.id)) || calc_delays.at(c.id) < 0){

            if(five){
                return 0;
            }else if(count_rural && c.is_rural){
               revenue += c.payment;
           }
        }else{
            revenue += c.payment;
        }
    }
    return revenue;
}

//returns fines occured

int pen_1(Graph& input, vector<Client>& clients, unordered_map<int, int>& delays, unordered_map<string,
        pair<float, int>>& fine_info){
    int complaints = 0;
    int fcc_complaints = 0;
    int num_fcc =0;
    int fine = 0;

    unordered_map<int, int> paths = bfs(input, clients);
    for(const Client& c: clients){
      // get the number of fcc clients first
        if (c.is_fcc) {
          ++num_fcc;
        }
        // increment complaints
        if((c.beta * (double) paths.at(c.id) < (double)delays.at(c.id)) || delays.at(c.id) < 0){
          ++complaints;
          // increment fcc_complaints
          if(c.is_fcc){
              ++fcc_complaints;
          }
        }
    }
    int clients_size = clients.size();
    // pen_1 from the python/java code
    if(complaints >= (fine_info.at("lawsuit").first * (double) clients_size)){
        fine +=fine_info.at("lawsuit").second;
    }

    // pen_2 from the python_java code
    if(fcc_complaints >= (fine_info.at("fcc").first * (double) num_fcc)){
        fine +=fine_info.at("fcc").second;
    }

    return fine;
}

//returns cost of increasing bandwidth
int bandwidth_increase(vector<int>& old_bandwidths, vector<int>& new_bandwidths, int increase_amt){
    int increase = 0;
    for(int i = 0; i < old_bandwidths.size() && i < new_bandwidths.size(); i ++){
        increase += max(0, increase_amt * (new_bandwidths.at(i) - old_bandwidths.at(i)));
    }
    return increase;
}
