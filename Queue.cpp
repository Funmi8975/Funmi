
//Queue.h

#ifndef QUEUE_H
#define QUEUE_H
#include<iostream>
using namespace std;
class Queue
{
int size, front, back;
int* queue;
public:
Queue();
Queue(int)

Queue::Queue():size(15), front(-1), back(-1), queue(new int[size])
{
}
Queue::Queue(int size)
{
this->size=size;
this->front=-1;
this->back=-1;
this->queue=new int[size];
}
bool Queue::empty()
{
return (back==-1 && front==-1);
}
bool Queue::full()
{
return (back==size-1);
}
void Queue::enqueue(int data)
{
if(empty())
{
front++;
back++;
queue[back]=data;
}
else if(full())
{
cout<<"Queue is Full"<<endl;
system("exit");
}
else
{
back++;
queue[back]=data;
}
return;
}
int Queue::dequeue()
{
int i;
if(empty()){
cout<<"Cano not dequeue, the queue is empty."<<endl;
system("exit");
}
else if(front==back)
{
i=queue[front];
front=-1;
back=-1;
}
else{
i=queue[front];
front++;
}
return i;
}

//QueueMain.cpp
#include"Queue.h"
const int SIZE=5;
int main()
{
//local var
Queue queue(SIZE);
int data;
//code
//queue.enqueue(10);
while(!queue.full())
{
cout<<"Enter an integer data to enqueue: ";
cin>>data;
queue.enqueue(data);
}
while(!queue.empty())
{
cout<<queue.dequeue()<<endl;
}
return 0;
}
