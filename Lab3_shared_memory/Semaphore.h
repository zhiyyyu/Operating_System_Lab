//
// Created by narrow on 2021/12/21.
//

#ifndef LAB3_SEMAPHORE_H
#define LAB3_SEMAPHORE_H

#include <sys/sem.h>
#include <sys/types.h>

void P(int semid, int index);
void V(int semid, int index);

#endif //LAB3_SEMAPHORE_H
