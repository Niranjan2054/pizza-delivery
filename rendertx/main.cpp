#include<GL/gl.h>
#include<GL/glu.h>
#include<Gl/glut.h>
#include<iostream>
#include<strings.h>
#include"pizzadelivery.h"
#include"linkedlist.h"
using namespace std;

void display();
void init();
void reshape(int, int);
void timer(int);
void mouse(int,int,int,int);
void displaytext(unsigned char str[],int x, int y);
int strlen(unsigned char str[]);
void displayquads(int,int,int,int);
void displaypoints(int,int);
int main(int argc, char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("Pizza Delivery Center Location For Efficient Pizza Delivery");
    glutDisplayFunc(display);
    glutTimerFunc(0,timer,0);
    glutReshapeFunc(reshape);
    init();

    glutMainLoop();
}
float x_position =0;
float y_position =0;
float height = 200;
float width = 200;


int x_position_one=200,y_position_one=200, x_position_zero=300, y_position_zero=300;

bool clicked = false;
void display()
{
    unsigned char str[] = "Pizza Delivery Center Location For Efficient Pizza Delivery";
    unsigned char submit[] ="Submit";
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //view
    glColor3f(1,1,1);
    glColor3f(.8,.8,.8);
    displayquads(0,0,600,50);
    glColor3f(0,0,0);
    displaytext(str,10,-30);
    glColor3f(1,1,0);
    linkedlist::displayvertex();
    glColor3f(0.298039,.686275,0.313725);
    displayquads(500,-560,100,40);
    glColor3f(0,0,0);
    displaytext(submit,515,-585);

    if(clicked){
        cout<<"Displayed"<<endl;
        glColor3f(1,0,0);
        glPointSize(20.0);
        cout<<"( "<<x_position_one<<", "<<y_position_one<<")"<<endl;
        cout<<"( "<<x_position_zero<<", "<<y_position_zero<<")"<<endl;
        glBegin(GL_POINTS);
        glVertex2f(x_position_one,y_position_one);
        glEnd();
        glBegin(GL_POINTS);
        glVertex2f(x_position_zero,y_position_zero);
        glEnd();
        clicked = false;
    }
    glutSwapBuffers();
}
void init()
{
    glClearColor(0.1f,.1f,1.0f,.5f);
}
void reshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,600,-600,0);
    glMatrixMode(GL_MODELVIEW);
}
void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
    glutMouseFunc(mouse);
}
void mouse(int button, int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(x>500 && y>560){
            cout<<"Clicked";
            linkedlist::kmeans(x_position_one,y_position_one,x_position_zero,y_position_zero);
            clicked = true;
        }else if(y>60){
            linkedlist::insertfromend(x,-y);
            linkedlist::display();

        }

    }
}
void displaytext(unsigned char str[],int x, int y)
{
    glRasterPos2f(x,y);
    int len = strlen(str);
    for(int i = 0;i<len;i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
    }
}
int strlen(unsigned char str[])
{
    int i=0;
    while(str[i]!='\0'){
        i++;
    }
    return i;
}

void displayquads(int x_position,int y_position,int width,int height)
{
    glBegin(GL_QUADS);
    glVertex2f(x_position,y_position);
    glVertex2f(x_position,y_position-height);
    glVertex2f(x_position+width,y_position-height);
    glVertex2f(x_position+width,y_position);
    glEnd();

}



