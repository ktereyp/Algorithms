#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calculator.h"



double calculate(oneitem *equal, double x)
{
    oneitem *p = equal;
    if(p == NULL){
        return 0;
    }    

    if( p->left && p->right ){
        double result_left = calculate(p->left, x);
        double result_right = calculate(p->right, x);
        switch(p->operate){
            case '^':
                return pow(result_left, result_right);
            case '*':
                return result_left * result_right;
            case '/':
                return result_left / result_right;
            case '+':
                return result_left + result_right;
            case '-':
                return result_left - result_right;
            default:
                abort();
        }
    }else{
        double d;
        if(strncmp(p->number, "x", 1) == 0){
            d  = x;
        }else{
            d = string2float(p->number);
        }
        //printf("%s -> %lf\n", p->number, d);
        return d;
    }
}

equalist *createlist(char *equa)
{
    if(equa == NULL || strlen(equa) == 0){
        return NULL;
    }

    oneitem *entry = create_oneitem();

    char *c = equa;
    int start, end;
    start = end = 0;
    int hasinner = 0;
    while(*c != '\0'){
        if(*c == '('){
            hasinner = 1;
            int n = 1;
            c++;
            end++;
            while(*c != '\0'){
                if(*c == '(')
                    n++;
                if(*c == ')')
                    n--;
                c++;
                end++;
                if(n == 0)
                    break;
            }
        } 

        if(hasinner && *c == '\0')
            break;

        if(isoperator(*c)){
            if (*c != '-' && end == 0){
                return NULL;
            }
            char *num;
            if(hasinner){
                num = getsubstring(equa, start+1, end -2);
            }else{
                num = getsubstring(equa, start, end -1);
            }
            oneitem *p = getsuitposition(*c, entry);
            if(p == entry){
                entry->operate = *c;
                if(hasinner){
                    oneitem *inner = createlist(num); 
                    entry->left = inner; 
                    entry->left->parent = entry;
                    hasinner = 0;
                    free(num);
                }else{
                    entry->left = create_oneitem();
                    entry->left->parent = entry;
                    entry->left->number = num;
                }
                entry->right = create_oneitem();
                entry->right->parent = entry;
                entry = entry->right;
            }else{
                //entry->number = num; 
                oneitem *entryold = entry;
                if(hasinner){
                    oneitem *inner = createlist(num); 
                    entry = entry->parent;
                    entry->right = inner; 
                    entry->right->parent = entry;
                    hasinner = 0;
                    free(num);
                    entry = entryold;
                }else{
                    //entry->left = create_oneitem();
                    //entry->left->number = num;
                    entry->number = num; 
                    entry = create_oneitem();
                }
                if(p->parent != NULL){
                    //p->parent->right = entry;
                    entry->parent = p->parent;
                    entry->parent->right = entry;
                }else{
                    entry->parent = NULL;
                }
                entry->operate = *c;
                entry->left = p;
                entry->left->parent = entry;
                entry->right = create_oneitem();
                entry->right->parent = entry;
                entry = entry->right;
            }
            start = end+1;
            end++;
            c++;
            continue;
        }else{
            end++;
            c++;
            continue;
        }

    }

    if(start != end){
        if(hasinner){
            char *num = getsubstring(equa, start+1, end -2);
            oneitem *inner = createlist(num); 
            oneitem *entryold = entry;
            entry = entry->parent;
            entry->right = inner; 
            entry->right->parent = entry;
            hasinner = 0;
            free(num);
            free(entryold);
        }else{
            char *num = getsubstring(equa, start, end -1);
            entry->number = num; 
        }
    }

    return gettop(entry); 
}

oneitem * create_oneitem()
{
    oneitem *o = malloc(sizeof (struct oneitem));
    o->number = '\0';
    o->operate = '\0';
    o->parent = NULL;
    o->left = NULL;
    o->right = NULL;
    return o;
}

void freelist(oneitem *list)
{
    if(list == NULL)
        return;

    oneitem *p = list;
    if(p->left != NULL && p->right != NULL){
        freelist(p->left);
        freelist(p->right);
        free(p);
    }else{
        free(p->number);
        free(p);
    }

}

void printlist(oneitem *list)
{
    if(list == NULL)
        return;

    oneitem *p = list;
    if(p->left != NULL && p->right != NULL){
        printlist(p->left);
        printf("%c", p->operate);
        printlist(p->right);
    }else{
        printf("%s", p->number);
    }
}

int ishigh(char first, char second)
{
    if(first == '^'){
        if(second == '^')
            return 0;
        else
            return 1;
    }
    if(first == '*' || first == '/'){
        if(second != '^' && second != '*' && second != '/')
            return 1;
        else
            return 0;
    }
    return 0;
}

oneitem * getsuitposition(char operate, oneitem * list)
{
    oneitem *p = list;
    if(p->parent == NULL){
        return p;
    }
    while((p = p->parent) != NULL){
        if(ishigh(p->operate, operate)){
            if(p->parent == NULL)
                return p;
            continue; 
        }else{
            return p->right;
        }
    }
    return NULL;
}

double string2float(char *s)
{
    double f;
    sscanf(s, "%lf", &f);
    return f;    
}

int isoperator(char c)
{
    if(c != '^' && c != '*' && c != '/' && c != '+'  && c != '-')
        return 0;
    else
        return 1;
}

char * getsubstring(const char * s, int start, int end)
{
    int n = end - start + 1;
    char *buff = malloc(sizeof(char) * (n +1));
    strncpy(buff, s+start, n);
    buff[n] = '\0';
    return buff;
}

oneitem * gettop(oneitem *list)
{
    if(list == NULL){
        return NULL;
    }
    oneitem *p = list;    
    while((p->parent) != NULL)
        p = p->parent;
    return p;
}
/*
int main(int argc, char **argv)
{
    char *s = "1+x*(3+4)+5";
    oneitem *l = createlist(s);
    printlist(l);
    
    printf("\n");

    double result = calculate(l, 3);
    printf("%s = %lf\n", s, result);

    freelist(l);


    return 0;
}
*/
