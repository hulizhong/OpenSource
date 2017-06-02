/*************************************************************************
	> File Name: pthread_lock_test.c
	> Author: 
	> Mail: 
	> Created Time: Thursday, May 11, 2017 AM11:08:39 HKT
 ************************************************************************/

#include <pthread.h>  
#include <stdio.h>  
#include <stdlib.h>  

/*
    pthread_cond_wait()具有原子解锁、加锁功能。
    pthread_cond_signal() 则没有以上功能。
*/
/*
pthread_cond_wait() 必须与pthread_mutex 配套使用。
pthread_cond_wait()函数一进入wait状态就会自动release mutex。
当其他线程通过pthread_cond_signal()或pthread_cond_broadcast，把该线程唤醒，使pthread_cond_wait()通过（返回）时，该线程又自动获得该mutex。

pthread_cond_signal函数的作用是发送一个信号给另外一个正在处于阻塞等待状态的线程,使其脱离阻塞状态,继续执行.
如果没有线程处在阻塞等待状态,pthread_cond_signal也会成功返回。
*/

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;/*初始化互斥锁*/  
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;/*初始化条件变量*/  
void *thread1(void *);  
void *thread2(void *);  
int i=1;  

int main(void)  
{  
    pthread_t t_a;  
    pthread_t t_b;  
    pthread_create(&t_a,NULL,thread1,(void *)NULL);/*创建进程t_a*/  
    pthread_create(&t_b,NULL,thread2,(void *)NULL); /*创建进程t_b*/  
    pthread_join(t_a, NULL);/*等待进程t_a结束*/  
    pthread_join(t_b, NULL);/*等待进程t_b结束*/  
    pthread_mutex_destroy(&mutex);  
    pthread_cond_destroy(&cond);  
    exit(0);  
}  

void *thread1(void *junk)  
{  
    for(i=1;i<=6;i++)  
    {  
        pthread_mutex_lock(&mutex);/*锁住互斥量*/  
        printf("thread1: lock %d\n", __LINE__);  
        if(i%3==0){  
            printf("thread1:signal 1  %d\n", __LINE__);  
            pthread_cond_signal(&cond);/*条件改变，发送信号，通知t_b进程*/ /*不会马上切换到被通知线程，因为此线程还未对互斥锁进行解锁。*/  
            printf("thread1:signal 2  %d\n", __LINE__);
            sleep(5);  
        }  
        pthread_mutex_unlock(&mutex);/*解锁互斥量*/  
        printf("thread1: unlock %d\n\n", __LINE__);  
        sleep(1);  
    }  
}  

void *thread2(void *junk)  
{  
    while(i<6)  
    {  
        pthread_mutex_lock(&mutex);  
        printf("thread2: lock %d\n", __LINE__);  
        if(i%3!=0){  
            printf("thread2: wait 1  %d\n", __LINE__);  
            pthread_cond_wait(&cond,&mutex);/*解锁mutex，并等待cond改变*/  
            printf("thread2: wait 2  %d\n", __LINE__);  
        }  
        pthread_mutex_unlock(&mutex);  
        printf("thread2: unlock %d\n\n", __LINE__);  
        sleep(1);  
    }  
}  

