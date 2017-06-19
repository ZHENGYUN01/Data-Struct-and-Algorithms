// sqQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

#define MAXQSIZE 4//max size of queue.

using namespace std;

typedef struct record{
	string courseNum;
	string studentName;
	float Chinese;
	float Math;
	float English;
}record;

typedef record qElemType;
typedef int Status;

ostream& operator <<(ostream& output, qElemType &elem){
	output<<"courseNum:"<<elem.courseNum<<' ';
	output<<"studentName:"<<elem.studentName<<' ';
	output<<"Chinese:"<<elem.Chinese<<' ';
	output<<"Math:"<<elem.Math<<' ';
	output<<"English:"<<elem.English<<' '<<endl;
	return output;
}

istream& operator >>(istream& input, qElemType &elem){
	input>>elem.courseNum>>elem.studentName>>elem.Chinese>>elem.Math>>elem.English;
	return input;
}

typedef struct sqQueue{
	qElemType *base;
	int front;
	int rear;
}sqQueue;

Status initQueue(sqQueue &Q){
	Q.base = new qElemType [MAXQSIZE * sizeof(qElemType)];
	if(!Q.base) exit(-1);
	Q.front = Q.rear = 0;
	return 1;
}

int getQueueLength(sqQueue &Q){
	return (Q.rear - Q.front + MAXQSIZE)%MAXQSIZE;
}

Status isFull(sqQueue &Q){
	//leave a empty space to judge if the queue is full.
	if((Q.rear + 1)%MAXQSIZE == Q.front)
		return 1;
	else 
		return 0;
}

Status isEmpty(sqQueue &Q){
	if(Q.front == Q.rear)
		return 1;
	else
		return 0;
}

Status enQueue(sqQueue &Q, qElemType e){
	if(isFull(Q)) return -1;//full.
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1)%MAXQSIZE;
	return 1;
}

Status deQueue(sqQueue &Q, qElemType &e){
	if(isEmpty(Q)) return -1;//empty.
	e = Q.base[Q.front];
	Q.front = (Q.front + 1)%MAXQSIZE;
	return 1;
}

Status clearQueue(sqQueue &Q){
	qElemType temp;
	while(!isEmpty(Q)){
		deQueue(Q,temp);
	}
	return 1;
}

Status destroyQueue(sqQueue &Q){
	clearQueue(Q);
	delete []Q.base;
	return 1;
}

Status printQueue(sqQueue &Q){
	if(isEmpty(Q)) return -1;
	int length = getQueueLength(Q);
	int cur = Q.front;

	for(int i = 0;i < length; i++){
		cout<<Q.base[cur]<<endl;
		cur = (cur + 1)%MAXQSIZE;
	}
	return 1;
}
int _tmain(int argc, _TCHAR* argv[])
{
	sqQueue Q;
	initQueue(Q);

	cout<<"Try to insert elements into queue..."<<endl;
	qElemType insert_one[4] = {{"2017", "zhangsan", 100, 100, 100}, {"2017", "lisi", 99, 99, 99},{"2017", "wangwu", 98, 98, 98},{"2017", "zhaoliu", 97, 97, 97}};
	for(int i = 0; i<4; i++){
		//queue can hold MAXQSIZE-1 elements.
		enQueue(Q, insert_one[i]);
	}

	printQueue(Q);

	cout<<"Try to judge if the queue is full:"<<endl;
	if(isFull(Q))
		cout<<"IsFull"<<endl;
	else
		cout<<"NotFull"<<endl;

	cout<<"Try to judge if the queue is empty:"<<endl;
	if(isEmpty(Q))
		cout<<"IsEmpty"<<endl;
	else
		cout<<"NotEmpty"<<endl;

	cout<<"Try to delete the head element of queue"<<endl;
	qElemType delete_one;
	deQueue(Q, delete_one);
	cout<<delete_one<<endl;
	cout<<"The queue after deletation:"<<endl;
	printQueue(Q);

	cout<<"Try to clear the queue..."<<endl;
	clearQueue(Q);
	cout<<"queue is cleared!"<<endl;
	cout<<"Try to judge if the queue is empty:"<<endl;
	if(isEmpty(Q))
		cout<<"IsEmpty"<<endl;
	else
		cout<<"NotEmpty"<<endl;

	cout<<"Try to destroy queue..."<<endl;
	destroyQueue(Q);

	system("pause");
	return 0;
}

