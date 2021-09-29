#include "DataInput.h"

DataInput initData(int n,int c,std::vector<int> w){
    DataInput data1;
    data1.n=std::move(n);
    data1.c=std::move(c);
    data1.w= std::move(w);
    return data1;
}

DataForCalc initData2(std::list<Bin> *current,int z, int z_reduction){
    DataForCalc data2;
    data2.current=*current;
    data2.z=z;
    data2.z_reduction=z_reduction;
    return data2;
}