#include <stdio.h>
#include <sys/wait.h>
#include "utils.h"
#include <stdlib.h>
#include <signal.h>

int process_number;
struct process* process_info;
int is_running = 0;
int next_run = 0;
pid_t* child_pid;
int ready_process = 0;

void child_handler(int sig){
  pid_t chpid = wait(NULL);
  is_running = 0;
  next_run++;
}


int sort_by_ready_time(const void* p1, const void* p2){
	const struct process* item1 = p1;
	const struct process* item2 = p2;
	return (item1->ready_time - item2->ready_time);
}

void run_next_process(){
	if(!is_running && next_run < process_number && next_run < ready_process){
		set_priority(child_pid[next_run], PRIORITY_HIGH);
		is_running = 1;
	}
}

int main(){

	scanf("%d", &process_number);
	process_info = (struct process*)malloc(process_number * sizeof(struct process));
	child_pid = (pid_t*)malloc(process_number * sizeof(pid_t));
	for(int i = 0; i < process_number; i++){
		scanf("%s%d%d", process_info[i].name, &process_info[i].ready_time, &process_info[i].execute_time);
	}
	signal(SIGCHLD, child_handler);
	
	qsort(process_info, process_number, sizeof(struct process), sort_by_ready_time);
	

	for(int time = 0; next_run < process_number; time++){
		while(ready_process < process_number && process_info[ready_process].ready_time == time){
			execute_process(process_info[ready_process].name, process_info[ready_process].execute_time, &child_pid[ready_process]);
			fprintf(stderr, "execute child pid = %d\n", child_pid[ready_process]);
			ready_process++;
		}
		run_next_process();
		execute_unit_time();
	}
	for(int i = 0; i < process_number; i++){
		printf("%s %d\n", process_info[i].name, (int)child_pid[i]);
	}
	return 0;
}
