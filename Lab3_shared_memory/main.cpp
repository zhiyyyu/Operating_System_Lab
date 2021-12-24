//
// Created by narrow on 2021/12/21.
//

#include "main.h"

// subprocess pid
pid_t s1, s2;
int ret = 0;

// shared memory
int head_shm_id;

// semaphore
int sem_id;
senum w, r, mutex;

// fifo
int fifo;

int main(){
    ret = initSharedMemory();
    STATUS(ret, "init shared memory failed");
    ret = initSemaphore();
    STATUS(ret, "init semaphore failed");
    ret = assignSemaphore();
    STATUS(ret, "assign semaphore failed");

    s1 = fork();
    if(s1 == 0){    // writebuf
//        cout << "writebuf subprocess start." << endl;

        char* head_s = (char*)malloc(sizeof(char)*10);
        char* sem_s = (char*)malloc(sizeof(char)*10);
        sprintf(head_s, "%d", head_shm_id);
        sprintf(sem_s, "%d", sem_id);
        char* args[] = {head_s, sem_s, nullptr};
        ret = execv(writebuf_path.c_str(), args);
        STATUS(ret, "runtime error in writebuf");
    } else{
        s2 = fork();
        if(s2 == 0){    // readbuf
//            cout << "readbuf subprocess start." << endl;

            char* head_s = (char*)malloc(sizeof(char)*10);
            char* sem_s = (char*)malloc(sizeof(char)*10);
            sprintf(head_s, "%d", head_shm_id);
            sprintf(sem_s, "%d", sem_id);
            char* args[] = {head_s, sem_s, nullptr};
            ret = execv(readbuf_path.c_str(), args);
            STATUS(-1, "runtime error in readbuf");
        } else{     // main

            waitpid(s1, nullptr, 0);
            waitpid(s2, nullptr, 0);

            ret = delSemaphore();
            STATUS(ret, "delete semaphore failed.");
            ret = delSharedMemory();
            STATUS(ret, "delete shared memory failed.");
        }
    }
}

int initSharedMemory(){
    head_shm_id = shmget(IPC_PRIVATE, sizeof(SharedMemory), IPC_CREAT | 0666);
    SharedMemory* shm = (SharedMemory*) shmat(head_shm_id, nullptr, 0);
    for (int i = 1; i < BUF_CNT; i++) {
//    for (int i = 0; i < BUF_CNT; i++) {
//        key_t shmkey = ftok("./k", i);
        //
        int idShm = shmget(IPC_PRIVATE, sizeof(SharedMemory), IPC_CREAT | 0666);
        shm->next_shm_id = idShm;
        shm = (SharedMemory *)shmat(idShm, nullptr, 0);
    }
    shm->next_shm_id = head_shm_id;
    return 0;
}

int initSemaphore(){
//    key_t shmkey = ftok("./k", BUF_CNT+1);
//    sem_id = semget(shmkey, 3, 0666|IPC_CREAT);
    sem_id = semget(IPC_PRIVATE, 3, 0666|IPC_CREAT);
    return sem_id;
}

int assignSemaphore(){
    r.val = 0;
    ret = semctl(sem_id, 0,SETVAL, r);
    w.val = BUF_CNT;
    ret = semctl(sem_id, 1,SETVAL, w);
    mutex.val = 1;
    ret = semctl(sem_id, 2,SETVAL, mutex);
    return 0;
}

int delSemaphore(){
    return semctl(sem_id, 0,IPC_RMID, mutex);
}

int delSharedMemory(){
    ret = shmctl(head_shm_id, IPC_RMID, 0);
    // TODO delete all

    return ret;
}