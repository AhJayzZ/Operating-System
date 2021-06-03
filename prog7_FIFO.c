#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
      int pageFaults = 0;
      int duplicated = 0 ,pos = 0;
      
      srand(time(NULL));

      int no_of_frames = (rand() % 7) + 1;
      int *frames= malloc(no_of_frames * sizeof(int));
      printf("random number of frames(1~7): %d\n",no_of_frames);

      int no_of_pages = (rand() % 20) + 1;
      int *pages = malloc(no_of_pages * sizeof(int));
      printf("random number of Pages(1~20): %d\n",no_of_pages);
      printf("Reference number(0~9):");
      for (int i = 0;i < no_of_pages; i++){
            pages[i] = rand() % 10;
            printf("%d ",pages[i]);
      }
      printf("\n");

      //Frames initalization
      for(int i = 0; i < no_of_frames; i++)
            frames[i] = -1;

      //FIFO Algorithm
      for (int i = 0;i < no_of_pages;i++){

                  //Frame is not empty,check no duplicated page in frames
                  duplicated = 0;
                  for (int x = 0 ; x < no_of_frames;x++){
                        if(frames[x] == pages[i]){
                              duplicated = 1;
                              break;
                        }
                  }

                  if(!duplicated){
                        frames[pos++ % no_of_frames] = pages[i];
                        pageFaults++;
                  }

      for (int k = 0;k<no_of_frames;k++)
            printf("%d ",frames[k]);
      printf("\n");

      }

printf("Total page fault: %d",pageFaults);
}
