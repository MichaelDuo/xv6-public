#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char * argv[])
{
    if(argc<2){
        printf(1, "Please select mode, 1, 2, 3\n");
    } else if(argc>2){
        printf(1, "Unsupported params, please select mode, 1, 2, 3\n");
    } else {
        int mode = atoi(argv[1]);
        // printf(1, "Using mode %d\n", mode);
        info(mode);
    }

    exit();
}