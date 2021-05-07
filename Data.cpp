#include "Data.h"

Data initData(int n,int c,std::vector<int> w){
    Data data1;
    data1.n=std::move(n);
    data1.c=std::move(c);
    data1.w= std::move(w);
    return data1;
}

Data2 initData2(std::vector<int> current,int z,int z_reduction){
    Data2 data2;
    data2.current=std::move(current);
    data2.z=std::move(z);
    data2.z_reduction=std::move(z_reduction);
    return data2;
}