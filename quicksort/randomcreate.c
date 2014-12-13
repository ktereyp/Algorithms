#include "randomcreate.h"

void create_random_array(long array[], int lenght)
{
    int i;
    for(i = 0; i < lenght; i++)
    {
        array[i] = random();
    }
}


void print_array(long array[], int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("%ld\n", array[i]);
    }
}
