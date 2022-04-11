//
// Created by narrow on 2021/12/23.
//

#include "main.h"

char buf[MAX_PATH_LENGTH];
int ret = 0;
int max_depth = 0;

int main(int argc, char** args){
    cout << "receive: " << argc << " params" << endl;
    string target_dir;

    if(argc < 2){
        cout << "use default path : ." << endl;
        target_dir = ".";
        cout << "use default depth : " << MAX_DEPTH_DEFAULT << endl << endl;
        max_depth = MAX_DEPTH_DEFAULT;
    } else if(argc < 3) {
        target_dir = string(args[1]);
        cout << "target dir: " << target_dir << endl;
        cout << "use default depth : " << MAX_DEPTH_DEFAULT << endl << endl;
        max_depth = MAX_DEPTH_DEFAULT;
    } else {
        target_dir = string(args[1]);
        max_depth = atoi(args[2]);
        cout << "target dir: " << target_dir << endl;
        cout << "depth: " << max_depth << endl << endl;
    }
    printdir(target_dir.c_str(), 0);

    return 0;
}

// dir是相对路径
void printdir(const char* dir, int depth){

    if(depth >= max_depth){
        return;
    }

    Dirent* entry = (Dirent* )malloc(sizeof(Dirent));
    Stat* statbuf = (Stat* )malloc(sizeof(Stat));
    vector<string> next_dirs;

    char* ret_p = getcwd(buf, MAX_PATH_LENGTH);
    ASSERT(ret_p, nullptr, "get current working directory failed");

    // old_path 是当前目录的绝对路径
    string old_path(buf);
    string cur_path;
    if(dir[0] == '/'){
        cur_path = string(dir);
    } else{
        cur_path = old_path+"/"+string(dir);
    }

    DIR* cur_dir = opendir(cur_path.c_str());
    ASSERT(cur_dir, nullptr, "open " + cur_path + " dir failed");
    
    ret = chdir(cur_path.c_str());
    ASSERT(ret, -1, "chdir to " + cur_path + " failed.");
//    cout << "current working path: " << cur_path << endl;
    cout << endl << cur_path << " :" << endl;

    // sort
    vector<Dirent*> entries;
    while((entry = readdir(cur_dir))){
        entries.emplace_back(entry);
    }
    int n = entries.size();

    sort(entries.begin(), entries.end(), [&](Dirent *&a, Dirent *&b)->bool{
        return strcasecmp(a->d_name, b->d_name) < 0;
    });


    // 读取当前目录下的目录项
    for(int i=0;i<n;i++){
//        cout << "sorted entried: " << entries[i]->d_name << endl;
        ret = lstat(entries[i]->d_name, statbuf);
        ASSERT(ret, -1, "lstat failed.");

        if(statbuf->st_mode & S_IFDIR){ // dir

            if(entries[i]->d_name[0] == '.'){
                continue;
            }
            printDetails(statbuf, entries[i]);
            // 子目录的目录名
            next_dirs.emplace_back(string(entries[i]->d_name));

        } else if(statbuf->st_mode & S_IFREG){ // file
            printDetails(statbuf, entries[i]);
        }
    }

    int size = next_dirs.size();
    for(int i=0;i<size;i++){
        printdir(next_dirs[i].c_str(), depth+1);
    }
    closedir(cur_dir);
    ret = chdir(old_path.c_str());
    ASSERT(ret, -1, "chdir to " + old_path + " failed.");

    return;
}

void printDetails(struct stat *statbuf, struct dirent *entry) {
    // 文件权限
    cout << ( (S_ISDIR(statbuf->st_mode))  ? "d" : "-") <<
        ( (statbuf->st_mode & S_IRUSR) ? "r" : "-") <<
        ( (statbuf->st_mode & S_IWUSR) ? "w" : "-") <<
        ( (statbuf->st_mode & S_IXUSR) ? "x" : "-") <<
        ( (statbuf->st_mode & S_IRGRP) ? "r" : "-") <<
        ( (statbuf->st_mode & S_IWGRP) ? "w" : "-") <<
        ( (statbuf->st_mode & S_IXGRP) ? "x" : "-") <<
        ( (statbuf->st_mode & S_IROTH) ? "r" : "-") <<
        ( (statbuf->st_mode & S_IWOTH) ? "w" : "-") <<
        ( (statbuf->st_mode & S_IXOTH) ? "x" : "-");
    // 用户组
    struct passwd *uid = getpwuid(statbuf->st_uid);
    struct group *gid = getgrgid(statbuf->st_gid);
    // 最后修改时间
    char last_modified_time[20];
    struct tm *local_time = localtime(&(statbuf->st_mtim.tv_sec));
    strftime(last_modified_time, 20, "%Y-%b-%d %H:%M", local_time);
    cout << " " << statbuf->st_nlink <<
         " " << uid->pw_name <<
         " " << gid->gr_name <<
         " " << statbuf->st_size <<
         " " << last_modified_time <<
         " " << entry->d_name <<
         endl;
}