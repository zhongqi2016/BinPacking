#include "Algorithm.h"

int BinPacking::BNB() {
    std::vector<Item> items = refactor(weightOfItems);
    sort(items.rbegin(), items.rend());
    Bound bound(c, items);
    UB = INT_MAX;
/*
    bound.addCurrentItem();
    std::vector<int> curSolution(bound.getDistribution());
     LB = bound.lowerBound2();
    UB = bound.upperBound(curSolution);
    solution = std::move(curSolution);
    if (LB == UB) return LB;
    int L3 = LB;

    if (L3 == UB) return L3;
    bound.reduction();
*/
    std::stack<Bound> s;
    s.emplace(bound);

//    L3 = LB;
    int res = dfs(s);
    organize();
    return res;
}

int BinPacking::dfs(std::stack<Bound> s) {
    while (!s.empty()) {
        Bound bound = std::move(s.top());
        s.pop();

        int z = bound.getIndexOfItem();
        std::vector<Item> &items = bound.getItems();
        if (z == items.size() || items[z].weight == 0) return z + bound.getReduced();

        //create a new bin
        if (z < UB - 1) {
            Bound newBound(bound);
            newBound.addCurrentItem();
            newBound.reduction();

            std::vector<int> curSolution(newBound.getDistribution());
            int LB_current = newBound.lowerBound2();
            int UB_current = newBound.upperBound(curSolution);

            if (UB_current == LB) {
                solution = std::move(curSolution);
                return UB_current;

            }
            if (UB > UB_current) {
                UB = UB_current;
                solution = std::move(curSolution);
            }
            newBound.incrementIndex();

            if (UB_current > LB_current && LB_current < UB) {

                if (z + newBound.getReduced() < UB) {
                    int L3 = newBound.lowerBound3();

                    if (L3 < UB) {
//                        printf("FF:%d, LB:%d, L3:%d, indexOfItem:%d\n", FF_current, LB_current, L3, z1 + zr);
//                        printItems(current);
                        s.push(newBound);
                    }
                }

            }

        }

        //to all feasible initialized bins
        int j;
        z = bound.getIndexOfItem();
        for (j = z - 1; j >= 0; --j) {
            if (items[j].weight + items[z].weight <= c) {
//                int z1 = z;
                Bound newBound(bound);
                newBound.mergeTwoItems(j, z);
                std::vector<int> curSolution(newBound.getDistribution());

                newBound.reduction();
                int LB_current = newBound.lowerBound2();
                int UB_current = newBound.upperBound(curSolution);

                if (UB_current == LB) {
                    solution = std::move(curSolution);
                    return UB_current;
                }
                if (UB > UB_current) {
                    UB = UB_current;
                    solution = std::move(curSolution);
                }
                if (UB_current > LB_current && LB_current < UB) {
                    if (z + newBound.getReduced() < UB) {
                        int L3 = newBound.lowerBound3();
                        if (L3 < UB) {

                            s.push(newBound);
                        }
                    }
                }
            }
        }

    }
    return UB;
}

void BinPacking::organize() {
    int min = *std::min_element(solution.begin(), solution.end());
    if (min < 0) min = -min;
    else return;
    for (int &elem:solution) {
        if (elem < 0)elem += min + 1;
        else if (elem > 0) elem += min;
    }
}

void BinPacking::printSolution() {
    for (auto index:solution) {
        printf("%d ", index);
    }
    printf("\n");
}