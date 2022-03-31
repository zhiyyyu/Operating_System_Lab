#include "tinyfilesystem.h"

FileOperations::FileOperations(){
    op = new DirOperations();
}

FileOperations::~FileOperations(){
    delete op;
}

void FileOperations::touch(string path){
    auto it = path.find_last_of("/");
    Dir* cur_old;
    // 多级目录，先cd
    if(it != string::npos){
        cur_old = TinyFileSystem::cur_dir;
        op->cd(path.substr(0, it));
    }
    string name = path.substr(it+1, path.size()-it);
    File* f = new File();
    // 判断是否有重名的文件
    File* p = TinyFileSystem::cur_dir->head_files;
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
    f->name = name;
    p = TinyFileSystem::cur_dir->head_files;
    TinyFileSystem::cur_dir->head_files = f;
    f->next = p;
    // 切换回工作目录
    TinyFileSystem::cur_dir = cur_old;
    return;
}

void FileOperations::rm(string path){
    auto it = path.find_last_of("/");
    Dir* cur_old;
    // 多级目录，先cd
    if(it != string::npos){
        cur_old = TinyFileSystem::cur_dir;
        op->cd(path.substr(0, it));
    }
    string name = path.substr(it+1, path.size()-it);
    // 判断是否有重名的目录
    File* p = TinyFileSystem::cur_dir->head_files;
    File* pre;
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
    if(p == TinyFileSystem::cur_dir->head_files){
        TinyFileSystem::cur_dir->head_files = p->next;
        free_file(p);
    } else{
        pre->next = p->next;
        free_file(p);
    }
    return;
}

void FileOperations::open(string){

}

void FileOperations::close(string){

}

string FileOperations::read(string path){
    auto it = path.find_last_of("/");
    Dir* cur_old;
    // 多级目录，先cd
    if(it != string::npos){
        cur_old = TinyFileSystem::cur_dir;
        op->cd(path.substr(0, it));
    }
    string name = path.substr(it+1, path.size()-it);
    string content;
    File* p = TinyFileSystem::cur_dir->head_files;
    bool has = false;
    while(p){
        if(p->name == name){
            has = true;
            break;
        }
        p = p->next;
    }
    if(!has){
        qDebug() << "read failed.";
        return "read failed.";
    }
    auto data = p->block_table;
    for(int i=0;i<BLOCK_NUM;i++){
        if(data[i] == -1) break;
        content += string(data_block[data[i]].data);
    }
}

void FileOperations::write(string path, string content) {
    auto it = path.find_last_of("/");
    Dir* cur_old;
    // 多级目录，先cd
    if(it != string::npos){
        cur_old = TinyFileSystem::cur_dir;
        op->cd(path.substr(0, it));
    }
    string name = path.substr(it+1, path.size()-it);
    File* p = TinyFileSystem::cur_dir->head_files;
    bool has = false;
    while(p){
        if(p->name == name){
            has = true;
            break;
        }
        p = p->next;
    }
    if(!has){
        qDebug() << "read failed.";
        return;
    }
    char* buffer = new char[BLOCK_SIZE];
    for(int i=0;i<content.size();i+=BLOCK_SIZE){
        for(int k=0;k<BLOCK_SIZE;k++){
            buffer[k] = content[i*BLOCK_SIZE+k];
        }
        bool canAlloc = false;
        int free_block = get_free_block();
        for(int j=0;j<BLOCK_NUM;j++){
            if(p->block_table[j] == -1){
                canAlloc = true;
                p->block_table[j] = free_block;
            }
        }
        if(canAlloc)
            memcpy(data_block[free_block].data, buffer, sizeof(BLOCK_SIZE));
    }
}

int FileOperations::get_free_block(){
    for(int i=0;i<BLOCK_NUM;i++){
        if(data_block[i].valid == 1){
            return i;
        }
    }
    return -1;
}

void FileOperations::free_file(File *& f){

}
