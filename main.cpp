#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <dirent.h>

#include "state.h"
#include "UpperBound.h"
#include "LowerBound.h"
#include "Data.h"

using namespace std;


int calc(vector<int> now, int z, int UB, int LB, int z_reduction) {
    if (z == now.size() || now[z] == 0) return z;
    int min_res = UB;

    for (int i = 0; i < now.size(); ++i) {
        printf("%d ", now[i]);
    }
    printf("\n");

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
            current.pop_back();            //delete the last item
            int zr = reduction(current, z1) + z_reduction;
            int LB_current = lowerBound2(current) + zr;
            int FF_current = firstFit(current) + zr;
            if (FF_current == LB) return FF_current;
            if (FF_current == LB_current) {
                if (min_res > FF_current) {
                    min_res = FF_current;
                }
            } else {
                if (UB > FF_current) {
                    UB = FF_current;
                }
                if (LB_current < UB) {
                    int res;
                    if (z1 + z_reduction >= FF_current) res = FF_current;
                    else {
                        printf("FF:%d, LB:%d\n", FF_current, LB_current);
                        res = calc(current, z1, UB, LB, zr);
                    }
                    if (min_res > res) {
                        min_res = res;
                    }
                }
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
        int zr = reduction(current, z1) + z_reduction;
        int LB_current = lowerBound2(current) + zr;
        int FF_current = firstFit(current) + zr;

        if (FF_current == LB) return FF_current;
        if (FF_current == LB_current) {
            if (min_res > FF_current) {
                min_res = FF_current;
            }
        } else {
            if (UB > FF_current) {
                UB = FF_current;
            }
            if (LB_current < UB) {
                int res;
                if (z1 + z_reduction >= FF_current) res = FF_current;
                else {
                    printf("FF:%d, LB:%d\n", FF_current, LB_current);
                    res = calc(current, z1, UB, LB, zr);
                }
                if (min_res > res) {
                    min_res = res;
                }
            }
        }
    }
    return min_res;
}

int BNB(Data data) {
    vector<int> &items=data.w;
    sort(items.rbegin(), items.rend());
    vector<int> weight(items);

    int LB = lowerBound2(weight);
    int UB = firstFit(weight);
    if (LB == UB) return LB;

    int z = 0;
    int reduced = 0;
    int z_res = reduction(weight, z);

//    UB = firstFit(weight);

//    int LB = lowerBound2(weight, 0);
//    int UB = firstFit(weight, 0);

//    int re = reduction(weight, 0);


//    vector<int> now;
//    now.reserve(n);
//    int res = calc(now, 0, 0, UB);


    int res = calc(weight, z, UB, LB, z_res);
    return res;


}

bool compare(int a, int b) {
    return a > b;

}

vector<string> readFileDir(string PATH) {
    struct dirent *ptr;
    DIR *dir;
    dir = opendir(PATH.c_str());
    vector<string> files;
    while ((ptr = readdir(dir)) != NULL) {
        if (ptr->d_name[0] == '.')
            continue;
//        printf("%s\n", ptr->d_name);
        files.push_back(ptr->d_name);
    }
    return files;
}

Data getData(string filename) {
    int n,c;
    vector<int> items;
    string path = "./data/";
    path.append(filename);
    ifstream infile(path);
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
        items.push_back(num);
    }
    infile.close();

    return initData(n,c,items);
}

int main() {
    vector<string> files = readFileDir("data");
    for (int i = 0; i < files.size(); ++i) {
        printf("%d. filename: %s\n", i, files[i].c_str());
        Data data=getData(files[i]);
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
