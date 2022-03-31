#include <unistd.h>  
#include <stdio.h>  
#include <dirent.h>  
#include <string.h>  
#include <sys/stat.h>  
#include <stdlib.h>
#include <fcntl.h>
#include <string>
#include <algorithm>
#include <grp.h>
#include <pwd.h>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

#define MAX_PATH_LENGTH (100)
#define BUFSIZE (1024)
char buf[MAX_PATH_LENGTH];

typedef struct dirent Dirent;
typedef struct stat Stat;
 
int copy_file(const char* src, const char* dst){

    char buf[BUFSIZE];
    
    int src_fd = open(src, O_RDONLY, 0666);
    if(src_fd == -1)
    {
        printf("Source file %s doesn't not exist! \n", src);
        return 1;
    }
 
    int dst_fd = open(dst, O_WRONLY | O_CREAT, 0666);
    if(dst_fd == -1)
    {
        printf("Dest file %s can't be created! \n", dst);
        return 1;
    }
 
    int num = -1;
    while((num = read(src_fd, buf, BUFSIZE)) > 0)
    {
        write(dst_fd, buf, num);
    }
    
    close(src_fd);
    close(dst_fd);
    return 0;
}

// dir是相对路径
void copy_dir(const char* src, const char* dst, int depth){
    // if(depth >= max_depth){
    //     return;
    // }

    Dirent* entry = (Dirent* )malloc(sizeof(Dirent));
    Stat* statbuf = (Stat* )malloc(sizeof(Stat));

    char* ret_p = getcwd(buf, MAX_PATH_LENGTH);

    // old_path 是当前目录的绝对路径
    string old_path(buf);
    string cur_path(src);
    string dst_path(dst);
    if(src[0] == '/'){
        cur_path = string(src);
    } else{
        cur_path = old_path+"/"+string(src);
    }
    if(dst[0] == '/'){
        dst_path = string(dst);
    } else{
        dst_path = old_path+"/"+string(dst);
    }
    // cout << old_path << " " << cur_path << " " << dst_path << endl;
    DIR* cur_dir = opendir(cur_path.c_str());
    int ret = chdir(cur_path.c_str());

    // sort
    vector<Dirent*> entries;
    while((entry = readdir(cur_dir))){
        entries.emplace_back(entry);
    }
    int n = entries.size();

    // sort(entries.begin(), entries.end(), [&](Dirent *&a, Dirent *&b)->bool{
    //     return strcasecmp(a->d_name, b->d_name) < 0;
    // });

    // 读取当前目录下的目录项
    for(int i=0;i<n;i++){
        ret = lstat(entries[i]->d_name, statbuf);

        if(statbuf->st_mode & S_IFDIR){ // dir

            if(entries[i]->d_name[0] == '.'){
                continue;
            }
            // printDetails(statbuf, entries[i]);
            // 子目录的目录名
            copy_dir((cur_path+string(entries[i]->d_name)).c_str(), (dst_path+string(entries[i]->d_name)).c_str(), depth+1);
            // next_dirs.emplace_back(string(entries[i]->d_name));

        } else if(statbuf->st_mode & S_IFREG){ // file
            // printDetails(statbuf, entries[i]);
            copy_file((cur_path+string(entries[i]->d_name)).c_str(), (dst_path+string(entries[i]->d_name)).c_str());
        }
    }

    // int size = next_dirs.size();
    // for(int i=0;i<size;i++){
    //     copy_dir(cur_path, dst_path, depth+1);
    // }
    closedir(cur_dir);
    ret = chdir(old_path.c_str());
    return;
    
}

int main(int argc,char* argv[])
{ 
    if(argc < 3){
        printf("Usage: cp [path1] [path2]\n");
        return 1;
    }
    struct stat buffer;
    stat(argv[1], &buffer);
    if(S_ISDIR(buffer.st_mode)){
        copy_dir(argv[1], argv[2], 0);
    } else{
        printf("src: %s, dst: %s\n", argv[1], argv[2]);
        long ret = copy_file(argv[1], argv[2]);
        printf("return code is: %ld\n", ret);
    }    
    return 0;
}

