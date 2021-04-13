#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


int input_size=10;

int *num;

pthread_t t1;
pthread_t t2;
pthread_t t3;

int *init_random();
void *create();
void *bubble_sort(parameters);

typedef struct{
    int starting;
    int ending;
}parameters;
int main(){
    create();
    printf("\n");
    
    printf("Merge Result:\n");
    for (int k=0;k<input_size;k++){
        printf("%d ",num[k]);
    }
    return 0;
}

//initial random number 
int *init_random(){
    srand(time(NULL));
    printf("Please enter input size:");
    scanf("%d",&input_size);
    int *rnd_arr=malloc(input_size*sizeof(int));
  
    printf("Random Number:\n");
    for (int i=0;i < input_size;i++){
    rnd_arr[i]=rand()%100;
    printf("%d ",rnd_arr[i]);
    }
    printf("\n");
    return rnd_arr;
}

//thread create
void *create(){
    num=malloc(input_size*sizeof(int));
    num=init_random();
    parameters *data1=(parameters *)malloc(sizeof(parameters));
    parameters *data2=(parameters *)malloc(sizeof(parameters));
    data1->starting=0;
    data1->ending=input_size/2;
    data2->starting=data1->ending;
    data2->ending=input_size;
    
    //sort1,sort2 thread
    pthread_create(&t1,NULL,bubble_sort,data1);
    pthread_create(&t2,NULL,bubble_sort,data2);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("Sort1 & Sort2 Thread:\n");
    for (int k=0;k<input_size;k++){
        printf("%d ",num[k]);
    }


    //merge two sorting result
    parameters *data3=(parameters *)malloc(sizeof(parameters));
    data3->starting=0;
    data3->ending=input_size;
    pthread_create(&t3,NULL,bubble_sort,data3);
    pthread_join(t3,NULL);
}

void *bubble_sort(parameters *data){
    int data_start=data->starting;
    int data_end=data->ending;
    int qunatity=(data->ending)-(data->starting);
    for (int times=0;times<qunatity;times++){
        for(int start=data_start;start<data_end-times-1;start++){
            if (num[start]>num[start+1]){
                int temp=num[start+1];
                num[start+1]=num[start];
                num[start]=temp;
            } 
        }
    }
}