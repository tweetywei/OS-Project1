#include "utils.h"



int main(){
	cpu_set_t set_cpu_mask;
	CPU_ZERO(&set_cpu_mask);
	CPU_SET(0, &set_cpu_mask);
	sched_setaffinity(getpid(), sizeof(cpu_set_t), &set_cpu_mask);
	char schedule_type[10];

	scanf("%s", schedule_type);
	if(strcmp(schedule_type, "FIFO") && strcmp(schedule_type, "RR") && strcmp(schedule_type, "SJF") && strcmp(schedule_type, "PSJF")){
		fprintf(stderr, "invalide scheduler type\n");
		exit(0);
	}
	
	fflush(stdin);

	execl(schedule_type, schedule_type, (char *)0);
	return 0;
}
