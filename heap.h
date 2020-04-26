struct heap_node{
	int idx;
	int value;
};
typedef struct heap_node heap_node;

struct heap{
	heap_node* heap_array;
	int element_number;	
	int capacity;
};
typedef struct heap heap;

int parent(int i);
int left(int i);
int right(int i);
void insertKey(heap* target_heap, int idx, int value);
void decreaseKey(heap* target_heap, int idx, int new_value);
heap_node* extractMin(heap* target_heap);
void MinHeapify(heap* target_heap, int i);
void swap(heap_node *x, heap_node *y);