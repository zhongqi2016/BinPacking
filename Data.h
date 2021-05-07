
#ifndef BINPACKING_BNB_DATA_H
#define BINPACKING_BNB_DATA_H

#include <vector>

#endif //BINPACKING_BNB_DATA_H

struct Data{
    int n;
    int c;
    std::vector<int> w;
};

struct Data2{
    std::vector<int> current;
    int z;
    int z_reduction;
};

Data initData(int n,int c,std::vector<int> w);
Data2 initData2(std::vector<int> current,int z,int z_reduction);