#include <stdlib.h>
#include<stdio.h>
#include "heap.h"

int parent(int i) { return (i-1)/2; } 
int left(int i) { return (2*i + 1); } 
int right(int i) { return (2*i + 2); } 
void insertKey(heap* target_heap, int idx, int value) 
{ 
    //fprintf(stderr, "inserting into heap... idx = %d, value = %d\n", idx, value);
    if (target_heap -> element_number >= target_heap -> capacity) 
    { 
        fprintf(stderr, "larger than %d nodes needed!\n", target_heap -> capacity); 
        exit(1); 
    } 
  
    // First insert the new key at the end 
    target_heap -> element_number++; 
    int i = target_heap -> element_number - 1; 
    target_heap -> heap_array[i].idx = idx; 
    target_heap -> heap_array[i].value = value;
  
    // Fix the min heap property if it is violated 
    while (i != 0 && target_heap -> heap_array[parent(i)].value > target_heap -> heap_array[i].value) 
    { 
       swap(&target_heap -> heap_array[i], &target_heap -> heap_array[parent(i)]); 
       i = parent(i); 
    } 
} 

void decreaseKey(heap* target_heap, int idx, int new_value) 
{ 
    int array_index = 0;
    for(int i = 0; i < target_heap -> element_number; i++){
        if(target_heap -> heap_array[i].idx == idx){
            array_index = i;
            break;
        }
    }

    target_heap -> heap_array[array_index].value = new_value; 
    while (array_index != 0 && target_heap -> heap_array[parent(array_index)].value > target_heap -> heap_array[array_index].value) 
    { 
       swap(&target_heap -> heap_array[array_index], &target_heap -> heap_array[parent(array_index)]); 
       array_index = parent(array_index); 
    } 
} 

heap_node* extractMin(heap* target_heap) 
{ 
    if (target_heap -> element_number <= 0){
        fprintf(stderr, "no element in heap!\n");
        exit(1);
    }
    if (target_heap -> element_number == 1) 
    { 
        target_heap -> element_number--; 
        return &target_heap -> heap_array[0]; 
    } 
  
    // Store the minimum value, and remove it from heap
    heap_node* root = (heap_node*)malloc(sizeof(heap_node)); 
    root -> idx = target_heap -> heap_array[0].idx; 
    root -> value = target_heap -> heap_array[0].value;
    target_heap -> heap_array[0].idx = target_heap -> heap_array[target_heap -> element_number-1].idx; 
    target_heap -> heap_array[0].value = target_heap -> heap_array[target_heap -> element_number-1].value; 
    target_heap -> element_number--; 
    MinHeapify(target_heap, 0); 
  
    return root; 
} 

void MinHeapify(heap* target_heap, int i) 
{ 
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < target_heap->element_number && (target_heap -> heap_array[l].value < target_heap -> heap_array[i].value || (target_heap -> heap_array[l].value == target_heap -> heap_array[i].value && target_heap -> heap_array[l].idx < target_heap -> heap_array[i].idx))) 
        smallest = l; 
    if (r < target_heap->element_number && (target_heap -> heap_array[r].value < target_heap -> heap_array[smallest].value || (target_heap -> heap_array[r].value == target_heap -> heap_array[smallest].value && target_heap -> heap_array[r].idx < target_heap -> heap_array[smallest].idx)))  
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&target_heap -> heap_array[i], &target_heap -> heap_array[smallest]); 
        MinHeapify(target_heap, smallest); 
    } 
} 

void swap(heap_node *x, heap_node *y) 
{ 
    heap_node temp;

    temp.idx = x -> idx;
    temp.value = x -> value;
    x -> idx = y -> idx;
    x -> value = y -> value;
    y -> idx = temp.idx;
    y -> value = temp.value;
} 
