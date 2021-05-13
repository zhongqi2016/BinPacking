#include "Algorithm.h"

void printItems(const std::vector<int> &items) {
    for (int item : items) {
        printf("%d ", item);
    }
    printf("\n");
}

int calc(std::stack<DataForCalc> s, int &UB, int LB, int c) {
    while (!s.empty()) {
        DataForCalc node = s.top();
        s.pop();
        int z = node.z;
        int z_reduction = node.z_reduction;
        std::vector<int> now = node.current;

        if (z == now.size() || now[z] == 0) return z + z_reduction;

        int i = z;
        //create a new bin
        if (z < UB - 1) {
            int z1 = z;
            std::vector<int> current(now);
//        current.push_back(items[i]);
            z1++;
            sort(current.rbegin(), current.rend());
            int zr = reduction(current, z1, c) + z_reduction;

            int LB_current = lowerBound2(current, c) + zr;
//            int FF_current = firstFit(current, c) + zr;
            int FF_current = bestFit(current, c) + zr;

            if (FF_current == LB) return FF_current;
            if (UB > FF_current) {
                UB = FF_current;
            }
            if (FF_current > LB_current && LB_current < UB) {

                if (z1 + zr < UB) {
                    int L3 = lowerBound3(current, c) + zr;

                    if (L3 < UB) {
//                        printf("FF:%d, LB:%d, L3:%d, z:%d\n", FF_current, LB_current, L3, z1 + zr);
//                        printItems(current);
                        s.push(initData2(current, z1, zr));
                    }
                }

            }

        }

        //to all feasible initialized bins
        int j;
        for (j = z - 1; j >= 0; --j) {
            if (now[j] + now[i] <= c) {
                int z1 = z;
                std::vector<int> current(now);
                current[j] += current[i];
                current[i] = 0;
                sort(current.rbegin(), current.rend());
                if (current.back() == 0) {
                    current.pop_back();            //delete the last item
                }
                int zr = reduction(current, z1, c) + z_reduction;
                int LB_current = lowerBound2(current, c) + zr;
//                int FF_current = firstFit(current, c) + zr;
                int FF_current = bestFit(current, c) + zr;

                if (FF_current == LB) return FF_current;
                if (UB > FF_current) {
                    UB = FF_current;
                }
                if (FF_current > LB_current && LB_current < UB) {
                    if (z1 + zr < UB) {
                        int L3 = lowerBound3(current, c) + zr;
                        if (L3 < UB) {
//                            printf("FF:%d, LB:%d, L3:%d, z:%d\n", FF_current, LB_current, L3, z1 + zr);
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

    std::stack<DataForCalc> s;
    s.push(initData2(weight, z, z_res));


    int res = calc(s, UB, L3, c);
    return res;


}