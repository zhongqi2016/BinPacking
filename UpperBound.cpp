#include <vector>

using namespace std;

int firstFit(const vector<int> &items, int c) {
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

int bestFit(const vector<int> &items, int c) {
    int result = 0;
    int length = items.size();
    int ava[length];

    for (int i = 0; i < length; ++i) {
        int j;
        int min = c + 1;
        int bin_min = 0;
        for (j = 0; j < result; j++) {
            if (ava[j] >= items[i] && ava[j] - items[i] < min) {
                min = ava[j] - items[i];
                bin_min = j;
            }
        }
        if (min == c + 1) {
            ava[result] = c - items[i];
            ++result;
        } else ava[bin_min] -= items[i];
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