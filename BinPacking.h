
#ifndef BINPACKING_BNB_BINPACKING_H
#define BINPACKING_BNB_BINPACKING_H

#include <algorithm>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <stack>

#include "Branch.h"

class BinPacking {
public:
    BinPacking(int _c, std::vector<int> _weight) : c(_c), weightOfItems(_weight), UB(0),
                                                   solution(std::vector<int>(_weight.size(), 0)) {}

    int BNB();

    std::vector<int> &getSolution() { return solution; }

    void printSolution();

private:
    int dfs(std::stack<Branch> s);

    void organize();

    const int c;//capacity of bin
    int UB;
    int LB;
    std::vector<int> weightOfItems;
    std::vector<int> solution;  //Current optimal solution
};


#endif //BINPACKING_BNB_BINPACKING_H

