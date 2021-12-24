//
// Created by narrow on 2021/12/24.
//

#ifndef LAB4_MAIN_H
#define LAB4_MAIN_H

#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

#define ASSERT(ret, val, str) \
    if((ret) == (val)) { \
        cout << (str) << endl;  \
        exit(-1);               \
    }

void printdir(const char* dir, int depth);

#endif //LAB4_MAIN_H
