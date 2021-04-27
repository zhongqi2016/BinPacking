#include <vector>
#include <algorithm>
#include "LowerBound.h"
#include "state.h"


int L2withA(int alpha, std::vector<int> w) {
    int J1 = 0;
    int J2 = 0;
    int J3 = 0;
    int sumJ3 = 0;
    int sumJ2 = 0;
    int length = w.size();
    for (int i = 0; i < length; i++) {
        if (w[i] != 0) {
            if (w[i] > c - alpha) {
                J1++;
            } else if (w[i] > c / 2) {
                J2++;
                sumJ2 += w[i];
            } else if (w[i] >= alpha) {
                J3++;
                sumJ3 += w[i];
            }
        }
    }

    int L = J1 + J2 + (std::max<int>(0, sumJ3 - (J2 * c - sumJ2)) + c - 1) / c;
    return L;
}

//

int lowerBound2(std::vector<int> w1) {
    int max = 0;
    int L;

    for (int a = 0; a <= c / 2; a++) {
        L = L2withA(a, w1);
        if (L > max) {
            max = L;
        }
    }
    return max;
}


int findLargestK(std::vector<int> w, int index) {
    int sum = w[index];
    if (sum + w.back() > c) {
        return 0;
    }
    int k = 1;
    sum+=w.back();
    for (int i = w.size() - k-1; i > 0; --i) {
        if (w[i] == 0) continue;
        if (sum + w[i] <= c) {
            sum += w[i];
            ++k;
        } else {
            break;
        }
    }
    return k;
}

int findMinH(std::vector<int> w, int index) {
    int wj = w[index];
    for (int i = 0; i < w.size(); ++i) {
        if (w[i] == 0||i==index) continue;
        if (wj + w[i] <= c) {
            return i;
        }
    }
    //fail
    return -1;
}

bool findAB(std::vector<int> w, int index, int &a, int &b) {
    int ava = c - w[index];
    int i;
    int maxValue = 0;
    bool flag = false;
    for (i = 0; i < w.size(); ++i) {
        if (w[i] == 0||i==index) continue;
        if (ava > w[i]) {
            for (int j = i + 1; j < w.size(); ++j) {
                if (w[j] == 0) continue;
                if (w[i] + w[j] == ava) {
                    a = i;
                    b = j;
                    return true;
                }
                if (w[i] + w[j] < ava) {
                    if (w[i] + w[j] > maxValue) {
                        maxValue = w[i] + w[j];
                        a = i;
                        b = j;
                        flag = true;
                    }
                    break;
                }
            }
        }
    }
    return flag;
}

int reduction(std::vector<int> &w, int &z) {
//    std::vector<int> w(w1);
//    w.reserve(n);
//    w.insert(w.end(), items.begin() + index, items.end());
    std::vector<int> bj(w.size(), 0);
    int zr = 0;
    std::vector<int> F;
    int count = 0;//Deleted items that have been put in bins
    int reduced=0;
    for (int i = 0; i < w.size(); ++i) {
        if (w[i] == 0) continue;
        int k = findLargestK(w, i);
        F.clear();
        if (k == 0) {
            F.push_back(i);
        } else {
            int h = findMinH(w, i);
            if (h == -1) continue;
            if (k == 1 || w[i] + w[h] == c) {
                F.push_back(i);
                F.push_back(h);
            } else if (k == 2) {
                int a;
                int b;
                if (findAB(w, i, a, b)) {
                    if (w[h] >= w[a] + w[b]) {
                        F.push_back(i);
                        F.push_back(h);
                    } else if (w[h] == w[a] && (b - a <= 2 || w[i] + w[b - 1] + w[b - 2] > c)) {
                        F.push_back(i);
                        F.push_back(a);
                        F.push_back(b);
                    }
                }
            }
        }
        if (!F.empty()) {
            ++zr;
            for (int j = 0; j < F.size(); ++j) {
                bj[F[j]] = zr;
//                printf("%d ",w[F[j]]);
                w[F[j]] = 0;
                if (F[j] < z) ++count;

            }
//            printf("\n");
            reduced+=F.size();
        }

    }
    z -= count;
    sort(w.rbegin(), w.rend());
    w.resize(w.size()-reduced);
    return zr;
}

//int L2withA(int alpha, std::vector<int> w1, int index) {
//    int J1 = 0;
//    int J2 = 0;
//    int J3 = 0;
//    int sumJ3 = 0;
//    int sumJ2 = 0;
//    int length = w1.size();
//    for (int i = 0; i < length; i++) {
//        if (w1[i] != 0) {
//            if (w1[i] > c - alpha) {
//                J1++;
//            } else if (w1[i] > c / 2) {
//                J2++;
//                sumJ2 += w1[i];
//            } else if (w1[i] >= alpha) {
//                J3++;
//                sumJ3 += w1[i];
//            }
//        }
//    }
//
//    for (int i = index; i < n; i++) {
//        if (items[i] != 0) {
//            if (items[i] > c - alpha) {
//                J1++;
//            } else if (items[i] > c / 2) {
//                J2++;
//                sumJ2 += items[i];
//            } else if (items[i] >= alpha) {
//                J3++;
//                sumJ3 += items[i];
//            }
//        }
//    }
//
//    int L = J1 + J2 + (std::max<int>(0, (sumJ3 - (J2 * c - sumJ2) + c - 1) / c));
//    return L;
//}
//
//int lowerBound2(std::vector<int> w1, int index) {
//    int max = 0;
//    int L;
//
//    for (int a = 0; a <= c / 2; a++) {
//        L = L2withA(a, w1, index);
//        if (L > max) {
//            max = L;
//        }
//    }
//    return max;
//}