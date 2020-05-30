#include "types.h"
#include "stat.h"
#include "user.h"
#include "threadlib.h"

struct player_args {
    int t_id;
    int passes;
    int *next;
    int *total_player;
    int *rounds;
    struct lock_t *lock;
};

void *player(void *input){
    struct player_args *args = (struct player_args*) input;
    while(1){
        lock_acquire(args->lock);
        if(*(args->rounds)>=args->passes){
            lock_release(args->lock);
            break;
        }
        if(*(args->next)==args->t_id){
            *(args->next) = (*(args->next)+1) % *(args->total_player);
            *(args->rounds) += 1;
            printf(1, "Pass number %d, thread %d is passing the token to thread %d\n", *(args->rounds), args->t_id, *(args->next));
        } else {
            lock_release(args->lock);
        }
        lock_release(args->lock);
    }
    return 0;
}

void play(int players, int passes){
    int i;
    int token = 0;
    int rounds = 0;
    struct lock_t lock;
    lock_init(&lock);

    for(i=0; i<players; i++){
        struct player_args *args = (struct player_args *)malloc(sizeof(struct player_args));
        args->t_id = i;
        args->passes = passes;
        args->next = &token;
        args->total_player = &players;
        args->rounds = &rounds;
        args->lock = &lock;

        thread_create(player, args);
    }
    for(i=0; i<players; i++){
        wait();
    }
    printf(1, "Simulation of Frisbee game has finished, 6 rounds were played in total!\n");
    exit();
}

int main(int argc, char * argv[])
{
    if(argc<3){
        printf(1, "Two arguments needed\n");
        return 1;
    }
    int players = atoi(argv[1]);
    int passes = atoi(argv[2]);
    play(players, passes);
    exit();
}