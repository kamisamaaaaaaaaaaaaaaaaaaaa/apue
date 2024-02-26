#include "my_barrier.h"

int my_pthread_barrier_init(struct my_barrier *barrier, size_t cnt)
{
    barrier->cnt = cnt;
    barrier->cur = 0;

    int err;
    if ((err = pthread_mutex_init(&barrier->mu, NULL)) != 0)
    {
        return err;
    }

    return pthread_cond_init(&barrier->cond, NULL);
}

int my_pthread_barrier_destroy(struct my_barrier *barrier)
{
    int err;
    if ((err = pthread_mutex_destroy(&barrier->mu)) != 0)
    {
        pthread_cond_destroy(&barrier->cond);
        return err;
    }
    return pthread_cond_destroy(&barrier->cond);
}

int my_pthread_barrier_wait(struct my_barrier *barrier)
{
    pthread_mutex_lock(&barrier->mu);

    if (barrier->cur == barrier->cnt)
    {
        barrier->cur = 0;
    }

    ++barrier->cur;

    if (barrier->cur == barrier->cnt)
    {
        pthread_cond_broadcast(&barrier->cond);
        pthread_mutex_unlock(&barrier->mu);
        return 0;
    }

    while (barrier->cur < barrier->cnt)
    {
        pthread_cond_wait(&barrier->cond, &barrier->mu);
    }

    pthread_mutex_unlock(&barrier->mu);
    return 0;
}