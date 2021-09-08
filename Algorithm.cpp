
#include "Algorithm.h"

void getDetermined(std::vector<Bin> &solution, std::vector<Bin> &current) {
    for (int i = 0; i < current.size(); ++i) {
        if (current[i].sum == 0 && current[i].serial.size() != 0) {
            solution.emplace_back(current[i]);
        }
    }
}

void skipDetermined(std::vector<Bin> &w, int &z) {
    for (; z < w.size(); ++z) {
        if (w[z].sum != 0) break;
    }
}


std::vector<Bin> calc(std::stack<DataForCalc> s, int &UB, int LB, int c) {
    std::vector<Bin> *solution = NULL;
    while (!s.empty()) {
        DataForCalc node = s.top();
        s.pop();
        int z = node.z;
        int z_reduction = node.z_reduction;
        std::vector<Bin> now = node.current;
        skipDetermined(now, ++z);
        if (z == now.size() || now[z].sum == 0) return now;
        int i = z;
        //create a new bin

        if (z < UB - 1) {
            int z1 = z;
            std::vector<Bin> current(now);
//            binSort(current);
//            skipDetermined(current,++z1);
            int zr = reduction(current, z1, c) + z_reduction;

            int LB_current = lowerBound2(current, c) + zr;
            std::vector<Bin> solution_UB;
            int UB_current = bestFit(current, c, solution_UB) + zr;

            if (UB_current == LB) {
                solution = &solution_UB;
                getDetermined(*solution, current);
                return *solution;
            }
            if (UB > UB_current) {
                UB = UB_current;
                solution = &solution_UB;
                getDetermined(*solution, current);
            }
            if (UB_current > LB_current && LB_current < UB) {

                if (binUsed(current, z1) + zr < UB) {
                    int L3 = lowerBound3(current, c) + zr;

                    if (L3 < UB) {

                        s.push(initData2(current, z1, zr));
                    }
                }

            }

        }

        //to all feasible initialized bins
        int j;
        for (j = z - 1; j >= 0; --j) {

            if (now[j].sum == 0) continue;
            if (now[j].sum + now[i].sum <= c) {
                int z1 = z;
                std::vector<Bin> current(now);
//                printf("%d:%d<-%d:%d\n",j,current[j].sum,i,current[i].sum);
                mergeBin(current[j], current[i]);

                int zr = reduction(current, z1, c) + z_reduction;
                int LB_current = lowerBound2(current, c) + zr;
                std::vector<Bin> solution_UB;
                int UB_current = bestFit(current, c, solution_UB) + zr;

//                bin_print(solution_UB);
                if (UB_current == LB) {
                    solution = &solution_UB;
                    getDetermined(*solution, current);
                    return *solution;
//                    return UB_current;
                }
                if (UB > UB_current) {
                    UB = UB_current;
                    solution = &solution_UB;
                    getDetermined(*solution, current);
                }
                if (UB_current > LB_current && LB_current < UB) {
                    if (binUsed(current, z1) + zr < UB) {
                        int L3 = lowerBound3(current, c) + zr;
                        if (L3 < UB) {

                            s.push(initData2(current, z1, zr));
                        }
                    }
                }
            }


        }

    }

    if (!solution) {
        return {};
    }

    return *solution;
}


int BNB(DataInput data) {
    std::vector<Bin> *solution = NULL;
    std::vector<int> &items = data.w;
    std::vector<Bin> binList = refactor(items);
    binSort(binList);
//    bin_print(binList);
    int c = data.c;

    int LB = lowerBound2(binList, c);
    std::vector<Bin> solution_UB;

    int UB = bestFit(binList, c, solution_UB);
    if (LB == UB) {
        binOrganize(solution_UB, items);
        solution = &solution_UB;
        bin_print(*solution);
        return LB;
    }
    int L3 = lowerBound3(binList, c);

    if (L3 == UB) {
        binOrganize(solution_UB, items);
        solution = &solution_UB;
        bin_print(*solution);
        return L3;
    }
    int z = 0;
//    std::vector<Bin> determined(UB);
    int z_res = reduction(binList, z, c);
    std::stack<DataForCalc> s;
    s.push(initData2(binList, z, z_res));
    std::vector<Bin> res_calc = calc(s, UB, L3, c);
    if (res_calc.size() == 0) {
        solution = &solution_UB;
    } else { solution = &res_calc; }

    binOrganize(*solution, items);
    bin_print(*solution);
    return solution->size();
}