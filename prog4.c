#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


#define TIME_MAX 5
#define RAND_MAX 100

/* buffer setting */
#define BUFFER_SIZE 5
typedef int buffer_item;


/* thread setting */
pthread_t t_consumer;
pthread_t t_producer;
pthread_mutex_t mutex;

/* function */
void *producer();               //Thread function for producer
void *consumer();               //Thread function for consumer
int insert_item(buffer_item);   //Producer insert item
int remove_item(buffer_item);   //Consumer remove item
int FullOrEmpty();              //Check buffer is full or empty

/* global variables */
buffer_item buffer[BUFFER_SIZE];
buffer_item item;                   

int main(){
    srand(time(NULL));
    for (int k;k<BUFFER_SIZE;k++) buffer[k]=-1;   //Initialize buffer
    
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&t_producer,NULL,producer,buffer);
    pthread_create(&t_consumer,NULL,consumer,buffer);
    pthread_join(t_producer,NULL);
    pthread_join(t_consumer,NULL);
    
return 0;
}



void *producer(){
    while (1){
        /* Enter critical section  */
        pthread_mutex_lock(&mutex);
        /*Insert item start*/
            if (FullOrEmpty() != 0){
                item=rand() % RAND_MAX;
                if(insert_item(item)==-1)   printf("Producer ERROR!\n");
                else                        printf("Producer produced:%d\n",item);
                printf("buffer:%d %d %d %d %d\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
            }
        /* Exit critical section */
        pthread_mutex_unlock(&mutex);
        
        /*Producer sleep for random_time_producer seconds */
        int random_time_producer=(rand() % TIME_MAX) + 1;
        printf("Producer sleep %d second(s)\n\n",random_time_producer);
        sleep(random_time_producer);
    }
}


void *consumer(){
    while (1){
        /* Enter critical section  */
        pthread_mutex_lock(&mutex);
            /*Remove_item start*/
            if (FullOrEmpty() != 1){
                if(remove_item(item)==-1)  printf("Consumer ERROR!\n");
            }    
        /* Exit critical section */   
        pthread_mutex_unlock(&mutex);
        
        /*Consumer sleep for random_time_consumer seconds */
        int random_time_consumer=(rand() % TIME_MAX)+1;
        printf("Consumer sleep %d second(s)\n\n",random_time_consumer);
        sleep(random_time_consumer);
    }
}


int insert_item(buffer_item item){
    for (int i=0;i<BUFFER_SIZE;i++){
        if (buffer[i] == -1){
            buffer[i]=item;
            return 1;
        }
    }
    return -1;
}

int remove_item(buffer_item item){
    if (buffer[0] != -1){
        printf("Consumer consumed:%d\n",buffer[0]);
        for (int j=0;j<BUFFER_SIZE-1;j++){
        buffer[j]=buffer[j+1];                      //shift the buffer   
        }
        buffer[BUFFER_SIZE-1]=-1;                   //set -1 means remove first item 
        printf("buffer:%d %d %d %d %d\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
        return 1;
    }
    else return -1;
}


int FullOrEmpty(){
    int count=0;
    for (int x=0;x<BUFFER_SIZE;x++)
        if (buffer[x]==-1)
            count++;
    
    if (count==5)           return 1;  //Empty
    else if (count==0)      return 0;  //Full
    else                    return -1; //Not Full or Empty
}