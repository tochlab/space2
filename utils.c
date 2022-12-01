#include "utils.h"

#include <sys/time.h>

int64_t time_now_mks() {
    struct timeval time_now = {0,0};
    gettimeofday(&time_now, 0);
    return time_now.tv_sec * 1000000 + time_now.tv_usec;
}

int64_t elapsed_time_mks(struct timeval a, struct timeval b) {
    int64_t a_mks = a.tv_sec * 1000000 + a.tv_usec;
    int64_t b_mks = b.tv_sec * 1000000 + b.tv_usec;
    return a_mks - b_mks;
}

