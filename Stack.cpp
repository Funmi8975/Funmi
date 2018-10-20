// Stack.h

#ifndef STACK_H
#define STACK_H
#include<iostream>
using namespace std;
class Stack
{
public:
Stack();
Stack(int);
void push(int);
int pop();
bool empty();
bool full();
void print();

// Stack.cpp
#include"Stack.h"
Stack::Stack():top(-1), max_stack(5), stack(new int[5])
{
}
Stack::Stack(int max): max_stack(max),top(-1)
{
stack=new int[max_stack];
}
bool Stack::full()
{
return (top==max_stack-1);
}
void Stack::push(int data)
{
 if(!full())
 {
 top++;
 stack[top]=data;
 }
 else
 {
 cout<<"The Stack is Full!\n";
 system("exit");
 }
return;
}
bool Stack::empty()
{
return (top==-1);
}
int Stack::pop()
{
int get_data;
if(!empty())
{
get_data=stack[top];
top--;
}
else
{
cout<<"The Stack is Empty!\n";
 system("exit");
}
return get_data;
}
void Stack::print()
{
cout<<"The Current State of the stack is:\n";
for(int i=top;i>=0;i--)
{
cout<<"Item "<<stack[i]<<endl;
}
}

// main.cpp
#include"Stack.h"
int main()
{
//Local var
Stack stack(5);
int data;
//Code
stack.push(100);
cout<<"Enter data to push in the top of the stack: ";
cin>>data;
stack.push(data);
stack.print();
stack.pop();
stack.print();
stack.pop();
stack.print();
stack.pop();
return 0;
}
