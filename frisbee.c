#include "types.h"
#include "stat.h"
#include "user.h"
#include "threadlib.h"

struct player_args {
    int t_id;
    int passes;
    int *next;
    int *total_player;
};

void *player(void *input){
    struct player_args *args = (struct player_args*) input;
    printf(1, "t_id: %d\n", args->t_id);
    return 0;
}

void play(int players, int passes){
    int i;
    int token = 0;
    // TODO: init lock
    for(i=0; i<players; i++){
        struct player_args *args = (struct player_args *)malloc(sizeof(struct player_args));
        args->t_id = i;
        args->passes = passes;
        args->next = &token;
        args->total_player = &players;
        thread_create(player, args);
    }
    for(i=0; i<players; i++){
        // TODO: wait threads
    }
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