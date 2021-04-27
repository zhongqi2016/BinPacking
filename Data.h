
#ifndef BINPACKING_BNB_DATA_H
#define BINPACKING_BNB_DATA_H

#include <vector>

#endif //BINPACKING_BNB_DATA_H

struct Data{
    int n;
    int c;
    std::vector<int> w;
};

Data initData(int n,int c,std::vector<int> w);