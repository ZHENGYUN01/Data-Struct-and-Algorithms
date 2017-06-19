// doubleLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

typedef struct Node{
	string courseNum;
	string studentName;
	float Chinese;
	float Math;
	float English;
}Node;

typedef Node ElemType;
typedef int Status;

istream& operator >>(istream& input, ElemType &elem);
ostream& operator <<(ostream& output, ElemType &elem);

typedef struct DuLNode{
	ElemType data;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode, *DuLNodeList;

Status initDuLNodeList(DuLNodeList &L ,int n){
	L = new DuLNode [sizeof(DuLNode)];
	if(!L) exit(-1);
	L->prior = NULL;

	DuLNodeList cur = L;
	for(int i = n; i > 0; i--){
		DuLNodeList p = new DuLNode [sizeof(DuLNode)];
		if(!p) exit(-1);

		cin>>(p->data);

		p->next = NULL;
		p->prior = cur;
		cur->next = p;
		cur = p;
	}
	return 1;
}

DuLNodeList getElemPosition(DuLNodeList &L, int i);
int getLengthofDuLNodeList(DuLNodeList &L);

Status insertDuLNodeList(DuLNodeList &L, int i, ElemType e){
	DuLNodeList p;
	if(!(p = getElemPosition(L, i))) return -1;
	DuLNodeList q = new DuLNode [sizeof(DuLNode)];
	if(!q) return -1;

	if (p->next){
		//insert the element in the mid of L or the first of L.
		q->data = e;
		q->prior = p;
		q->next = p->next;
		p->next->prior = q;
		p->next = q;
	}
	else{
		//insert the element on the tail of L.
		q->data = e;
		q->prior = p;
		q->next = p->next;
		//p->next->prior = q;
		p->next = q;
	}
	return 1;
}

Status deleteElem(DuLNodeList &L, int i, ElemType &e){
	int length = getLengthofDuLNodeList(L);
	if (i<1 || i>length) return -1;	

	DuLNodeList cur = L;
	int j = 0;
	while(cur->next && j<i){
		cur = cur->next;
		j++;
	}
	e = cur->data;

	if(cur->next){
		//delete the element in the mid of L.
		cur->prior->next = cur->next;
		cur->next->prior = cur->prior;
	}
	else{
		//delete the element at the tail of L.
		cur->prior->next = NULL;
	}
	return 1;
}

Status printDuLNodeList(DuLNodeList &L){
	DuLNodeList cur = L;
	while(cur->next){
		cur = cur->next;
		cout<<(cur->data);
	}
	return 1;
}

Status mergeDuLNodeList(DuLNodeList &La, DuLNodeList &Lb, DuLNodeList &Lc){
	DuLNodeList pa = La->next;
	DuLNodeList pb = Lb->next;
	DuLNodeList pc = Lc;

	while(pa&&pb){
		if(pa->data.Chinese < pb->data.Chinese){
			pc->next = pa;
			pa->prior = pc;
			pc = pa;
			pa = pa->next;
		}
		else{
			pc->next = pb;
			pb->prior = pc;
			pc = pb;
			pb = pb->next;
		}
	}

	//pc->next = pa?pa:pb;
	if(pa){
		pc->next = pa;
		pa->prior = pc;
	}
	else{
		pc->next = pb;
		pb->prior = pc;
	}
	delete []La;
	delete []Lb;

	return 1;
	
}

int getLengthofDuLNodeList(DuLNodeList &L){
	DuLNodeList cur = L;
	int length = 0;

	while(cur->next){
		cur = cur->next;
		length++;
	}
	return length;
}

DuLNodeList getElemPosition(DuLNodeList &L, int i){
//obtain proper position to insert an element
	int length = getLengthofDuLNodeList(L);
	if (i<0 || i>length+1) exit(-1);
	
	DuLNodeList cur = L;
	int j = 0;

	while(cur->next && j < i-1){
		cur = cur->next;
		j++;
	}
	return cur;
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
	DuLNodeList L;
	int n = 3;
	int i = 3;
	cout<<"Try to initialise L:"<<endl;
	initDuLNodeList(L ,n);
	printDuLNodeList(L);

	cout<<"Try to insert an element into L:"<<endl;
	ElemType insert_one;
	cin>>insert_one;
	insertDuLNodeList(L, i+1, insert_one);
	printDuLNodeList(L);

	cout<<"Try to delete an element of L:"<<endl;
	ElemType delete_one;
	deleteElem(L, i, delete_one);
	cout<<"The deleted one:"<<endl;
	cout<<delete_one;
	cout<<"The DuLNodeList L after being deleted:"<<endl;
	printDuLNodeList(L);

	cout<<"Try to merge two DuLNodeList:"<<endl;
	DuLNodeList La, Lb, Lc;
	initDuLNodeList(La ,3);
	cout<<"La:"<<endl;
	printDuLNodeList(La);

	initDuLNodeList(Lb ,4);
	cout<<"Lb:"<<endl;
	printDuLNodeList(Lb);

	initDuLNodeList(Lc ,0);
	cout<<"merged DuLNodeList(Lc):"<<endl;
	mergeDuLNodeList(La, Lb, Lc);
	printDuLNodeList(Lc);

	system("pause");
	return 0;
}

