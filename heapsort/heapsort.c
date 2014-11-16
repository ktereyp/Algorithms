#include <stdio.h>
#include <stdlib.h>

int get_parent(int child_id){
    return child_id/2;
}

int left_child(int parent){
    return (2*parent);
}

int right_child(int parent){
    return (2*parent + 1);
}

void max_heapify(int array[], int array_size, int i){
    int left = left_child(i);
    int right = right_child(i);
    int largest = i;

    if(left <= array_size && array[left] > array[largest]){
        largest = left;
    }
    if(right <= array_size && array[right] > array[largest]){
        largest = right;
    }
    if(largest != i){
        int tmp = array[i];
        array[i] = array[largest];
        array[largest] = tmp;
        max_heapify(array, array_size, largest);
    }
}

void build_max_heap(int array[], int array_size){
    int i; 
    for(i = array_size/2; i >= 1; i--){
        max_heapify(array, array_size, i);
    }
}

void heapsort(int array[], int array_size){
    build_max_heap(array, array_size);
    int i;
    for(i = array_size; i >= 2; i--){
        int tmp = array[1];
        array[1] = array[i];
        array[i] = tmp;
        max_heapify(array, i-1, 1);
    }
}

int main(){
    int array[11] = { 0, 3, 5, 2, 1, 8, 10, 9, 7 , 20, 13};
    int i = 0;
    for(i = 0; i < 11; i++)
        printf("%d - ", array[i]);
    printf("\n");

    heapsort(array, 10);

    i = 0;
    for(i = 0; i < 11; i++)
        printf("%d - ", array[i]);
    printf("\n");

    return 0;
}

