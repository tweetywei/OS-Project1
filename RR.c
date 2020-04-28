#include <stdio.h>
#include <sys/wait.h>
#include "utils.h"
#include <signal.h>
#include "heap.h"
#include "queue.h"

int process_number;
struct process* process_info;
int is_running = 0;
int next_run = -1;
int finished = 0;
pid_t* child_pid;
int ready_process = 0;
int current_t;
int next_priority_high = -1;
Queue* queue;
int remaining_time = 0;
int* ind_remain_time;
Item* temp_item;




int sort_by_ready_time(const void* p1, const void* p2){
	const struct process* item1 = p1;
	const struct process* item2 = p2;
	return (item1->ready_time - item2->ready_time);
}


void run_next_process(){
	if(next_run >= 0 && remaining_time != 0)
		return;
	if(finished >= process_number)
		return;

	if(next_run >= 0){
		ind_remain_time[next_run] -= 500;
		temp_item -> idx = next_run;
		temp_item -> value = ind_remain_time[next_run];
		//fprintf(stderr, "process %d remain time %d\n", temp_item -> idx, temp_item -> value);
		if(temp_item -> value > 0){
			enqueue(temp_item, queue);
			set_priority(child_pid[next_run], PRIORITY_LOW);
		}

	}	
	
	if(!isEmpty(queue)){
		//fprintf(stderr, "current queue...\n");
		//printQueue(queue);
		temp_item = peek(queue);
		dequeue(queue);
		remaining_time = 500;
		next_run = temp_item -> idx;
		set_priority(child_pid[next_run], PRIORITY_HIGH);
		is_running = 1;
	}

	if(!isEmpty(queue)){
		temp_item = peek(queue);
		set_priority(child_pid[temp_item -> idx], PRIORITY_MIDDLE);
	}
}

void child_handler(int sig){
  pid_t chpid = wait(NULL);
  is_running = 0;
  finished++;
  remaining_time = 0;
  //fprintf(stderr, "one process finished!\n");
  if(finished >= process_number)
	exit(0);
  run_next_process();
}


int main(){

	scanf("%d", &process_number);
	process_info = (struct process*)malloc(process_number * sizeof(struct process));
	ind_remain_time = (int*)malloc(process_number * sizeof(int));
	queue = initial(process_number);
	//fprintf(stderr, "queue, front = %d, rear = %d, capacity = %d\n", queue -> front, queue -> rear, queue -> capacity);
	child_pid = (pid_t*)malloc(process_number * sizeof(pid_t));
	temp_item = (Item*)malloc(sizeof(Item));
	for(int i = 0; i < process_number; i++){
		scanf("%s%d%d", process_info[i].name, &process_info[i].ready_time, &process_info[i].execute_time);
	}
	signal(SIGCHLD, child_handler);

	qsort(process_info, process_number, sizeof(struct process), sort_by_ready_time);
	

	for(current_t = 0; finished < process_number; current_t++){
		int new_process_ready = 0;
		remaining_time -= 1;
		while(ready_process < process_number && process_info[ready_process].ready_time == current_t){
			temp_item -> idx = ready_process;
			temp_item -> value = process_info[ready_process].execute_time;
			ind_remain_time[ready_process] = process_info[ready_process].execute_time;
			enqueue(temp_item, queue);
			execute_process(process_info[ready_process].name, process_info[ready_process].execute_time, &child_pid[ready_process], "NO");
			new_process_ready = 1;
			//fprintf(stderr, "execute child pid = %d\n", child_pid[ready_process]);
			ready_process++;
		}
		run_next_process();
		execute_unit_time();
	}
	return 0;
}
