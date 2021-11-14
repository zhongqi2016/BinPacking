#include "BinPacking.h"

int BinPacking::BNB() {
    std::vector<Item> items = refactor(weightOfItems);
    sort(items.rbegin(), items.rend());
    Branch bound(c, items);
    UB = INT_MAX;

    std::stack<Branch> s;
    s.emplace(bound);

    int res = dfs(s);
    organize();
    return res;
}

int BinPacking::dfs(std::stack<Branch> s) {
    while (!s.empty()) {
        Branch bound = std::move(s.top());
        s.pop();

        int z = bound.getIndexOfItem();
        std::vector<Item> &items = bound.getItems();
        if (z == items.size() || items[z].weight == 0) return z + bound.getReduced();

        //create a new bin
        if (z < UB - 1) {
            Branch newBound(bound);
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
                if (newBound.getIndexOfItem() + newBound.getReduced() < UB) {
                    if (newBound.lowerBound3() < UB) {
                        s.push(newBound);
                    }
                }

            }

        }

        //to all feasible initialized bins
        z = bound.getIndexOfItem();
        for (int j = z - 1; j >= 0; --j) {
            if (items[j].weight + items[z].weight <= c) {
//                int z1 = z;
                Branch newBound(bound);
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
                    if (newBound.getIndexOfItem() + newBound.getReduced() < UB) {
                        if (newBound.lowerBound3() < UB) {
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