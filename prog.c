#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>


#define NUM_MAX 80
#define DELIMITER " \t\r\n\a"

int arg_index=0;
int back_excute=0;
int should_run = 1;
int ready=0;

char **get_input();
void shell_activate();
void excute();


int main() {
	while(should_run){
	    printf("osh>");
	    char **arg=malloc(NUM_MAX*sizeof(char *));
		arg=get_input();
	 	shell_activate(arg[0]);
		if(ready){
			ready=0;
			excute(arg);
			free(arg);
		}
		arg_index=0;
	 }

	return 0;
} 


char **get_input(){
	char *input=malloc(NUM_MAX*sizeof(char));
	char **arg=malloc(NUM_MAX*sizeof(char *));
	char *pch;
	if (input[0]=='\n'){
	    printf("No Command!\n");
	    exit(1);
	}
	fgets(input,NUM_MAX,stdin);
	pch=strtok(input,DELIMITER);
	while (pch != NULL){
	    arg[arg_index++]=pch;
	    pch=strtok(NULL,DELIMITER);
	}
	return arg;
}



void shell_activate(char *arg){
	if (!strcmp(arg,"exit")){
		should_run=0;
		ready=0;
	}
	else{
		ready = 1;
	}

}


void excute(char **arg){
    pid_t pid = fork();
    if(!strcmp(arg[arg_index-1],"&")){
        back_excute=1;
        arg[arg_index-1]= NULL;
    }
    
    if (pid < 0) {													//Error Process
		fprintf(stderr,"Fork Failed\n");
	}
	else if (pid == 0)												//Child Process
	{
		printf("I am child process,pid=%d\n",getpid());	
		if(!execvp(arg[0],arg) == -1){
			printf("Command Error!\n");
			exit(0);
		}
	}
    else {														//Parent Process
		printf("I am Parent Process=%d\n",getpid());
        if (back_excute){
            wait(NULL);
            back_excute=0;
        }
    }
}
