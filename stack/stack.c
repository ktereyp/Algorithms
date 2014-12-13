#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define isEven(NUM) ((NUM & 0x1)? 0:1)

#define TOP 16
int stack[TOP];

int top = 0;


int is_empty()
{
    if(top == 0)
        return 1;
    else
        return -1;
}

int is_top()
{
    if(top == TOP)
        return 1;
    else
        return 0;
}

int push(int item)
{
    if(!is_top()){
        stack[top] = item;
        return ++top;
    }else{
        printf("has reached the top\n");
        return -1;
    }
}

int pop()
{
    if(!is_empty()){
        return --top;            
        
    }else{
        printf("has reached the bottom\n");
        return 0;
    }
}


void print_stack()
{
    int i = 0;
    for(i = 0; i < TOP; i++){
        int n = stack[i];
        if(isEven(n))
            printf("%d: %d    even\n", i, n);
        else
            printf("%d: %d    odd\n", i, n);
    }
}


int main()
{
    int i = 0;
    unsigned int seed = time(NULL);


    for(i = 0; i < TOP; i++){
        push(rand_r(&seed));
    }

    print_stack();

    return 0;
}
