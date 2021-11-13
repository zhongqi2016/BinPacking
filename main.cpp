//
// Created by 吴中奇 on 2021/11/12.
//
#include <iostream>
#include "ReadFiles.h"

using namespace std;


int main() {
    string path = "./bin1data";//Path of input data

    ReadFiles readFiles(path);
    for (int i = 0; i < readFiles.getNumOfFiles(); ++i) {
        std::cout << i << ". filename: " << readFiles.getFileName(i) << std::endl;

        BinPacking binPacking = std::move(readFiles.getData(i));
        clock_t start, end;
        start = clock();

        int result = binPacking.BNB();
        end = clock();
        double time = (double) (end - start) / CLOCKS_PER_SEC;
        binPacking.printSolution();
        printf("Number of bins needed = %d\nTime=%lf\n", result, time);
        //        break;
    }

    return 0;
}
