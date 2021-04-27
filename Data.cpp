#include "Data.h"

Data initData(int n,int c,std::vector<int> w){
    Data data1;
    data1.n=std::move(n);
    data1.c= std::move(c);
    data1.w= std::move(w);
    return data1;
}