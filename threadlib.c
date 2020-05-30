#include "types.h"
// #include "stat.h"
// #include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "threadlib.h"

void thread_create(void *(*routine)(void*), void *arg){
    // (*routine)(arg);
    clone(0, 0);
}

void lock_init(struct lock_t *lk){
    lk->locked = 0;
}

void lock_acquire(struct lock_t *lk){
    while(xchg(&(lk->locked), 1)!=0);
}

void lock_release(struct lock_t *lk){
    xchg(&(lk->locked), 0);
}