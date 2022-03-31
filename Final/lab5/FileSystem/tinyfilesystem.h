#ifndef TINYFILESYSTEM_H
#define TINYFILESYSTEM_H

#include <QDebug>

#include <string>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;

#define BLOCK_SIZE  512
#define BLOCK_NUM   10

typedef struct File{
    string name;                // 文件名
    File*  next;                // 同级文件
    int block_table[BLOCK_NUM]; // 使用的块号
} File;

typedef struct Dir{
    string name;                // 目录名
    Dir* head_dirs;             // 子目录
    Dir* parent;                // 上级目录
    Dir* next;                  // 同级目录
    File* head_files;           // 文件
} Dir;

typedef struct DataBlock{
    char data[BLOCK_SIZE];
    bool valid;
} DataBlock;

typedef struct SuperBlock{
//    string type;
    int inode_num;
    int free_block_num;
} SuperBlock;

typedef struct BitMapEntry{
    int first;
    int num;
} BitMapEntry;

class DirOperations{
public:
    void mkdir(string);
    void rmdir(string);
    void cd(string);
    void ls(void);
    void readdir(string);

public:
    static void free_dir(Dir*&);
    static Dir* create_dir(string);
};

class FileOperations{
public:
    FileOperations();
    ~FileOperations();

    void touch(string);
    void rm(string);
    void open(string);
    void close(string);
    string read(string);
    void write(string, string);

private:
    DirOperations* op;
    void free_file(File*&);
    File* create_file(string);
    int get_free_block();
};

static string fs_img = "../fs.img";
//static char* base_p;
static DataBlock data_block[BLOCK_NUM-2];

class TinyFileSystem
{
public:
    TinyFileSystem();
    ~TinyFileSystem();

    void Init();

 public:
    static Dir* root;
    static Dir* cur_dir;

private:
    void initSuperBlock();
    void initBitMap();

private:
    SuperBlock superb;
    vector<BitMapEntry> bitmap;
};

#endif // TINYFILESYSTEM_H
