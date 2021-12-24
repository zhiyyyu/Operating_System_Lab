//
// Created by narrow on 2021/12/23.
//

#include <unistd.h>
#include "main.h"

int main(int argc, char** args){
    cout << "receive: " << argc << " params" << endl;
    string target_dir;
    if(argc < 2){
        cout << "use default path : ." << endl;
        target_dir = ".";
    } else{
        target_dir = string(args[1]);
        cout << "target dir: " << target_dir << endl;
    }
    printdir(target_dir.c_str(), 0);

    return 0;
}

void printdir(const char* dir, int depth){
    DIR* root_dir = opendir(dir);
    ASSERT(root_dir, nullptr, "open target dir failed");
    struct dirent* entry;
    struct stat* statbuf;
    int ret = 0;
    ret = chdir(dir);
    ASSERT(ret, -1, "chdir failed.");

    while((entry = readdir(root_dir))){
        ret = lstat(entry->d_name, statbuf);
        ASSERT(ret, -1, "lstat failed.");
        if(statbuf->st_mode & S_IFDIR){ // dir

        } else if(statbuf->st_mode & S_IFREG){ // file

        }
    }
}