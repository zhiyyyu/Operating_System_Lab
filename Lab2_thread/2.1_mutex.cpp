//
// Created by narrow on 2021/12/15.
//

#include <iostream>
#include <sys/sem.h>
#include <sys/types.h>
#include <pthread.h>

using namespace std;

void* subp1(void* );
void* subp2(void* );
void P(int semid, int index);
void V(int semid, int index);

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
};

int sem_id;
union semun arg;
pthread_t t1, t2;
int tickets = 100;

int main(){
    sem_id = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
    if(sem_id == -1){
        cout << "semget failed." << endl;
        return -1;
    }

    arg.val = 1;
    int ret = semctl(sem_id,0,SETVAL,arg);
    if(ret == -1){
        cout << "sectl failed." << endl;
        return -1;
    }

    ret = pthread_create(&t1, nullptr, subp1, nullptr);
    ret = pthread_create(&t2, nullptr, subp2, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    ret = semctl(sem_id,0,IPC_RMID,arg);
    if(ret == -1){
        cout << "sectl failed." << endl;
        return -1;
    }
    return 0;
}

void* subp1(void* ){
    int cnt = 0;
    while(tickets > 0){
        P(sem_id, 0);
        if(tickets > 0){
            cnt++;
            cout << "ticket " << tickets << " has been sold." << endl;
            tickets--;
        }
        V(sem_id, 0);
    }
    cout << "thread1 has sold " << cnt << " tickets." << endl;
}

void* subp2(void* ){
    int cnt = 0;
    while(tickets > 0){
        P(sem_id, 0);
        if(tickets > 0){
            cnt++;
            cout << "ticket " << tickets << " has been sold." << endl;
            tickets--;
        }
        V(sem_id, 0);
    }
    cout << "thread2 has sold " << cnt << " tickets." << endl;
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
}