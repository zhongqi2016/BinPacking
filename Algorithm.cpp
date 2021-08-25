
#include "Algorithm.h"

void printItems(const std::vector<int> &items) {
    for (int item : items) {
        printf("%d ", item);
    }
    printf("\n");
}

int calc(std::stack<DataForCalc> s, int &UB, int LB, int c, std::vector<Bin> *solution) {
    while (!s.empty()) {
        DataForCalc node = s.top();
        s.pop();
        int z = node.z;
        int z_reduction = node.z_reduction;
        std::vector<Bin> now = node.current;

        if (z + z_reduction == now.size() || now[z + z_reduction].sum == 0) return z + z_reduction;
        int i = z + z_reduction;
        //create a new bin
        if (z + z_reduction < UB) {
            int z1 = z;
            std::vector<Bin> current(now);
            binSort(current);
            z1++;

            int zr = reduction(current, z1, c) + z_reduction;

            int LB_current = lowerBound2(current, c) + zr;
            std::vector<Bin> solution_UB(current);
            int UB_current = bestFit(solution_UB, c) + zr;

            if (UB_current == LB) {
                solution = &solution_UB;
                return UB_current;
            }
            if (UB > UB_current) {
                UB = UB_current;
                solution = &solution_UB;
            }
            bin_print(*solution);
            if (UB_current > LB_current && LB_current < UB) {

                if (z1 + zr < UB) {
                    int L3 = lowerBound3(current, c) + zr;

                    if (L3 < UB) {
//                        printf("FF:%d, LB:%d, L3:%d, z:%d\n", UB_current, LB_current, L3, z1 + zr);
//                        printItems(current);
                        s.push(initData2(current, z1, zr));
                    }
                }

            }

        }

        //to all feasible initialized bins
        int j;
        for (j = z + z_reduction - 1; j >= z_reduction - 1; --j) {
            if (now[j].sum + now[i].sum <= c) {
                int z1 = z;
                std::vector<Bin> current(now);
                mergeBin(current[j], current[i]);
                binSort(current);
//                current[j] += current[i];
//                current[i] = 0;
//                sort(current.rbegin(), current.rend());
                if (current.back().sum == 0) {
                    current.pop_back();            //delete the last item
                }
                int zr = reduction(current, z1, c) + z_reduction;
                int LB_current = lowerBound2(current, c) + zr;
                std::vector<Bin> solution_UB(current);
                int UB_current = bestFit(solution_UB, c) + zr;


                if (UB_current == LB) {
                    solution = &solution_UB;
                    return UB_current;
                }
                if (UB > UB_current) {
                    UB = UB_current;
                    solution = &solution_UB;
                }
                if (UB_current > LB_current && LB_current < UB) {
                    if (z1 + zr < UB) {
                        int L3 = lowerBound3(current, c) + zr;
                        if (L3 < UB) {
//                            printf("FF:%d, LB:%d, L3:%d, z:%d\n", UB_current, LB_current, L3, z1 + zr);
//                            printItems(current);
                            s.push(initData2(current, z1, zr));
                        }
                    }
                }
            }


        }

    }

    return UB;
}


int BNB(DataInput data) {
    std::vector<Bin> *solution;
    std::vector<int> &items = data.w;
    std::vector<Bin> BinList = refactor(items);
    binSort(BinList);

    int c = data.c;
//    sort(items.rbegin(), items.rend());
//    std::vector<int> weight(items);

    int LB = lowerBound2(BinList, c);
    std::vector<Bin> solution_UB(BinList);
    int UB = bestFit(solution_UB, c);
    if (LB == UB) {
        binOrganize(solution_UB,items);
        solution = &solution_UB;
        bin_print(*solution);
        return LB;
    }
    int L3 = lowerBound3(BinList, c);

    if (L3 == UB) {
        binOrganize(solution_UB,items);
        solution = &solution_UB;
        bin_print(*solution);
        return L3;
    }
    int z = 0;
    int z_res = reduction(BinList, z, c);
    solution = &solution_UB;
    std::stack<DataForCalc> s;
    s.push(initData2(BinList, z, z_res));

    int res = calc(s, UB, L3, c, solution);

    binOrganize(solution_UB,items);
    bin_print(*solution);
    return res;
}