#ifndef COPY_H
#define COPY_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>

using namespace std;

#define STATUS(ret, str) \
    if((ret) == -1)              \
        cout << (str) << endl;


// functions
int initSharedMemory();
int inline initSemaphore();
int inline assignSemaphore();
int inline delSemaphore();
int delSharedMemory();
void P(int semid, int index);
void V(int semid, int index);
void copy(string src, string dst);

// file path
static string src_path = "./utils/src.jpg";
static string dst_path = "./utils/dst.jpg";
static string writebuf_path = "./bin/writebuf";
static string readbuf_path = "./bin/readbuf";

// buf params
constexpr static int BUF_CNT = 10;
constexpr static int BUF_SIZE = 50;    // byte

// shared memory
typedef struct _SharedMemory {
    char buf[BUF_SIZE];
    int next_shm_id;
    int write_size;
} SharedMemory;

// semaphore
typedef union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO */
} senum;


#endif // COPY_H
