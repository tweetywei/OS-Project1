#include"queue.h"

#include<stdio.h>
#include<stdlib.h>

int isFull(Queue* Q){
	return Q->size==Q->capacity;
}

int isEmpty(Queue* Q){
	return Q->size==0;
}

Item* peek(Queue* Q){
	if(isEmpty(Q)){
		fprintf(stderr, "Queue is empty!!\n");
		return NULL;
	}
	Item* return_item = (Item*)malloc(sizeof(Item));
	return_item -> idx = Q -> array[Q->front].idx;
	return_item -> value = Q -> array[Q->front].value;
	return return_item;
}

Queue* initial(int max_element){
	
	Queue* Q;
	Q = (Queue*)malloc(sizeof(Queue));
	if(Q == NULL){
		fprintf(stderr, "Queue malloc error\n");
		exit(1);
	}
	Q->size = 0;
	Q->capacity = max_element;
	Q->front = 1;
	Q->rear = 0;
	Q->array = (Item*)malloc(sizeof(Item) * (Q->capacity));
	
	if(Q->array==NULL){
		fprintf(stderr, "Queue array arrange fail\n");
		free(Q);
		exit(1);
	}
	return Q;
}


void enqueue(Item* item,Queue* Q){
	if(!isFull(Q)){
		if((Q->rear)+1 == Q->capacity)
		   Q->rear=-1; 
		Q->rear++;
		Q->array[(Q->rear)].idx = item -> idx;
		Q->array[(Q->rear)].value = item -> value;
		Q->size++;
	}
}

void dequeue(Queue* Q){
	if(!isEmpty(Q)){
		if(Q->front+1==Q->capacity)
		   Q->front=-1; 
		Q->size--;
		Q->front++;
		
	}
}

void printQueue(Queue* Q){
	int i=Q->front;
	while(i!=Q->rear){
		fprintf(stderr, "%d\t",Q->array[i].idx);
		if(i+1==Q->capacity)
		  i=-1;
		i++;
	}
	fprintf(stderr, "%d\t",Q->array[i].idx);
}
