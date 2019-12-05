#include "MPUtility.h"
#include "Solution.cpp"
#include "Graph.h"
#include "Revenue.cpp"
#include "Objects.h"
#include "Simulator.cpp"
#include "Traversals.cpp"
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class Driver;

int main(int argc, char** argv) {

    if(argc < 2){
        cout << "Please put the filename as an argument." << endl;
    }

    MPUtility utility;

    int problem = 4; // change this to the problem # you are working on

    string filename = argv[1];

    Graph input = utility.readFile(filename);
    string info = filename;
    info += "-info";
    pair<vector<Client>, vector<int>> b_c = utility.readInfo(info, problem);

    int increase = 0;
    unordered_map<string, pair<float, int>> fines;

    if(problem > 2){
        increase = utility.readIncrease(info, problem);
    }
    if(problem > 2 && problem < 5){
        fines = utility.readFines(info);
    }else{
        fines = unordered_map<string, pair<float, int>>();
    }


    Solution s(input, b_c.first, b_c.second, fines, increase);
    Solution_Object studentSolution = s.outputPaths();
    cout << "Your solution " << endl;
    cout << "==========================================" << endl;
    if (studentSolution.paths.empty()) {
      cout << "Your paths are empty!!!" << endl;
      return 0;
    }
    if (studentSolution.bandwidths.empty()) {
      cout << "Your bandwidths are empty!!!" << endl;
      return 0;
    }
    cout << "[";
	switch(problem){
        case 1:
            {
                studentSolution.bandwidths = b_c.second;

                unordered_map<int, int> delays = Simulator(input, studentSolution, b_c.first);


                        for(Client c: b_c.first){

                            cout << "Client: "  << c.id << " Delay: " << delays[c.id]  << endl;
                        }


                        int rev = pen_0(input, b_c.first, delays, false, false);

                        cout << "]" << endl << "Revenue: " << rev << endl;
            }

            break;

        case 2: {
                unordered_map<int, int> delays = Simulator(input, studentSolution, b_c.first);

                    for(Client c: b_c.first){
                        cout << "Client: "  << c.id << " Delay: " << delays[c.id] << endl;
                    }

                    int rev = pen_0(input, b_c.first, delays, false, false);

                    cout << "]" << endl << "Revenue: " << rev << endl;
                }
            break;

        case 3: {
                unordered_map<int, int> delays = Simulator(input, studentSolution, b_c.first);

                    for(Client c: b_c.first){
                        cout << "Client: "  << c.id << " Delay: " << delays[c.id] << endl;
                    }

                int rev = pen_0(input, b_c.first, delays, false, false) - pen_1(input, b_c.first, delays, fines) - bandwidth_increase(b_c.second, studentSolution.bandwidths, increase);

                    cout << "]" << endl << "Revenue: " << rev << endl;
            }
            break;
        case 4: {
                unordered_map<int, int> delays = Simulator(input, studentSolution, b_c.first);

                    for(Client c: b_c.first){
                        cout << "Client: "  << c.id << " Delay: " << delays[c.id] << endl;
                    }

                int rev = pen_0(input, b_c.first, delays, true, false) - pen_1(input, b_c.first, delays, fines) - bandwidth_increase(b_c.second, studentSolution.bandwidths, increase);

                    cout << "]" << endl << "Revenue: " << rev << endl;
            }
            break;

        case 5:{
            unordered_map<int, int> delays = Simulator(input, studentSolution, b_c.first);

            for(Client c: b_c.first){
                cout << "Client: "  << c.id << " Delay: " << delays[c.id] << endl;
            }

            cout << "** Warning: bandwith increases are not able to be properly read in yet **" << endl;
            int rev = pen_0(input, b_c.first, delays, false, true) - bandwidth_increase(b_c.second, studentSolution.bandwidths, increase);

            cout << "]" << endl << "Revenue: " << rev << endl;
            }
            break;
    }

    return 0;
}
