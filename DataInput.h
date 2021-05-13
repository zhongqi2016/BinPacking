
#ifndef BINPACKING_BNB_DATA_H
#define BINPACKING_BNB_DATA_H

#include <vector>

struct DataInput{
    int n;
    int c;
    std::vector<int> w;
};

struct DataForCalc{
    std::vector<int> current;
    int z;
    int z_reduction;
};

DataInput initData(int n,int c,std::vector<int> w);
DataForCalc initData2(std::vector<int> current, int z, int z_reduction);

#endif //BINPACKING_BNB_DATA_H

