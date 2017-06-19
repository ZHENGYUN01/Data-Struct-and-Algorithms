// linkedQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

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

typedef struct qNode{
	qElemType data;
	struct qNode *next;
}qNode, *queueNodePtr;

typedef struct linkedQueue{
	queueNodePtr front;
	queueNodePtr rear;
}linkedQueue;

Status initQueue(linkedQueue &Q){
	queueNodePtr ptr = new qNode [sizeof(qNode)];
	if(!ptr) exit(-1);

	Q.front = Q.rear = ptr;
	Q.front->next = NULL;
	return 1;
}

Status destroyQueue(linkedQueue &Q){
	queueNodePtr cur = Q.front;
	while(Q.front){
		cur = Q.front->next;
		delete []Q.front;
		Q.front = cur;
	}
	return 1;
}
Status deQueue(linkedQueue &Q, qElemType &e);
Status isEmpty(linkedQueue &Q);

Status clearQueue(linkedQueue &Q){
	qElemType temp;
	while(!isEmpty(Q)){
		deQueue(Q,temp);
	}
	return 1;
}

Status isEmpty(linkedQueue &Q){
	if(Q.rear == Q.front)
		return 1;
	else
		return 0;
}

Status getHead(linkedQueue &Q, qElemType &e){
	if(isEmpty(Q)) return -1;
	e = Q.front->next->data;
	return 1;
}

Status enQueue(linkedQueue &Q, qElemType e){
	queueNodePtr p = new qNode [sizeof(qNode)];
	if(!p) exit(-1);

	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}

Status deQueue(linkedQueue &Q, qElemType &e){
	if(Q.rear == Q.front) return -1;
	queueNodePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p) Q.rear = Q.front;
	delete []p;
	return 1;
}

void printQueue(linkedQueue &Q){
	if(isEmpty(Q))
		cout<<"Queue is empty!"<<endl;

	queueNodePtr cur = Q.front->next;
	while(cur != NULL){
		cout<<(cur->data);
		cur = cur->next;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	linkedQueue Q;
	cout<<"Try to initialize queue..."<<endl;
	initQueue(Q);

	cout<<"Try to insert elements into queue..."<<endl;
	qElemType elem[4] = {{"2017", "zhangsan", 100, 100, 100}, {"2017", "lisi", 99, 99, 99},{"2017", "wangwu", 98, 98, 98},{"2017", "zhaoliu", 97, 97, 97}};
	for(int i = 0; i<4; i++){
		enQueue(Q, elem[i]);
	}

	cout<<"Try to print datas in queue"<<endl;
	printQueue(Q);

	cout<<"Try to delete elements from queue"<<endl;
	qElemType delete_one;
	deQueue(Q, delete_one);
	cout<<"The deleted one is: "<<endl;
	cout<<delete_one<<endl;
	cout<<"The queue after being deleted:"<<endl;
	printQueue(Q);

	cout<<"Try to obtain the head element of queue"<<endl;
	qElemType head_one;
	getHead(Q, head_one);
	cout<<head_one<<endl;

	cout<<"Try to clear queue..."<<endl;
	clearQueue(Q);
	printQueue(Q);
	
	cout<<"Try to judge if the queue is empty after clearing the queue"<<endl;
	if(isEmpty(Q))
		cout<<"Is Empty"<<endl;
	else
		cout<<"Is not Empty"<<endl;

	cout<<"Try to destroy queue..."<<endl;
	destroyQueue(Q);

	system("pause");
	return 0;
}

