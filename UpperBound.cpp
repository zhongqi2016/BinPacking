#include <vector>
#include "state.h"

using namespace std;

int firstFit(vector<int> items) {
    int result = 0;
    int length = items.size();
    int ava[length];

    for (int i = 0; i < length; ++i) {
        int j;
        for (j = 0; j < result; ++j) {
            if (ava[j] >= items[i]) {
                ava[j] -= items[i];
                break;
            }
        }
        if (j == result) {
            ava[result] = c - items[i];
            result++;
        }
    }
    return result;
}


//int firstFit(vector<int> w1, int index) {
//    int result = 0;
//    int length1 = w1.size();
//
//    int ava[n];
//
//    for (int i = 0; i < length1; ++i) {
//        int j;
//        for (j = 0; j < result; ++j) {
//            if (ava[j] >= w1[i]) {
//                ava[j] -= w1[i];
//                break;
//            }
//        }
//        if (j == result) {
//            ava[result] = c - w1[i];
//            result++;
//        }
//    }
//    for (int i = index; i < n; ++i) {
//        int j;
//        for (j = 0; j < result; ++j) {
//            if (ava[j] >= items[i]) {
//                ava[j] -= items[i];
//                break;
//            }
//        }
//        if (j == result) {
//            ava[result] = c - items[i];
//            result++;
//        }
//    }
//    return result;
//}