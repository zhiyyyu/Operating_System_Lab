#include "tinyfilesystem.h"

Dir* TinyFileSystem::root;
Dir* TinyFileSystem::cur_dir;

TinyFileSystem::TinyFileSystem(){
    bitmap = vector<BitMapEntry>(64);
//    root = DirOperations::create_dir("../root");
//    cur_dir = DirOperations::create_dir("../root");
    for(int i=0;i<BLOCK_NUM;i++){
        data_block[i].valid = 1;
    }
    Init();
}

TinyFileSystem::~TinyFileSystem(){
//    DirOperations::free_dir(cur_dir);
//    DirOperations::free_dir(root);
}

void TinyFileSystem::Init(){
    initSuperBlock();
    initBitMap();
}

void TinyFileSystem::initSuperBlock(){
    superb.inode_num = 0;
    superb.free_block_num = BLOCK_NUM - 2;
}

void TinyFileSystem::initBitMap(){
    bitmap[0].first = 2;
    bitmap[0].num = BLOCK_NUM - 2;
    for(int i=1;i<64;i++){
        bitmap[i].first = -1;
        bitmap[i].num = 0;
    }
}
