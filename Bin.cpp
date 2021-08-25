//
// Created by 吴中奇 on 2021/8/23.
//
#include <cstdio>
#include "Bin.h"

Bin initBin(int sum, std::list<int> serial) {
    Bin bin;
    bin.sum = std::move(sum);
    bin.serial = std::move(serial);
    return bin;
}

std::vector<Bin> refactor(const std::vector<int> &items) {
    int length = items.size();
    std::vector<Bin> list;
    list.reserve(length);
    for (int i = 0; i < length; ++i) {
        std::list<int> itemsInBin;
        itemsInBin.emplace_back(i);
        Bin bin = initBin(items[i], itemsInBin);

        list.emplace_back(bin);
    }
    return list;
}

bool cmp(const Bin &a, const Bin &b) {
    return a.sum > b.sum;
}

void binSort(std::vector<Bin> &binList) {
    std::sort(binList.begin(), binList.end(), cmp);
}

//Bin1 <- Bin2
void mergeBin(Bin &bin1, Bin &bin2) {
    bin1.sum += bin2.sum;
    bin1.serial.splice(bin1.serial.end(), bin2.serial);
    bin2.sum = 0;
}

void mergeSerial(Bin &bin1, Bin &bin2) {
    bin1.serial.splice(bin1.serial.end(), bin2.serial);
}

void binOrganize(std::vector<Bin> &binList, std::vector<int> &items) {
    int count = 0;
    for (int i = 0; i < binList.size(); ++i) {
        int sum = 0;
        std::list<int>::iterator it;
        std::list<int> &l = binList[i].serial;
        for (it = l.begin(); it != l.end(); ++it) {
            sum += items[*it];
        }
        if (sum == 0) count++;
        binList[i].sum = std::move(sum);
    }
    binSort(binList);
    binList.resize(binList.size() - count);
}

void bin_print(std::vector<Bin> &binList){
    for (int i = 0; i < binList.size(); ++i) {
        std::list<int>::iterator it;
        printf("%d(",binList[i].sum);
        std::list<int>& l=binList[i].serial;
        for (it = l.begin(); it != l.end(); ++it) {
            printf("%d, ", *it);
        }
        printf("),");
    }
    printf("\n");
}