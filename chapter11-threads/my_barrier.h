#include <unistd.h>
#include <pthread.h>

struct my_barrier
{
    size_t cnt;
    size_t cur;
    size_t saved_cur;
    pthread_mutex_t mu;
    pthread_cond_t cond;

    short allowed;
    pthread_cond_t allowed_cond;
    pthread_mutex_t allowed_mu;
};

int my_pthread_barrier_init(struct my_barrier *barrier, size_t cnt);

int my_pthread_barrier_wait(struct my_barrier *barrier);

int my_pthread_barrier_destroy(struct my_barrier *barrier);