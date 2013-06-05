/*
 * =====================================================================================
 *
 *       Filename:  pthread2.c
 *
 *    Description:  no mutex and have mutex
 *
 *        Version:  1.0
 *        Created:  06/04/2013 03:40:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;

void *thread_function(void *arg);

int run_now = 1;

int main(int argc, char **argv)
{
    int print_count1 = 0;
    pthread_t a_thread;

    if(pthread_create(&a_thread, NULL, thread_function, NULL) != 0 )
    {
        perror("thread creation failed.\n");
        exit(1);
    }

    while(print_count1++ < 5)
    {
        pthread_mutex_lock(&condition_mutex);
        printf("main cond_mutex lock. \n");
        pthread_cond_wait(&condition_cond, &condition_mutex);
        pthread_mutex_unlock(&condition_mutex);
        printf("main cond_mutex unlock. \n");
        if(pthread_mutex_lock(&mutex) == 0)
        {
            printf("main lock. \n");
        }
        if(run_now == 2)
        { 
            printf("main thread is run .\n");
            run_now = 1;
        }
        else
        {
            printf("main thread is sleep\n");
            usleep(10);
        }
        if(pthread_mutex_unlock(&mutex) == 0)
        {
            printf("main unlock. \n");
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_join(a_thread, NULL);
    exit(0);
}

void *thread_function(void *arg)
{
    int print_count2 = 0;

    while(print_count2++ < 5)
    {
        if(pthread_mutex_lock(&mutex) == 0)
        {
            printf("thread lock. \n");
        }
        if(run_now == 1)
        {
            printf("function thread is run. \n");
            run_now = 2;
            pthread_mutex_lock(&condition_mutex);
            pthread_cond_signal(&condition_cond);
            pthread_mutex_unlock(&condition_mutex);
        }
        else
        {
            printf("function thread is sleep:\n");
            usleep(10);
        }
        if(pthread_mutex_unlock(&mutex) == 0)
        {
            printf("thread unlock. \n");
        }
    }

    pthread_exit(NULL);
}
