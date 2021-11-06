
#ifndef BINPACKING_BNB_ALGORITHM_H
#define BINPACKING_BNB_ALGORITHM_H

#include <algorithm>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <stack>

#include "Bound.h"

class BinPacking {
public:
    BinPacking(int _c, std::vector<int> _weight) : c(_c), weightOfItems(_weight), UB(0),
                                                   solution(std::vector<int>(_weight.size(), 0)) {}

    int BNB();

    std::vector<int> &getSolution() { return solution; }

    void printSolution();

private:
    int dfs(std::stack<Bound> s);
    void organize();
    const int c;//capacity of bin
    int UB;
    int LB;
    std::vector<int> weightOfItems;
    std::vector<int> solution;
};


#endif //BINPACKING_BNB_ALGORITHM_H

