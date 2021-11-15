#include "BinPacking.h"

int BinPacking::BNB() {
    std::vector<Item> items = refactor(weightOfItems);
    sort(items.rbegin(), items.rend());
    Branch branch(c, items);

    branch.reduction();
    solution=branch.getDistribution();
    LB = branch.lowerBound2();
    UB = branch.upperBound(solution);

    if (UB== LB) {
        organize();
        return UB;
    }
    LB=branch.lowerBound3();
    if (UB== LB) {
        organize();
        return UB;
    }
    std::stack<Branch> s;
    s.emplace(branch);

    int res = dfs(s);
    organize();
    return res;
}

int BinPacking::dfs(std::stack<Branch> s) {
    while (!s.empty()) {
        Branch branch = std::move(s.top());
        s.pop();

        int z = branch.getIndexOfItem();
        std::vector<Item> &items = branch.getItems();
        if (z == items.size() || items[z].weight == 0) return z + branch.getReduced();

        //create a new bin
        if (z < UB - 1) {
            Branch newBranch(branch);
            newBranch.reduction();

            std::vector<int> curSolution(newBranch.getDistribution());
            int LB_current = newBranch.lowerBound2();
            int UB_current = newBranch.upperBound(curSolution);

            if (UB_current == LB) {
                solution = std::move(curSolution);
                return UB_current;

            }
            if (UB > UB_current) {
                UB = UB_current;
                solution = std::move(curSolution);
            }
            newBranch.incrementIndex();

            if (UB_current > LB_current && LB_current < UB) {
                if (newBranch.getIndexOfItem() + newBranch.getReduced() < UB) {
                    if (newBranch.lowerBound3() < UB) {
                        s.push(newBranch);
                    }
                }

            }

        }

        //to all feasible initialized bins
        z = branch.getIndexOfItem();
        for (int j = z - 1; j >= 0; --j) {
            if (items[j].weight + items[z].weight <= c) {
//                int z1 = z;
                Branch newBranch(branch);
                newBranch.mergeTwoItems(j, z);
                std::vector<int> curSolution(newBranch.getDistribution());

                newBranch.reduction();
                int LB_current = newBranch.lowerBound2();
                int UB_current = newBranch.upperBound(curSolution);

                if (UB_current == LB) {
                    solution = std::move(curSolution);
                    return UB_current;
                }
                if (UB > UB_current) {
                    UB = UB_current;
                    solution = std::move(curSolution);
                }

                if (UB_current > LB_current && LB_current < UB) {
                    if (newBranch.getIndexOfItem() + newBranch.getReduced() < UB) {
                        if (newBranch.lowerBound3() < UB) {
                            s.push(newBranch);
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