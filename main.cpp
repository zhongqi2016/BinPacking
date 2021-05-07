#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <dirent.h>

//#include "state.h"
#include "UpperBound.h"
#include "LowerBound.h"
#include "Data.h"

using namespace std;

//void printItems(const vector<int> &items) {
//    for (int i = 0; i < items.size(); ++i) {
//        printf("%d ", items[i]);
//    }
//    printf("\n");
//}

int calc(stack<Data2> s, int UB, int LB, int c) {
//    int min_res = UB;
    while (!s.empty()) {
        Data2 node = s.top();
        s.pop();
        int z = node.z;
        int z_reduction = node.z_reduction;
        vector<int> now = node.current;

        if (z == now.size() || now[z] == 0) return z + z_reduction;


        int j;
        int i = z;

        //to all feasible initialized bins
        for (j = 0; j < z; ++j) {
            if (now[j] + now[i] <= c) {
                int z1 = z;
                vector<int> current(now);
                current[j] += current[i];
                current[i] = 0;
                sort(current.rbegin(), current.rend());
                if (current.back() == 0) {
                    current.pop_back();            //delete the last item
                }
                int zr = reduction(current, z1, c) + z_reduction;
                int LB_current = lowerBound2(current, c) + zr;
                int FF_current = firstFit(current, c) + zr;
//                printf("Lb %d,FF %d\n", LB_current, FF_current);


                if (FF_current == LB) return FF_current;
                if (UB > FF_current) {
                    UB = FF_current;
                }
                if (FF_current > LB_current && LB_current < UB) {
                    if (z1 + zr <= UB) {
//                        printf("FF:%d, LB:%d\n", FF_current, LB_current);
                        s.push(initData2(current, z1, zr));
                    }
//                        int res;
//                        if (z1 + z_reduction >= FF_current) res = FF_current;
//                        else {
//                            printf("FF:%d, LB:%d\n", FF_current, LB_current);
////                            res = calc(current, z1, UB, LB, zr);
//                            s.push(initData2(current, z1, z_reduction));
//                        }
//                        if (min_res > res) {
//                            min_res = res;
//                        }
                }
            }


        }
        //create a new bin
        if (j == z && z < UB) {
            int z1 = z;
            vector<int> current(now);
//        current.push_back(items[i]);
            z1++;
            sort(current.rbegin(), current.rend());
            int zr = reduction(current, z1, c) + z_reduction;
            int LB_current = lowerBound2(current, c) + zr;
            int FF_current = firstFit(current, c) + zr;

            if (FF_current == LB) return FF_current;
            if (UB > FF_current) {
                UB = FF_current;
            }
            if (FF_current > LB_current && LB_current < UB) {

                if (z1 + zr <= UB) {
//                    printf("FF:%d, LB:%d\n", FF_current, LB_current);
                    s.push(initData2(current, z1, zr));
                }
//                    int res;
//                    if (z1 + z_reduction >= FF_current) res = FF_current;
//                    else {
//                        printf("FF:%d, LB:%d\n", FF_current, LB_current);
////                        res = calc(current, z1, UB, LB, zr);
//                        s.push(initData2(current, z1, z_reduction));
//                    }
//                    if (min_res > res) {
//                        min_res = res;
//                    }
            }

        }
    }
    return UB;
}

int BNB(Data data) {
    vector<int> &items = data.w;
    int n = data.n;
    int c = data.c;
    sort(items.rbegin(), items.rend());
    vector<int> weight(items);

    int LB = lowerBound2(weight, c);
    int UB = firstFit(weight, c);
    if (LB == UB) return LB;
    int L3= lowerBound3(weight,c);
    int z = 0;
//    int reduced = 0;
    int z_res = reduction(weight, z, c);

    stack<Data2> s;
    s.push(initData2(weight, z, z_res));
//    UB = firstFit(weight);

//    int LB = lowerBound2(weight, 0);
//    int UB = firstFit(weight, 0);

//    int re = reduction(weight, 0);


//    vector<int> now;
//    now.reserve(n);
//    int res = calc(now, 0, 0, UB);


    int res = calc(s, UB, LB, c);
    return res;


}


vector<string> readFileDir(const string &PATH) {
    struct dirent *ptr;
    DIR *dir;
    dir = opendir(PATH.c_str());
    vector<string> files;
    while ((ptr = readdir(dir)) != nullptr) {
        if (ptr->d_name[0] == '.')
            continue;
//        printf("%s\n", ptr->d_name);
        files.emplace_back(ptr->d_name);
    }
    return files;
}

Data getData(const string &filename) {
    int n, c;
    vector<int> items;
//    string path = "./bin1data/";
//    path.append(filename);
    ifstream infile(filename);
    string line;

    getline(infile, line);
    istringstream iss_n(line);
    iss_n >> n;
    getline(infile, line);
    istringstream iss_c(line);
    iss_c >> c;

    items.reserve(n);

    while (getline(infile, line)) {
        int num;
        istringstream iss(line);
        iss >> num;
        items.emplace_back(num);
    }
    infile.close();

    return initData(n, c, items);
}

int main() {
    string path = "./bin1data/";
    vector<string> files = readFileDir(path);
    for (int i = 0; i < files.size(); ++i) {
        printf("%d. filename: %s\n", i, files[i].c_str());
        string fileName = path;
        fileName.append(files[i]);
        Data data = getData(fileName);
        clock_t start, end;
        start = clock();

        int result = BNB(data);
        end = clock();
        double time = (double) (end - start) / CLOCKS_PER_SEC;
        printf("Number of bins needed = %d\nTime=%lf\n", result, time);
        break;
    }

    return 0;
}
