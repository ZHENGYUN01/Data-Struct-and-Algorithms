// linkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

typedef int Status;
typedef struct Node{
	string courseNum;
	string studentName;
	float Chinese;
	float Math;
	float English;
}Node;
typedef Node ElemType;

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *linkedList;


ostream& operator <<(ostream& output, ElemType &elem);
istream& operator >>(istream& input, ElemType &elem);

Status initLinkedList(linkedList &L){
	L = new LNode [sizeof(LNode)];
	if(!L) exit(-1);
	L->next = NULL;
	return 1;
}

void createLinkedList(linkedList &L, int n){
	initLinkedList(L);//L is the head node of the linked list.
	linkedList cur = L;
	for(int i = n; i > 0; i--){
		linkedList p = new LNode [sizeof(LNode)];
		cin>>(p->data);
		p->next = cur->next;
		cur->next = p;
		cur = p;
	}
}

Status printLinkedList(linkedList &L){
	linkedList p = L->next;
	//int j = 1;
	while(p){
		cout<<(p->data);
		p = p->next;
	}
	return 1;
}

Status getElem(linkedList &L, int i, ElemType &e){
	//i starts from 1 rather than 0.
	linkedList p = L->next;
	int j = 1;

	while(p && j < i){
		p = p->next;
		j++;
	}
	if(!p || j > i) return -1;//not exist.
	e = p->data;
	return 1;
}

Status insertLinkedList(linkedList &L, int i, ElemType e){
	//insert an element e into linkedList L before i-th position.
	//i starts from 1 rather than 0.
	linkedList p = L;
	int j = 0;

	while(p && j<i -1){
		p = p->next;
		j++;
	}
	if(!p || j > i -1) return -1;
	linkedList s = new LNode [sizeof(LNode)];
	s->data = e;
	s->next = p->next;
	p->next = s;
	return 1;
}

Status deleteElem(linkedList &L, int i, ElemType &e){
	linkedList p = L;
	int j = 0;
	
	while(p ->next && j< i - 1){
		p = p->next;
		j++;
	}

	if(!(p->next) || j > i -1) return -1;
	linkedList q = p->next;//delete the next node of p.
	p->next = q->next;
	e = q->data;
	delete []q;
	return 1;
}

Status mergeLinkedList(linkedList &La, linkedList &Lb, linkedList &Lc){
	linkedList pa = La->next;
	linkedList pb = Lb->next;
	linkedList pc = Lc;

	while(pa && pb){
		if(pa->data.Chinese <= pb->data.Chinese){
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else{
			pc->next = pb;
			pc = pb;
			pb = pb->next;		
		}
	}
	pc->next = pa?pa:pb;
	return 1;
}

Status destroyLinkedList(linkedList &L){
	linkedList p = L;
	linkedList cur;

	while(p){
		cur = p->next;
		delete []p;
		p = cur;
	}
	return 1;
}

ostream& operator <<(ostream& output, ElemType &elem){
	output<<"courseNum:"<<elem.courseNum<<' ';
	output<<"studentName:"<<elem.studentName<<' ';
	output<<"Chinese:"<<elem.Chinese<<' ';
	output<<"Math:"<<elem.Math<<' ';
	output<<"English:"<<elem.English<<' '<<endl;
	return output;
}

istream& operator >>(istream& input, ElemType &elem){
	input>>elem.courseNum>>elem.studentName>>elem.Chinese>>elem.Math>>elem.English;
	return input;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n = 3;
	linkedList List;
	Node tempElem;

	cout<<"please input student info with the form:"<<endl;
	cout<<"courseNum studentName Chinese Math English"<<endl;
	createLinkedList(List, n);

	cout<<"LinkedList List:"<<endl;
	printLinkedList(List);

	cout<<"Try to insert an element and please input:"<<endl;
	cin>>tempElem;
	insertLinkedList(List, 1, tempElem);
	printLinkedList(List);

	cout<<"Try to delete an element"<<endl;
	Node deleteOne;
	deleteElem(List, 2, deleteOne);
	cout<<deleteOne<<endl;
	printLinkedList(List);

	cout<<"Try to get an element at i-th position"<<endl;
	Node getOne;
	getElem(List, 2, getOne);
	cout<<getOne<<endl;

	cout<<"Try to merge two linkedList"<<endl;
	linkedList La = List;
	cout<<"LinkedList La"<<endl;
	printLinkedList(La);

	linkedList Lb, Lc;
	createLinkedList(Lb, 5);
	cout<<"LinkedList Lb"<<endl;
	printLinkedList(Lb);

	initLinkedList(Lc);
	mergeLinkedList(La, Lb, Lc);
	cout<<"Merged LinkedList Lc:"<<endl;
	printLinkedList(Lc);

	cout<<"Try to free linkedList"<<endl;
	destroyLinkedList(List);
	

	system("pause");
	return 0;
}

