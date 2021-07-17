#include "Algorithm.h"

void printItems(const std::vector<int> &items) {
    for (int item : items) {
        printf("%d ", item);
    }
    printf("\n");
}



int calc(DataForCalc &node, int &UB, int LB, int c) {

//#pragma omp parallel for
//    {
    if (UB == LB) return UB;
    int z = node.z;
    int z_reduction = node.z_reduction;
    std::vector<int> now = node.current;

    if (z == now.size() || now[z] == 0) return z + z_reduction;

    //to all feasible initialized bins

    for (int j = 0; j < z; ++j) {
        {
                printf("id=%d\n", omp_get_thread_num());
            if (now[j] + now[z] <= c) {
                int z1 = z;
                std::vector<int> current(now);
                current[j] += current[z];
                current[z] = 0;
                sort(current.rbegin(), current.rend());
                if (current.back() == 0) {
                    current.pop_back();            //delete the last item
                }
                int zr = reduction(current, z1, c) + z_reduction;
                int LB_current = lowerBound2(current, c) + zr;
//                int FF_current = firstFit(current, c) + zr;
                int FF_current = bestFit(current, c) + zr;

#pragma omp critical
                if (UB > FF_current) {
                    UB = FF_current;
                }
                if (UB != LB) {
//                return UB;

                    if (FF_current > LB_current && LB_current < UB) {
                        if (z1 + zr < UB) {
                            int L3 = lowerBound3(current, c) + zr;
                            if (L3 < UB) {

                                DataForCalc newData = initData2(current, z1, zr);

#pragma omp task  shared(UB) firstprivate(newData,c,LB)  default(none)
                                calc(newData, UB, LB, c);
                            }
                        }
                    }
                }
            }
        }
    }

    {
        //create a new bin
        if (z < UB - 1) {
            int z1 = z;
            std::vector<int> current(now);
            z1++;
            sort(current.rbegin(), current.rend());
            int zr = reduction(current, z1, c) + z_reduction;

            int LB_current = lowerBound2(current, c) + zr;
            int FF_current = bestFit(current, c) + zr;

#pragma omp critical
            if (UB > FF_current) {
                UB = FF_current;
            }
            if (UB != LB) {

                if (FF_current > LB_current && LB_current < UB) {

                    if (z1 + zr < UB) {
                        int L3 = lowerBound3(current, c) + zr;

                        if (L3 < UB) {

                            DataForCalc newData = initData2(current, z1, zr);

#pragma omp task  shared(UB) firstprivate(newData,c,LB)  default(none)
                            calc(newData, UB, LB, c);
                        }
                    }

                }
            }
        }
    }


//    }
    return UB;
}

int BNB(DataInput data) {
    std::vector<int> &items = data.w;
    int c = data.c;
    sort(items.rbegin(), items.rend());
    std::vector<int> weight(items);

    int LB = lowerBound2(weight, c);
    int UB = firstFit(weight, c);
    if (LB == UB) return LB;
    int L3 = lowerBound3(weight, c);

    if (L3 == UB) return L3;
    int z = 0;
    int z_res = reduction(weight, z, c);

//    std::stack<DataForCalc> s;
//    s.push(initData2(weight, z, z_res));
    DataForCalc calcData = initData2(weight, z, z_res);
    int res;
#pragma omp parallel shared(res,UB)
    {

#pragma omp single
        res= calc(calcData, UB, L3, c);
    }
    return UB;


}