#include <stdio.h>
#include <sys/wait.h>
#include "utils.h"
#include <signal.h>
#include "heap.h"

int process_number;
struct process* process_info;
int is_running = 0;
int next_run = 0;
int finished = 0;
pid_t* child_pid;
int ready_process = 0;
heap SJF_heap;
heap_node* heap_array_head;
int current_t;
int next_priority_high = -1;
int remaining_time;
int second_priority = -1;

void child_will_end(){
	//fprintf(stderr, "receive child signal from %d\n", next_run);
	int finished_id = next_run;
	int expected_t = process_info[finished_id].ready_time + process_info[finished_id].execute_time;
	while(ready_process < process_number && process_info[ready_process].ready_time < expected_t){
		insertKey(&SJF_heap, ready_process, process_info[ready_process].execute_time);
		execute_process(process_info[ready_process].name, process_info[ready_process].execute_time, &child_pid[ready_process], "YES");
		ready_process++;
	}
	kill(child_pid[next_run], SIGUSR2);
}

void register_sigusr1(){
	struct sigaction act;
	act.sa_flags = 0;
	act.sa_handler = child_will_end;
	sigfillset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
}

void child_handler(int sig){
  pid_t chpid = wait(NULL);
  is_running = 0;
  finished++;
  /*int finished_id = next_run;
  if(child_pid[finished_id] != chpid){
	for(finished_id = 0; finished_id < process_number; finished_id++){
		if(child_pid[finished_id] == chpid) break;
	}
  }*/

  //fprintf(stderr, "one process finished!\n");
  if(finished >= process_number)
	exit(0);
  /*int expected_t = process_info[finished_id].ready_time + process_info[finished_id].execute_time;
  while(ready_process < process_number && process_info[ready_process].ready_time < expected_t){
	insertKey(&SJF_heap, ready_process, process_info[ready_process].execute_time);
	execute_process(process_info[ready_process].name, process_info[ready_process].execute_time, &child_pid[ready_process]);
	ready_process++;
  }*/

}


int sort_by_ready_time(const void* p1, const void* p2){
	const struct process* item1 = p1;
	const struct process* item2 = p2;
	return (item1->ready_time - item2->ready_time);
}

void check_increase_priority(){
  if(SJF_heap.element_number > 0 && is_running){
	/*
	if(temp_next_run != next_priority_high){
		if(next_priority_high >= 0 && next_priority_high != next_run){
			set_priority(child_pid[next_priority_high], PRIORITY_LOW);
			fprintf(stderr, "set idx = %d to PRIORITY_LOW\n", next_priority_high);
		}
	        set_priority(child_pid[temp_next_run], PRIORITY_MIDDLE);  
		fprintf(stderr, "set idx = %d to PRIORITY_MIDDLE\n", temp_next_run);
		next_priority_high = temp_next_run;
	}*/
	int min_execute_time = SJF_heap.heap_array[0].value;
	int min_idx = SJF_heap.heap_array[0].idx;
	if(min_execute_time < remaining_time){
		//preemptive!
		extractMin(&SJF_heap);
		insertKey(&SJF_heap, next_run, remaining_time);
		set_priority(child_pid[next_run], PRIORITY_LOW); 
		next_run = min_idx;
		set_priority(child_pid[next_run], PRIORITY_HIGH); 
		remaining_time = min_execute_time;
	}
	int second_execute_time = SJF_heap.heap_array[0].value;
	int second_idx = SJF_heap.heap_array[0].idx;
	if(second_idx != second_priority){
		if(second_priority >= 0 && second_priority != next_run)
			set_priority(child_pid[second_priority], PRIORITY_LOW);
		set_priority(child_pid[second_idx], PRIORITY_MIDDLE);		
		second_priority = second_idx;
	}
  }
}

void run_next_process(){
	if(finished >= process_number || is_running)
		return;
	heap_node* smallest = extractMin(&SJF_heap);
	next_run =  smallest -> idx;
	//fprintf(stderr, "setting next process priority high, idx = %d\n", next_run);
	set_priority(child_pid[next_run], PRIORITY_HIGH); 
	remaining_time =  smallest -> value;
	is_running = 1;
	check_increase_priority();
}



int main(){

	scanf("%d", &process_number);
	process_info = (struct process*)malloc(process_number * sizeof(struct process));
	heap_array_head = (heap_node*)malloc(process_number * sizeof(heap_node));
	SJF_heap.heap_array = heap_array_head;
	SJF_heap.element_number = 0;
	SJF_heap.capacity = process_number;
	child_pid = (pid_t*)malloc(process_number * sizeof(pid_t));
	register_sigusr1();
	for(int i = 0; i < process_number; i++){
		scanf("%s%d%d", process_info[i].name, &process_info[i].ready_time, &process_info[i].execute_time);
	}
	signal(SIGCHLD, child_handler);

	qsort(process_info, process_number, sizeof(struct process), sort_by_ready_time);
	

	for(current_t = 0; finished < process_number; current_t++){
		if(is_running && remaining_time > 0)
			remaining_time--;
		int new_process_ready = 0;
		while(ready_process < process_number && process_info[ready_process].ready_time == current_t){
			insertKey(&SJF_heap, ready_process, process_info[ready_process].execute_time);
			execute_process(process_info[ready_process].name, process_info[ready_process].execute_time, &child_pid[ready_process], "YES");
			new_process_ready = 1;
			//fprintf(stderr, "execute child pid = %d\n", child_pid[ready_process]);
			ready_process++;
		}
		if(new_process_ready) check_increase_priority();
		if(SJF_heap.element_number > 0)
			run_next_process();
		execute_unit_time();
	}
	return 0;
}
