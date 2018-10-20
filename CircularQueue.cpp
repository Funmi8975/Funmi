// CIRCULARQUEUE.h

#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H
#include<iostream>
using namespace std;
class CircularQueue
{
 int front, back, max;
 double *cqueue;
 public:
 CircularQueue(int);
 bool empty();
 bool full();
 void enqueue(double);
 double dequeue();
 double get_first();
 double get_last();
};
#endif

// CIRCULARQUEUE.cpp

#include"CircularQueue.h"
CircularQueue::CircularQueue(int mx):front(-1),back(-1),max(mx),cqueue(new double[max])
{
}
bool CircularQueue::empty()
{
 return (front==-1
 system("exit");
 }
}
double CircularQueue::get_last()
{
 if(!empty())
 return cqueue[back];
 else
 {
 cout<<"ERROR: Queue is empty."<<endl;
 system("exit");
 }
}
void CircularQueue::enqueue(double item)
{
 if(full())
 {
 cout<<"ERROR: Circular Queue Overflow."<<endl;
 system("exit");
 }//if full

 else if(empty())
 {
 front=0;
 back=0;
 }
 else
 back=(back+1)%max;

 cqueue[back]=item;
 return;
}
double CircularQueue::dequeue()
{
 //local var
 double i;
 //code
 if(empty())
 {
 cout<<"ERROR: Circular Queue is Empty."<<endl;
 system("exit");
 }
 
 else if(front==back)
 {
 i=cqueue[front];
 front=-1;
 back=-1;
 }
 else
 {
 i=cqueue[front];
 front=(front+1)%max;
 }

 return i;
}

//main.cpp

#include"CircularQueue.h"
//gv
//function Declaration
void display(CircularQueue);
int main()
{
//local var
CircularQueue cqueue(3);
double item;
//code
for(int i=0;i<3;i++)
{
cout<<"Enter item" <<i+1<<endl;
cin>>item;
cqueue.enqueue(item);
}//for i
//display
display(cqueue);
return 0;
}//main
//function definition
void display(CircularQueue cq)
{
 cout<<"The Sorted Items are: ";
 while(!cq.empty())
 {
 cout<<cq.get_first()<<" ";
 cq.dequeue();
 }//while
}//display
