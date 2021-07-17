#include <iostream>
#include "Algorithm.h"

using namespace std;

vector<string> readFileDir(const string &PATH) {
    struct dirent *ptr;
    DIR *dir;
    const char *p = PATH.c_str();
    dir = opendir(p);
    vector<string> files;
    while ((ptr = readdir(dir)) != nullptr) {
        if (ptr->d_name[0] == '.')
            continue;
//        printf("%s\n", ptr->d_name);
        files.emplace_back(ptr->d_name);
    }
    return files;
}

DataInput getData(const string &filename) {
    int n, c;
    vector<int> items;

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
    int th=omp_get_max_threads();
    printf("thread num:%d\n",th);
    omp_set_num_threads(8);
    double start0 = omp_get_wtime();
    for (int i = 0; i < files.size(); ++i) {
        if (i==5) continue;
        printf("%d. filename: %s\n", i, files[i].c_str());
        string fileName = path;
        fileName.append(files[i]);
        DataInput data = getData(fileName);
        double start, end;
        start = omp_get_wtime();

        int result = BNB(data);
        end = omp_get_wtime();
        double time = (double) (end - start) ;
        double sum = (double) (end - start0) ;

        printf("Number of bins needed = %d\n, Time=%f, Sum=%f\n", result,time,sum);
//        break;
    }

    return 0;
}