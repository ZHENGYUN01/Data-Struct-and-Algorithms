// circleLinkedList.cpp : Defines the entry point for the console application.
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
}LNode, *circleLinkedList;


ostream& operator <<(ostream& output, ElemType &elem);
istream& operator >>(istream& input, ElemType &elem);

Status initCircleLinkedList(circleLinkedList &L){
	L = new LNode [sizeof(LNode)];
	if(!L) exit(-1);
	L->next = L;
	return 1;
}

void createCircleLinkedList(circleLinkedList &L, int n){
	initCircleLinkedList(L);//L is the head node of the linked list.
	circleLinkedList cur = L;
	for(int i = n; i > 0; i--){
		circleLinkedList p = new LNode [sizeof(LNode)];
		cin>>(p->data);
		p->next = L;
		cur->next = p;
		cur = p;
	}
}

Status printCircleLinkedList(circleLinkedList &L){
	circleLinkedList p = L->next;
	//int j = 1;
	while(p != L){
		cout<<(p->data);
		p = p->next;
	}
	return 1;
}

Status getElem(circleLinkedList &L, int i, ElemType &e){
	//i starts from 1 rather than 0.
	circleLinkedList p = L->next;
	int j = 1;

	while(p!= L && j < i){
		p = p->next;
		j++;
	}
	if(p == L || j > i) return -1;//not exist.
	e = p->data;
	return 1;
}

Status insertCircleLinkedList(circleLinkedList &L, int i, ElemType e){
	//insert an element e into circleLinkedList L before i-th position.
	//i starts from 1 rather than 0.
	circleLinkedList p = L;
	int j = 0;

	while((p->next) != L && j< i - 1){
		p = p->next;
		j++;
	}
	if((p->next) == L || j > i -1) return -1;
	circleLinkedList s = new LNode [sizeof(LNode)];
	s->data = e;
	s->next = p->next;
	p->next = s;
	return 1;
}

Status deleteElem(circleLinkedList &L, int i, ElemType &e){
	circleLinkedList p = L;
	int j = 0;
	
	while((p ->next)!= L && j< i - 1){
		p = p->next;
		j++;
	}

	if((p->next) == L || j > i -1) return -1;
	circleLinkedList q = p->next;//delete the next node of p.
	p->next = q->next;
	e = q->data;
	delete []q;
	return 1;
}

Status mergeCircleLinkedList(circleLinkedList &La, circleLinkedList &Lb, circleLinkedList &Lc){
	circleLinkedList pa = La->next;
	circleLinkedList pb = Lb->next;
	circleLinkedList pc = Lc;

	while(pa != La && pb != Lb){
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
//	pc->next = pa?pa:pb;
	if(pa != La){
		pc->next = pa;
		while((pa->next)!= La){
			pa = pa->next;
		}
		pa->next = Lc;
	}
	else{
		pc->next = pb;
		while((pb->next)!= Lb){
			pb = pb->next;
		}
		pb->next = Lc;
	}

	return 1;
}

Status destroyCircleLinkedList(circleLinkedList &L){
	circleLinkedList p = L;
	circleLinkedList cur;

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
	circleLinkedList List;
	Node tempElem;

	cout<<"please input student info with the form:"<<endl;
	cout<<"courseNum studentName Chinese Math English"<<endl;
	createCircleLinkedList(List, n);

	cout<<"circleLinkedList List:"<<endl;
	printCircleLinkedList(List);

	cout<<"Try to insert an element and please input:"<<endl;
	cin>>tempElem;
	insertCircleLinkedList(List, 1, tempElem);
	printCircleLinkedList(List);

	cout<<"Try to delete an element"<<endl;
	Node deleteOne;
	deleteElem(List, 2, deleteOne);
	cout<<deleteOne<<endl;
	printCircleLinkedList(List);

	cout<<"Try to get an element at i-th position"<<endl;
	Node getOne;
	getElem(List, 2, getOne);
	cout<<getOne<<endl;

	cout<<"Try to merge two circleLinkedList"<<endl;
	circleLinkedList La = List;
	cout<<"circleLinkedList La"<<endl;
	printCircleLinkedList(La);

	circleLinkedList Lb, Lc;
	createCircleLinkedList(Lb, 5);
	cout<<"circleLinkedList Lb"<<endl;
	printCircleLinkedList(Lb);

	initCircleLinkedList(Lc);
	mergeCircleLinkedList(La, Lb, Lc);
	cout<<"Merged circleLinkedList Lc:"<<endl;
	printCircleLinkedList(Lc);

	cout<<"Try to free circleLinkedList"<<endl;
	destroyCircleLinkedList(List);
	

	system("pause");
	return 0;
}

