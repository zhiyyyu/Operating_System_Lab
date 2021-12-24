//
// Created by narrow on 2021/12/7.
//

#include <iostream>
#include <csignal>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;

void sigint_handler(int );
void kill1(int );
void kill2(int );

constexpr int MAX_MSG = 10;
constexpr int BUF_SIZE = 100;
int pipefd[2];  // 1 for write, 0 for read
char buffer[BUF_SIZE];
pid_t s1, s2;
int rcv1, rcv2;

int main(){
    int ret = pipe(pipefd);
    if(ret == -1){
        cout << "error in creating pipe." << endl;
        return -1;
    }
    signal(SIGINT, sigint_handler);
    s1 = fork();
    if(s1 == 0){
        close(pipefd[1]);
        cout << "child process1 starts." << endl;
        signal(SIGINT, SIG_IGN);
        signal(SIGUSR1, kill1);
        while(1){
            memset(buffer, 0, BUF_SIZE);
            ret = read(pipefd[0], buffer, BUF_SIZE);
            if(ret == 0){
                close(pipefd[0]);
                break;
            }
            cout << "child process1 receive: " << buffer << endl;
            rcv1++;
        }
        cout << "child process1 has received " << rcv1 << " msgs." << endl;
        cout << "child process1 is killed by parent." << endl;
        sleep(1);
//        exit(0);
    } else{
        s2 = fork();
        if(s2 == 0){
            close(pipefd[1]);
            cout << "child process2 starts." << endl;
            signal(SIGINT, SIG_IGN);
            signal(SIGUSR2, kill2);
            while(1){
                memset(buffer, 0, BUF_SIZE);
                ret = read(pipefd[0], buffer, BUF_SIZE);
                if(ret == 0){
                    close(pipefd[0]);
                    break;
                }
                cout << "child process2 receive: " << buffer << endl;
                rcv2++;
            }
            cout << "child process2 has received " << rcv2 << " msgs." << endl;
            cout << "child process2 is killed by parent." << endl;
            sleep(1);
//            exit(0);
        } else{
            close(pipefd[0]);
            cout << "parent process starts." << endl;

            int cnt = 1;
            while(1){
                sprintf(buffer, "I send you %d times.", cnt);
                write(pipefd[1], buffer, BUF_SIZE);
                cnt++;
                sleep(1);
                if(cnt > MAX_MSG){
                    break;
                }
            }
            close(pipefd[1]);
            waitpid(s1, nullptr, 0);
            waitpid(s2, nullptr, 0);
            cout << "parent process is killed." << endl;
        }
    }
    return 0;
}

void sigint_handler(int ){
    kill(s1, SIGUSR1);
    kill(s2, SIGUSR2);
    waitpid(s1, nullptr, 0);
    waitpid(s2, nullptr, 0);
    close(pipefd[1]);
    cout << "parent process is killed." << endl;
    exit(0);
}

void kill1(int ){
    close(pipefd[0]);
    cout << "child process1 has received " << rcv1 << " msgs." << endl;
    cout << "child process1 is killed by parent." << endl;
    sleep(1);
    exit(0);
}

void kill2(int ){
    close(pipefd[0]);
    cout << "child process2 has received " << rcv2 << " msgs." << endl;
    cout << "child process2 is killed by parent." << endl;
    sleep(1);
    exit(0);
}