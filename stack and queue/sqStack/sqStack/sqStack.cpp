// sqStack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

#define STACK_INIT_SIZE 2
#define STACKINCREMENT 10

using namespace std;

typedef struct Node{
	string courseNum;
	string studentName;
	float Chinese;
	float Math;
	float English;
}Node;

typedef Node sElemType;
typedef int Status;

ostream& operator <<(ostream& output, sElemType &elem){
	output<<"courseNum:"<<elem.courseNum<<' ';
	output<<"studentName:"<<elem.studentName<<' ';
	output<<"Chinese:"<<elem.Chinese<<' ';
	output<<"Math:"<<elem.Math<<' ';
	output<<"English:"<<elem.English<<' '<<endl;
	return output;
}

istream& operator >>(istream& input, sElemType &elem){
	input>>elem.courseNum>>elem.studentName>>elem.Chinese>>elem.Math>>elem.English;
	return input;
}

typedef struct sqStack{
	sElemType *base;
	sElemType *top;
	int stackSize;
}sqStack;

Status initStack(sqStack &S){
	S.base = new sElemType[STACK_INIT_SIZE * sizeof(sElemType)];

	if(!S.base) exit(-1);
	S.top = S.base;
	S.stackSize = STACK_INIT_SIZE;
	return 1;
}

Status getTop(sqStack &S, sElemType &e){
	if(S.top == S.base) return -1;
	e = *(S.top - 1);
	return 1;
}

Status push(sqStack &S, sElemType e){
	if(S.top - S.base >= S.stackSize){
		sElemType* newbase = new sElemType[(STACK_INIT_SIZE + STACKINCREMENT) * sizeof(sElemType)];
		memcpy(newbase, S.base, S.stackSize * sizeof(sElemType));

		delete []S.base;
		S.base = newbase;
		if(!S.base) exit(-1);

		S.top = S.base + S.stackSize;
		S.stackSize += STACKINCREMENT;
	}
	*S.top++ = e;
	return 1;
}

Status pop(sqStack &S, sElemType &e){
	if(S.top == S.base) return -1;
	e = *(--S.top);
	return 1;
}

Status isEmpty(sqStack &S){
	if(S.top == S.base)
		return 1;
	else
		return 0;
}

Status clearStack(sqStack &S){
	sElemType temp;
	while(!isEmpty(S)){
		pop(S, temp);
	}
	return 1;
}

Status destroyStack(sqStack &S){
	sElemType temp;
	while(!isEmpty(S)){
		pop(S, temp);
	}
	S.base = NULL;
	return 1; 
}

Status printStack(sqStack &S){
	if(isEmpty(S)){
		cout<<"Stack is empty"<<endl;
		return -1;
	}
	sElemType *cur = S.top;

	while(cur != S.base){
		cout<<*(--cur)<<endl;
	}
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{	
	sqStack S;
	initStack(S);
	sElemType elem[4] = {{"2017", "zhangsan", 100, 100, 100}, {"2017", "lisi", 99, 99, 99},{"2017", "wangwu", 98, 98, 98},{"2017", "zhaoliu", 97, 97, 97}};
	for(int i = 0; i<4; i++){
		push(S, elem[i]);
	}
	cout<<"Try to print stack element"<<endl;
	printStack(S);

	cout<<"Try to get the top element of stack"<<endl;
	sElemType top_elem;
	getTop(S,top_elem);
	cout<<top_elem<<endl;

	cout<<"Try to pop elements of stack"<<endl;
	sElemType pop_elem;
	pop(S, pop_elem);
	cout<<"The poped element is:"<<endl;
	cout<<pop_elem<<endl;

	cout<<"Try to check if the stack is empty"<<endl;
	if(isEmpty(S)) 
		cout<<"Empty"<<endl;
	else
		cout<<"Not Empty"<<endl;

	cout<<"Try to clear Stack"<<endl;
	clearStack(S);
	if(isEmpty(S)) 
		cout<<"Stack is cleared"<<endl;
	else
		cout<<"Stack is not cleared"<<endl;

	cout<<"Try to destroy stack..."<<endl;
	destroyStack(S);

	system("pause");
	return 0;
}

