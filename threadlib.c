#include "types.h"
#include "user.h"
#include "x86.h"
#include "threadlib.h"

void thread_create(void *(*routine)(void*), void *arg){
    void *stack = malloc(PGSIZE*2);
    if((uint)stack % PGSIZE)
        stack = stack + (PGSIZE - (uint)stack % PGSIZE);
    int id;
    id = clone(stack, PGSIZE*2);
    if(id==0){
        (*routine)(arg);
        free(stack);
        exit();
    }
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