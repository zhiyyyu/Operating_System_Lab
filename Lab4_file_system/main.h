//
// Created by narrow on 2021/12/24.
//

#ifndef LAB4_MAIN_H
#define LAB4_MAIN_H

#include <unistd.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <algorithm>

using namespace std;

#define ASSERT(ret, val, str) \
    if((ret) == (val)) { \
        cout << (str) << endl;  \
        exit(-1);               \
    }

// typedef enum ENTRY_TYPE{
//     IS_FILE,
//     IS_DIR
// } ENTRY_TYPE;

typedef struct dirent Dirent;
typedef struct stat Stat;

constexpr int MAX_PATH_LENGTH = 100;
constexpr int MAX_DEPTH_DEFAULT = 4;

void printdir(const char* dir, int depth);
void printDetails(struct stat *statbuf, struct dirent *entry);

#endif //LAB4_MAIN_H
