//
// Created by narrow on 2021/12/21.
//

#include "copy.h"

// subprocess pid
pid_t s1, s2;
int ret = 0;

// shared memory
int head_shm_id;

// semaphore
int sem_id;
senum w, r, mutex;

void copy(string src, string dst){
    src_path = src;
    dst_path = dst;
    cout << src_path << " " << dst_path << endl;
//    ret = initSharedMemory();
//    ret = initSemaphore();
//    ret = assignSemaphore();

    s1 = fork();
    if(s1 == 0){    // writebuf
        cout << "read proc" << endl;
//        char* head_s = (char*)malloc(sizeof(char)*10);
//        char* sem_s = (char*)malloc(sizeof(char)*10);
//        sprintf(head_s, "%d", head_shm_id);
//        sprintf(sem_s, "%d", sem_id);
//        char* args[] = {head_s, sem_s, nullptr};
//        ret = execv(writebuf_path.c_str(), args);
    } else{
        s2 = fork();
        if(s2 == 0){    // readbuf
            cout << "write proc" << endl;
//            char* head_s = (char*)malloc(sizeof(char)*10);
//            char* sem_s = (char*)malloc(sizeof(char)*10);
//            sprintf(head_s, "%d", head_shm_id);
//            sprintf(sem_s, "%d", sem_id);
//            char* args[] = {head_s, sem_s, nullptr};
//            ret = execv(readbuf_path.c_str(), args);
        } else{     // main
//            waitpid(s1, nullptr, 0);
//            waitpid(s2, nullptr, 0);
//            ret = delSemaphore();
//            ret = delSharedMemory();
        }
    }
    return;
}

int initSharedMemory(){
    head_shm_id = shmget(IPC_PRIVATE, sizeof(SharedMemory), IPC_CREAT | 0666);
    SharedMemory* shm = (SharedMemory*) shmat(head_shm_id, nullptr, 0);
    for (int i = 1; i < BUF_CNT; i++) {
        int idShm = shmget(IPC_PRIVATE, sizeof(SharedMemory), IPC_CREAT | 0666);
        shm->next_shm_id = idShm;
        shm = (SharedMemory *)shmat(idShm, nullptr, 0);
    }
    shm->next_shm_id = head_shm_id;
    return 0;
}

int initSemaphore(){
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

void P(int semid, int index){
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}

void V(int semid, int index){
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}
