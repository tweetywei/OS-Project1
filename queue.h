struct Item{
	int idx;
	int value;
};
typedef struct Item Item;

struct Queue{
	int size;
	int capacity;
	int front;
	int rear;
	Item *array;
};
typedef struct Queue Queue;

Item* peek(Queue* Q);
int isFull(Queue* Q);
int isEmpty(Queue* Q);
Queue* initial(int max_element);
void enqueue(Item* item,Queue* Q);
void dequeue(Queue* Q);
void printQueue(Queue* Q);


