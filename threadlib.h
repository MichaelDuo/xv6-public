#define PGSIZE 4096
struct lock_t {
  uint locked;
};
void lock_init(struct lock_t*);
void lock_acquire(struct lock_t*);
void lock_release(struct lock_t*);

void thread_create(void *(*)(void*), void *);