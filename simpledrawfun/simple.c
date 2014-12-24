#include <GL/glut.h>
#include <math.h>
#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>

float *x;
float *y;
int lenght;

oneitem *list;

void genarate(char *equal, double xmin, double xmax, int lenght)
{
    int i;
    float xx = xmin;
    float step = (xmax-xmin)/lenght;
    x = malloc(sizeof(float) * lenght);
    y = malloc(sizeof(float) * lenght);
    list = createlist(equal);
    for(i = 0; i < lenght; i++){
        xx = -1 + i * step;
        x[i] = xx;
        y[i] = calculate(list, xx);
    }
    freelist(list);
}

void create_car(float x[], float y[], int lenght)
{
    float xmin = x[0], xmax = x[0];
    float ymin = y[0], ymax = y[0];

    int i;
    for(i = 0; i < lenght; i++){
        if(x[i] < xmin){
            xmin = x[i];
        } 
        if(x[i] > xmax){
            xmax = x[i];
        } 
        if(y[i] < ymin){
            ymin = y[i];
        } 
        if(y[i] > ymax){
            ymax = y[i];
        } 
    }
    

    //x
    glBegin(GL_LINE_STRIP);
    glVertex2f(xmin, 0);
    glVertex2f(xmax, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(xmax, 0);
    glVertex2f(xmax - (xmax - xmin)/20, (xmax-xmin)/20);
    glVertex2f(xmax, 0);
    glVertex2f(xmax - (xmax - xmin)/20, -(xmax-xmin)/20);
    glEnd();

    //y
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, ymin);
    glVertex2f(0, ymax);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0, ymax);
    glVertex2f((xmax - xmin)/20, ymax - (xmax-xmin)/20);
    glVertex2f(0, ymax);
    glVertex2f(-(xmax - xmin)/20, ymax - (xmax-xmin)/20);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    create_car(x, y, lenght);

    glBegin(GL_LINE_STRIP);
    int i;
    for(i = 0; i < 200; i++){
        glVertex2f(x[i], y[i]);
    }
    glEnd();

    glFlush();
}

void init()
{
    glClearColor(0, 0, 0, 0);

    glColor3f(1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float xmin = x[0], xmax = x[0];
    float ymin = y[0], ymax = y[0];

    int i;
    for(i = 0; i < lenght; i++){
        if(x[i] < xmin){
            xmin = x[i];
        } 
        if(x[i] > xmax){
            xmax = x[i];
        } 
        if(y[i] < ymin){
            ymin = y[i];
        } 
        if(y[i] > ymax){
            ymax = y[i];
        } 
    }
    float frex = (xmax - xmin)/10;
    float frey = (ymax - ymin)/10;
    gluOrtho2D(xmin - frex, xmax + frex, ymin-frey, ymax + frey);
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Simple");

    char *s = *(argv+1);
    printf("equalation -> %s  ,", s);
    double  xmin = string2float(*(argv+2));
    double  xmax = string2float(*(argv+3));
    printf("(xmin, xmax) -> (%lf, %lf)\n", xmin, xmax);
    genarate(s, xmin, xmax, 200);
    lenght = 200;

    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
