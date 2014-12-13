#include <stdio.h>
#include <stdlib.h>
#include "randomcreate.h"


int partition(long array[], int begin, int end)
{
    int std = end;
    int i;
    int q = begin -1;
    for(i = begin; i < end; i++)
    {
        if(array[i] < array[std]){
            q++;
            long tmp = array[q];
            array[q] = array[i];
            array[i] = tmp;
        }
    }

    q++;
    long tmp = array[q];
    array[q] = array[end];
    array[end] = tmp;

    return q;
}

void quicksort(long array[], int begin, int end)
{
    if(begin < end)
    {
        int sep = partition(array, begin, end);
        quicksort(array, begin, sep-1);
        quicksort(array, sep+1, end);
    }
}

void check(long array[], int length)
{
    int i;
    for(i = 0; i < length - 1; i++)
    {
        if(array[i] > array[i+1]){
            abort();
        }
    }
}


#define LENGTH 2000

int main()
{

    long array[LENGTH];  
    create_random_array(array, LENGTH); 

    quicksort(array, 0, LENGTH);



    print_array(array, LENGTH);

    return 0;
}
