//
// Created by narrow on 2021/12/15.
//

#include <iostream>
#include <sys/sem.h>
#include <sys/types.h>
#include <pthread.h>

using namespace std;

void* compute(void* );
void* print1(void* );
void* print2(void* );
void P(int semid, int index);
void V(int semid, int index);

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
};

int sem_id;
union semun arg0, arg1, arg2, del;
pthread_t t0, t1, t2;
int a = 0;
int cnt = 0;

int main(){
    sem_id = semget(IPC_PRIVATE, 3, 0666|IPC_CREAT);
    if(sem_id == -1){
        cout << "semget failed." << endl;
        return -1;
    }

    int ret = 0;
    arg0.val = 1;
    ret = semctl(sem_id,0,SETVAL,arg0);
    if(ret == -1){
        cout << "sectl failed." << endl;
        return -1;
    }
    arg1.val = 0;
    ret = semctl(sem_id,1,SETVAL,arg1);
    if(ret == -1){
        cout << "sectl failed." << endl;
        return -1;
    }
    arg2.val = 0;
    ret = semctl(sem_id,2,SETVAL,arg2);
    if(ret == -1){
        cout << "sectl failed." << endl;
        return -1;
    }

    ret = pthread_create(&t0, nullptr, compute, nullptr);
    ret = pthread_create(&t1, nullptr, print1, nullptr);
    ret = pthread_create(&t2, nullptr, print2, nullptr);


    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t0, nullptr);

//    ret = semctl(sem_id,0,IPC_RMID,arg0);
//    if(ret == -1){
//        cout << "sectl failed." << endl;
//        return -1;
//    }
//    ret = semctl(sem_id,1,IPC_RMID,arg1);
//    if(ret == -1){
//        cout << "sectl failed." << endl;
//        return -1;
//    }
    ret = semctl(sem_id,0,IPC_RMID,del);
    if(ret == -1){
        cout << "sectl failed." << endl;
        return -1;
    }
    return 0;
}

void* compute(void* ){
    for(int i=1;i<=100;i++){
        P(sem_id, 0);
        a += i;
        if(a & 1){
            V(sem_id, 1);
        } else{
            V(sem_id, 2);
        }
    }
}

void* print1(void* ){
    while(1){
        P(sem_id, 1);
        if(cnt < 100){
            cout << "print1 " << a << endl;
            cnt++;
        } else break;
        if(cnt == 100){
            V(sem_id, 2);
            break;
        }
        V(sem_id, 0);
    }
}

void* print2(void* ){
    while(1){
        P(sem_id, 2);
        if(cnt < 100){
            cout << "print2 " << a << endl;
            cnt++;
        } else break;
        if(cnt == 100){
            V(sem_id, 1);
            break;
        }
        V(sem_id, 0);
    }
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