#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findLRU(int temp_time[], int n){
    //Find Least Recently Used page
	int minimum = temp_time[0], pos = 0;
	for(int i = 1; i < n; ++i){
		if(temp_time[i] < minimum){
			minimum = temp_time[i];
			pos = i;
		}
	}
	
	return pos;
}
 
int main(){

int counter = 0,flag1, flag2, pos, faults = 0;

srand((unsigned)time(NULL));

//Randomly generate frames
int  no_of_frames = (rand() % 7) + 1;
int *frames = malloc(no_of_frames*sizeof(int));
printf("random number of Frames(1~7): %d\n",no_of_frames);

//Randomly generate pages
int  no_of_pages = (rand() % 20) + 1;
int *temp_time = malloc(no_of_pages * sizeof(int));
int *pages = malloc(no_of_pages * sizeof(int));
printf("random number of pages(1~20): %d\n",no_of_pages);

//Randomly generate reference string
printf("reference string(0~9): ");
for(int i = 0; i < no_of_pages; ++i){
    int random_num = rand() % 10;
    pages[i] = random_num;
    printf("%d ",pages[i]);
}
printf("\n");

//Page initialization    
for(int i = 0; i < no_of_frames; ++i)
    frames[i] = -1;

//LRU Algorithm
for(int i = 0; i < no_of_pages; ++i){
    flag1 = flag2 = 0;
    //If page still exist in frames
    for(int j = 0; j < no_of_frames; ++j){
        if(frames[j] == pages[i]){
            counter++;
            temp_time[j] = counter;
            flag1 = flag2 = 1;
            break;
        }
    }

    //Case 1 : If frame is empty then replace null with page
    if(flag1 == 0){
        for(int j = 0; j < no_of_frames; ++j){
            if(frames[j] == -1){
                counter++;
                faults++;
                frames[j] = pages[i];
                temp_time[j] = counter;
                flag2 = 1;
                break;
            }
        }
    }
    
    //Case 2 : If frame is not empty then replace the least recently used page
    if(flag2 == 0){
        pos = findLRU(temp_time, no_of_frames);
        counter++;
        faults++;
        frames[pos] = pages[i];
        temp_time[pos] = counter;
    }
    

    //Frames output    
    printf("\n");
    for(int j = 0; j < no_of_frames; ++j)
        printf("%d\t", frames[j]);

}

printf("\n\nTotal Page Faults = %d", faults);
    
return 0;
}