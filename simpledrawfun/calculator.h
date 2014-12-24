#ifndef CALCULATOR_H
#define CALCULATOR_H

typedef struct oneitem{
    char operate;
    char *number;
    struct oneitem *left;
    struct oneitem *right;
    struct oneitem *parent;
}oneitem;
typedef struct oneitem equalist;


double calculate(oneitem *equal, double x);
equalist *createlist(char *equal);

void freelist(oneitem *);

void printlist(oneitem *);

int ishigh(char first, char second);

oneitem * getsuitposition(char operate, oneitem * list);

oneitem * create_oneitem();

double string2float(char *s);

int isoperator(char);

char * getsubstring(const char * s, int start, int end);
oneitem * gettop(oneitem *);

#endif //CALCULATOR_H
