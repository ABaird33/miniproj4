#ifndef MPUTILITY_H_
#define MPUTILITY_H_

#include "Utility.h"
#include "Graph.h"
#include "Objects.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <utility>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


using namespace std;



class MPUtility: public Utility<Graph> {
public:
    MPUtility(){};

    Graph readFile(std::string filename){
        fstream input(filename, ios_base::in);
        std::string start;
        int start_node;
        std::getline(input, start);
        start_node = atoi(start.c_str());
        std::string line;

        std::unordered_map<int, vector<int>> graph;
        std::unordered_map<int, unordered_set<int>> graph_set;
        int nodeCounter = 0;
        while(std::getline(input, line)){
            if(line != ""){

                std::istringstream iss(line);
                std::vector<int> neighbors;
                std::unordered_set<int> neighbors_set;
                int node;
                while(iss >> node){
                    neighbors.push_back(node);
                    neighbors_set.emplace(node);
                }
                graph[nodeCounter] = neighbors;
                graph_set[nodeCounter] = neighbors_set;
            }
            else{
                std::unordered_set<int> neighbors_set;
                vector<int> neighbors;
                graph[nodeCounter] = neighbors;
                graph_set[nodeCounter] = neighbors_set;
            }
            nodeCounter++;
        }
        input.close();
        Graph in_graph(start_node, graph, graph_set);
        return in_graph;
    }

    std::pair<vector<Client>, vector<int>> readInfo(std::string fileName, int problem){

        fstream input(fileName, ios_base::in);
        std::string start;
        std::string line;

        vector<Client> clients = vector<Client>();
        vector<int> bandwidths = vector<int>();

        if(problem == 3 || problem == 4){
            for(int i = 0; i < 5; i ++){
                std::getline(input, line);

            }
        }

        if(problem == 5){
            std::getline(input, line);
        }

        while(std::getline(input, line)) {

            std::istringstream  iss(line);
            std::vector<std::string> curr_line((std::istream_iterator<std::string>(iss)),
                    std::istream_iterator<std::string>());
            //prases bandwidth

            bandwidths.push_back(stoi(curr_line.at(1)));
            if(curr_line.at(0)[0] == '0'){

                continue;

            }
            // parses client
            float beta = 0;
            bool rural = false, fcc = false;

            if(curr_line.size() > 4){
                beta = stof(curr_line.at(4));

            }
            if(curr_line.size() > 5 && curr_line.at(5)[0]== '1'){
                fcc = true;
            }
            float alpha = stof(curr_line.at(2));
            if(curr_line.size() > 6 && curr_line.at(6)[0]== '1'){
                rural = true;
                alpha = -1;
            }

            Client c = Client(bandwidths.size()-1, alpha, beta, stoi(curr_line.at(3)), rural, fcc, 0);
            clients.push_back(c);
        }
        input.close();
        return pair<vector<Client>, vector<int>>(clients, bandwidths);
    }

    unordered_map<string, pair<float, int>> readFines(string filename){
        fstream input(filename, ios_base::in);
        std::string line;

        getline(input, line);
        float law_suit = stof(line);
        getline(input, line);
        float fcc = stof(line);

        getline(input, line);
        int law_suit_f = stoi(line);
        getline(input, line);
        int fcc_f = stoi(line);

        unordered_map<string, pair<float, int>> fines = unordered_map<string, pair<float, int>>();

        std::string law = "lawsuit";
        std::string f = "fcc";

        fines[law] = pair<float, int>(law_suit, law_suit_f);
        fines[f] = pair<float, int>(fcc, fcc_f);

        input.close();

        return fines;
    }

    int readIncrease(string filename, int problem){
        fstream input(filename, ios_base::in);
        std::string line;

        if(problem < 5){
            for(int i = 0; i < 4; i ++){
                getline(input, line);
            }
        }
        getline(input, line);

        input.close();

        return stoi(line);
    }
};
#endif
