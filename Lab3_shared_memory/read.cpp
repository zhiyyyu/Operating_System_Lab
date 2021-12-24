//
// Created by narrow on 2021/12/21.
//

#include "main.h"

int ret;
int head_shm_id;
int sem_id;

int main(int argc, char** argv){
    cout << "readbuf start." << endl;

    head_shm_id = atoi(argv[0]);
    sem_id = atoi(argv[1]);
    cout << head_shm_id << " " << sem_id << endl;

    SharedMemory* data[BUF_CNT];
//    for(int i=0;i<BUF_CNT;i++){
//        key_t shmkey = ftok("./k", i);
//        int shmid = shmget(shmkey, sizeof(SharedMemory), IPC_CREAT | 0666);
//        data[i] = (SharedMemory *) shmat(shmid, nullptr, 0);
//    }

    data[0] = (SharedMemory *)shmat(head_shm_id, nullptr, 0);
    for(int i=1;i<BUF_CNT;i++){
        data[i] = (SharedMemory *)shmat(data[i-1]->next_shm_id, nullptr, 0);
    }
//    key_t shmkey = ftok("./k", BUF_CNT+1);
//    sem_id = semget(shmkey, 3, 0666|IPC_CREAT);

    FILE* input = fopen(src_path.c_str(),"rb");

    int i = 0;
    int size;
    char tmp[BUF_SIZE+1];
    while ((size=fread(tmp,sizeof(char),BUF_SIZE,input))!=0) {     // 从文件中读出，写入缓冲区
        // 写信号灯
        P(sem_id, 1);
        P(sem_id, 2);

        memcpy(data[i]->buf, tmp, size);
//        cout << tmp << endl;
        data[i]->write_size = size;
//        in = in->next;
//        in = (SharedMemory*) shmat(in->next_shm_id, nullptr, 0);
        i = (i+1)%BUF_CNT;
        cout << "reading ..." << i << " size " << size << endl;
        V(sem_id, 2);
        // 读信号灯
        V(sem_id, 0);
    }
//    sleep(1);
    fclose(input);
}