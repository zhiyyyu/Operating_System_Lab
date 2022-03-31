#include "tinyfilesystem.h"

//void DirOperations::free_dir(Dir *& dir);
//Dir* DirOperations::create_dir(string path);

void DirOperations::mkdir(string path){
    auto it = path.find_last_of("/");
    Dir* cur_old;
    // 多级目录，先cd
    if(it != string::npos){
        cur_old = TinyFileSystem::cur_dir;
        cd(path.substr(0, it));
    }
    string name = path.substr(it+1, path.size()-it);
    Dir* d = new Dir();
    // 判断是否有重名的目录
    Dir* p = TinyFileSystem::cur_dir->head_dirs;
    bool hasSame = false;
    while(p){
        if(p->name == name){
            hasSame = true;
            break;
        }
        p = p->next;
    }
    if(hasSame){
        qDebug() << "same dir";
        return;
    }
    d->name = name;
    p = TinyFileSystem::cur_dir->head_dirs;
    TinyFileSystem::cur_dir->head_dirs = d;
    d->next = p;
    d->head_dirs = nullptr;
    d->parent = TinyFileSystem::cur_dir;
    d->head_files = nullptr;
    // 切换回工作目录
    TinyFileSystem::cur_dir = cur_old;
    return;
}

void DirOperations::rmdir(string path){
    auto it = path.find_last_of("/");
    Dir* cur_old;
    // 多级目录，先cd
    if(it != string::npos){
        cur_old = TinyFileSystem::cur_dir;
        cd(path.substr(0, it));
    }
    string name = path.substr(it+1, path.size()-it);
    // 判断是否有重名的目录
    Dir* p = TinyFileSystem::cur_dir->head_dirs;
    Dir* pre;
    bool has = false;
    while(p){
        if(p->name == name){
            has = true;
            break;
        }
        pre = p;
        p = p->next;
    }
    if(!has){
        qDebug() << "rmdir failed.";
        return;
    }
    // 是头结点
    if(p == TinyFileSystem::cur_dir->head_dirs){
        TinyFileSystem::cur_dir->head_dirs = p->next;
        free_dir(p);
    } else{
        pre->next = p->next;
        free_dir(p);
    }
    return;
}

void DirOperations::cd(string path){
    // 处理绝对路径
    if(path[0] == '/'){
        TinyFileSystem::cur_dir = TinyFileSystem::root;
        cd("."+path);
        return;
    }
    // 按/划分，每次cd一级目录
    auto it = path.find("/");
    int start = 0;
    while(it != string::npos){
        Dir* p = TinyFileSystem::cur_dir->head_dirs;
        if(!p){
            qDebug() << "failed to cd.";
            return;
        }
        bool hasSub = true;
        while(p){
            if(p->name == path.substr(start, it-start)){
                hasSub = true;
                break;
            }
            p = p->next;
        }
        if(!hasSub){
            qDebug() << "failed to cd.";
            return;
        }
        start = it+1;
        TinyFileSystem::cur_dir = p;
        it = path.find("/", start);
    }
    return;
}

void DirOperations::ls(){
    Dir* p = TinyFileSystem::cur_dir->head_dirs;
    while(p){
        qDebug() << QString::fromStdString(p->name);
        p = p->next;
    }
    File* f = TinyFileSystem::cur_dir->head_files;
    while(f){
        qDebug() << QString::fromStdString(f->name);
        f = f->next;
    }
}

void DirOperations::readdir(string path){

}

void DirOperations::free_dir(Dir *& dir){
    dir->next = nullptr;
    dir->parent = nullptr;
    dir->head_dirs = nullptr;
    dir->head_files = nullptr;
    delete dir;
    return;
}

Dir* DirOperations::create_dir(string name){
    Dir* d = new Dir();
    d->name = name;
    d->next = nullptr;
    d->parent = nullptr;
    d->head_dirs = nullptr;
    d->head_files = nullptr;
    return d;
}
