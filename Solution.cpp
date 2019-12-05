#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "Objects.h"
#include "Graph.h"
#include "Traversals.h"

using namespace std;
class Solution {
private:
    Graph graph; // this is your graph (see graph.h for details)
    vector<Client> clients; // here are your clients (for full client details see objects.h)
    vector<int> bandwidths; // bandwidths for each node
    /*
     * Format:
     * "fcc" -> rho_fcc, fine amount
     * "lawsuit" -> rho_lawsuit, fine amount
     * for problems 3 and 4 to store fines and their tolerances
     */
    unordered_map<string, pair<float, int>> fines;
    int band_incr_cost; // amount to increase bandwidth by 1

public:
    Solution(Graph g, vector<Client> c, vector<int> band, unordered_map<string, pair<float, int>> fine, int incr):
            graph(g), clients(c), bandwidths(band), fines(fine), band_incr_cost(incr)
    {

    }
    //route your clients, for info on solution_object see objects.h
    Solution_Object outputPaths() {

        Solution_Object solution;
        // change all three of solution.paths, solution.bandwidhts and solution.priorities for this problem
        /*
         * TODO: Implement the solution
         */
        
        return solution;
    }
};
