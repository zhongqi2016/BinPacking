
#include "Algorithm.h"

void getDetermined(std::vector<Bin> &solution, std::list<Bin> &current) {
    for (auto it = current.rbegin(); it != current.rend(); ++it) {
        if (it->sum == 0 && it->serial.size() != 0) {
            solution.emplace_back(*it);
        } else break;
    }
}


std::vector<Bin> calc(std::stack<DataForCalc> &s, int &UB, int LB, int c) {
    std::vector<Bin> *solution = NULL;
    std::vector<Bin> solution_UB;
    solution_UB.reserve(UB);

    while (!s.empty()) {
        DataForCalc node = s.top();
        s.pop();
        int &z = node.z;
        int &z_reduction = node.z_reduction;
        std::list<Bin> now = node.current;
//        skipDetermined(now, ++z);
//        if (z == now.size() || now[z].sum == 0) return now;
        //create a new bin
        auto iterator_z= std::next(now.begin(),z);
        ++iterator_z;
        if (iterator_z->sum==0) break;

        if (z < UB - 1) {
            int z1 = z;
            ++z1;
//            auto iterator_z = node.iterator;
//            ++iterator_z;
            std::list<Bin> current(now);
//            binSort(current);
//            skipDetermined(current,++z1);
            int zr = reduction(current, z1, c) + z_reduction;

            int LB_current = lowerBound2(current, c) + zr;
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

                if (z1 + zr < UB) {
                    int L3 = lowerBound3(current, c) + zr;

                    if (L3 < UB) {

                        s.push(initData2(&current, z1, zr));
                    }
                }

            }

        }

        //to all feasible initialized bins
        for (int j = z - 1; j >= 0; --j) {
            std::list<Bin> current(now);
            auto iterator_j= std::next(current.begin(),j);
            auto iterator_i=std::next(iterator_j,z-j);

            if (iterator_i->sum == 0) break;
            if (iterator_j->sum + iterator_i->sum <= c) {
                int z1 = z;
//                printf("%d:%d<-%d:%d\n",j,current[j].sum,i,current[i].sum);

                mergeBin(current, iterator_i, iterator_j);
                --z1;
                int zr = reduction(current, z1, c) + z_reduction;
                int LB_current = lowerBound2(current, c) + zr;
                solution_UB.clear();
//                std::vector<Bin> solution_UB;
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
                    if (z1 + zr < UB) {
                        int L3 = lowerBound3(current, c) + zr;
                        if (L3 < UB) {

                            s.push(initData2(&current, z1, zr));
                        }
                    }
                }
            }


        }

    }


    if (!solution) {
        return {};
    }
    bin_print(*solution);
    return *solution;
}


int BNB(DataInput data) {
    std::vector<Bin> *solution = NULL;
    std::vector<int> &items = data.w;
    std::sort(items.rbegin(), items.rend());
    std::list<Bin> binList = refactor(items);

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
    s.push(initData2(&binList, z, z_res));
    std::vector<Bin> res_calc = calc(s, UB, L3, c);
    if (res_calc.size() == 0) {
        solution = &solution_UB;
    } else { solution = &res_calc; }
    binOrganize(*solution, items);
    bin_print(*solution);
    return solution->size();
}