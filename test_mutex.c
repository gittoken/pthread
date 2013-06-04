/*
 * =====================================================================================
 *
 *       Filename:  
 *
 *    Description: mutex test 
 *
 *        Version:  1.0
 *        Created: 
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *function_count(void);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

int main(int argc, char **argv)
{
    int rc1, rc2;
    pthread_t thread1, thread2;

    if(rc1 = pthread_create(&thread1, NULL, (void*) function_count, NULL))
    {
        printf("thread creation failed:%d\n", rc1);
    }
    if(rc2 = pthread_create(&thread2, NULL, (void *)function_count, NULL))
    {
        printf("thread creation failed:%d\n", rc2);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

void *function_count(void)
{
    int i;
    pthread_mutex_lock(&mutex1);
    for(i=0;i<4;i++)
    {
        counter++;
        printf("pid:%ld ", pthread_self());
        printf("counter value:%d\n", counter);
    }
    pthread_mutex_unlock(&mutex1);
}
