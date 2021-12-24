//
// Created by narrow on 2021/12/21.
//

#include "main.h"

int ret;
int head_shm_id;
int sem_id;

int main(int argc, char** argv){
    cout << "writebuf start." << endl;

    head_shm_id = atoi(argv[0]);
    sem_id = atoi(argv[1]);
    cout << head_shm_id << " " << sem_id << endl;

    SharedMemory* data[BUF_CNT];
    data[0] = (SharedMemory *)shmat(head_shm_id, nullptr, 0);
    for(int i=1;i<BUF_CNT;i++){
        data[i] = (SharedMemory *)shmat(data[i-1]->next_shm_id, nullptr, 0);
    }

//    for(int i=1;i<BUF_CNT;i++){
//        key_t shmkey = ftok("./k", i);
//        int shmid = shmget(shmkey, sizeof(SharedMemory), IPC_CREAT | 0666);
//        data[i] = (SharedMemory *) shmat(shmid, nullptr, 0);
//    }
//    key_t shmkey = ftok("./k", BUF_CNT+1);
//    sem_id = semget(shmkey, 3, 0666|IPC_CREAT);

    FILE* output = fopen(dst_path.c_str(),"wb");

    int i=0;
    while (1) {     // 从缓冲区读出，写入文件
        // 读信号灯
        P(sem_id, 0);
        P(sem_id, 2);
        fwrite(data[i]->buf, sizeof(char), data[i]->write_size, output);
        if(data[i]->write_size < BUF_SIZE){
            V(sem_id, 2);
            V(sem_id, 1);
            break;
        }
        cout << "writing ..." << i << " size " << data[i]->write_size << endl;
//        out = out->next;
//        data[i] = (SharedMemory*) shmat(data[i]->next_shm_id, nullptr, 0);
        i = (i+1)%BUF_CNT;
        V(sem_id, 2);
        // 写信号灯
        V(sem_id, 1);

    }
//    sleep(1);
    fclose(output);
}