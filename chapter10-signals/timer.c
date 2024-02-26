#include <time.h>
#include <stdlib.h>
#include "apue.h"

struct Timer
{
    time_t expire;
    void (*callback)(time_t);
};

struct Timer_List
{
    struct Timer *timer;
    struct Timer_List *next;
    struct Timer_List *prev;
};

static struct Timer_List *timer_list_head = NULL;

struct Timer *new_timer(size_t _time, void (*callback)(time_t))
{
    struct Timer *new_timer = (struct Timer *)malloc(sizeof(struct Timer));
    new_timer->callback = callback;
    new_timer->expire = time(NULL) + _time;
    return new_timer;
}

void addTimer(struct Timer *timer)
{
    struct Timer_List *new_timer_list_node = (struct Timer_List *)malloc(sizeof(struct Timer_List));

    new_timer_list_node->timer = timer;

    if (!timer_list_head)
    {
        timer_list_head = new_timer_list_node;
        timer_list_head->prev = timer_list_head->next = NULL;
    }
    else
    {
        struct Timer_List *temp = timer_list_head;
        while (temp->next && temp->next->timer->expire <= timer->expire)
        {
            temp = temp->next;
        }

        if (temp->next)
        {
            new_timer_list_node->next = temp;
            new_timer_list_node->prev = temp->prev;
            new_timer_list_node->next->prev = new_timer_list_node;
            new_timer_list_node->prev->next = new_timer_list_node;
        }
        else
        {
            new_timer_list_node->prev = temp;
            new_timer_list_node->next = NULL;
            temp->next = new_timer_list_node;
        }
    }

    alarm(timer_list_head->timer->expire - time(NULL));
}

void delTimer(struct Timer *timer)
{
    if (timer_list_head == NULL)
    {
        return;
    }

    struct Timer_List *temp = timer_list_head;
    while (temp && temp->timer != timer)
    {
        temp = temp->next;
    }

    if (temp)
    {
        if (temp == timer_list_head)
        {
            timer_list_head = timer_list_head->next;
        }
        else
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        free(temp);

        if (!timer_list_head)
        {
            alarm(0);
        }
        else
        {
            alarm(timer_list_head->timer->expire - time(NULL));
        }
    }
}

static void sig_alarm(int signo)
{
    time_t cur = time(NULL);

    struct Timer_List *temp = timer_list_head, *temp_next;
    while (temp && temp->timer->expire <= cur)
    {
        temp->timer->callback(temp->timer->expire);
        temp_next = temp->next;
        free(temp);
        temp = temp_next;
    }
    timer_list_head = temp;

    if (timer_list_head)
    {
        alarm(timer_list_head->timer->expire - cur);
    }
}

void initTimerList()
{
    if (signal_reli(SIGALRM, sig_alarm) < 0)
    {
        err_sys("signal error");
    }
}

void callback(time_t _time)
{
    printf("cur is %ld, expire is %ld\n", time(NULL), _time);
}

int main()
{
    initTimerList();

    addTimer(new_timer(5, callback));
    addTimer(new_timer(10, callback));
    addTimer(new_timer(15, callback));
    addTimer(new_timer(20, callback));

    for (;;)
        pause();

    return 0;
}