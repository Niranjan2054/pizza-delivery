#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include<iostream>
#include<math.h>
#include"pizzadelivery.h"
#include<GL/gl.h>
#include<GL/glu.h>
#include<Gl/glut.h>
using namespace std;
void displaypoints(int x_position,int y_position);
void kmeans();
void cluster();


namespace linkedlist{
    int a = 1;
    pizzadelivery *pfirst=NULL, *pthis, *pnew, *ptemp;
    void getnode(int x, int y)
    {
        pnew = new pizzadelivery(x,y);
        pnew->setcluster(a);
        if(a){
            a=0;
        }else{
            a=1;
        }
        pnew->setnext(NULL);
    }
    void insertfrombeginning(int x, int y)
    {
        getnode(x,y);
        pnew->setnext(pfirst);
        pfirst= pnew;
    }
    void insertfromend(int x, int y)
    {
        if(pfirst==NULL){
            insertfrombeginning(x,y);
        }else{
            pthis = pfirst;
            while(pthis->getnext()!=NULL){
                pthis = pthis->getnext();
            }
            getnode(x,y);
            pthis->setnext(pnew);
        }
    }
    void display()
    {
        pthis = pfirst;
        cout<<endl;
        while(pthis != NULL){
            cout<<"("<<pthis->getx()<<", "<<pthis->gety()<<") -- "<<pthis->getcluster()<<endl;
            pthis = pthis->getnext();
        }
    }
    void displayvertex(){
        pthis = pfirst;
        //glPointSize(10);
        //glColor3f(0,0,0);
        while(pthis != NULL){
            glColor3f(1,1,0);
            glPointSize(10.0);
            glBegin(GL_POINTS);
            glVertex2f(pthis->getx(),pthis->gety());
            glEnd();
            pthis = pthis->getnext();
        }

    }
    void displaypoints(int x_position,int y_position)
    {
        glColor3f(1,0,0);
        glPointSize(20.0);
        glBegin(GL_POINTS);
        glVertex2f(x_position,y_position);
        glEnd();

    }
//calculate distance between two points
    int distances(int x1, int y1, int x2, int y2){
        return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    }

//get centroid of cluster 1 or 0
    void meanCluseter(int cluster,int &x,int &y){
        int x_sum=0, y_sum=0;
        int no_of_data=0;
        pthis = pfirst;
        while(pthis != NULL){
            if(pthis->getcluster()==cluster){
                x_sum += pthis->getx();
                y_sum += pthis->gety();
                no_of_data++;
            }
            pthis = pthis->getnext();
        }
        x = x_sum/no_of_data;
        y = y_sum/no_of_data;
    }

//cluster the given data points
    void clusterthedatapoints(){
        int dist_cluster_one, dist_cluster_zero;
        int cluster_one_x,cluster_one_y,cluster_zero_x,cluster_zero_y;
        meanCluseter(1,cluster_one_x,cluster_one_y);
        meanCluseter(0,cluster_zero_x,cluster_zero_y);
        pthis=pfirst;
        while(pthis != NULL){
            dist_cluster_one = distances(pthis->getx(),pthis->gety(),cluster_one_x,cluster_one_y);
            dist_cluster_zero = distances(pthis->getx(),pthis->gety(),cluster_zero_x,cluster_zero_y);
            if(dist_cluster_one>dist_cluster_zero){
                pthis->setcluster(0);
                cout<<"("<<pthis->getx()<<", "<<pthis->gety()<<")"<<"--"<<pthis->getcluster()<<"\n";
            }else{
                pthis->setcluster(1);
                cout<<"("<<pthis->getx()<<", "<<pthis->gety()<<")"<<"--"<<pthis->getcluster()<<endl;
            }
            pthis = pthis->getnext();
        }
    }

    void kmeans(int &x1, int &y1, int &x0, int &y0)
    {
        int i=1;
        int x_position_one,y_position_one,x_new_position_one,y_new_position_one;
        int x_position_two,y_position_two,x_new_position_two,y_new_position_two;
        meanCluseter(1,x_position_one,y_position_one);
        meanCluseter(0,x_position_two,y_position_two);
        while(i<10){
            clusterthedatapoints();
            meanCluseter(1,x_new_position_one,y_new_position_one);
            meanCluseter(0,x_new_position_two,y_new_position_two);
            if(abs(x_new_position_one-x_position_one)<1 && abs(y_new_position_one-y_position_one)<1 && abs(x_new_position_two-x_position_two)<1 && abs(y_new_position_two-y_position_two)<1){
                x1 = x_position_one;
                y1 = y_position_one;
                x0 = x_position_two;
                y0 = y_position_two;
                break;
            }else{
                x_position_one = x_new_position_one;
                y_position_one = y_new_position_one;
                x_position_two = x_new_position_two;
                y_position_two = y_new_position_two;
            }
            i++;
        }
    }
}
#endif // LINKEDLIST_H_INCLUDED
