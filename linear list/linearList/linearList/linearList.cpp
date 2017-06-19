// linearList.cpp : Defines the entry point for the console application.
//
//Linear List with seqential physical space.

#include "stdafx.h"
#include<cstdlib>
#include <string>
#include <iostream>

using namespace std;

#define LIST_INIT_SIZE 3
#define LISTINCREMENT 10

typedef int Status;

typedef struct Node{
	string courseNum;
	string studentName;
	float Chinese;
	float Math;
	float English;
}Node;

typedef Node ElemType;

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

typedef struct LNode{  
    ElemType  *elem;        //存储空间的基地址  
    int      length;        //当前的长度  
    int      listSize;      //当前分配的存储容量  
}SqList; 

Status initList(SqList &L)
{
	//L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	L.elem = new ElemType [LIST_INIT_SIZE * sizeof(ElemType)];
	if (!L.elem) exit(-1);
	L.length = 0;
	L.listSize = LIST_INIT_SIZE;
	return 1;
}

Status insertList(SqList &L, ElemType e, int i){
	 if (i < 0 || i > L.listSize) return -1;
	 if (L.length >= L.listSize){

		 ElemType *newLoc = new ElemType [(L.listSize + LISTINCREMENT)*sizeof(ElemType)];
		 memcpy(newLoc, L.elem, L.length*sizeof(ElemType));

		 if (!newLoc) return -1;
		 L.elem = newLoc;
		 L.listSize += LISTINCREMENT;
	 }
	 ElemType *temp = &L.elem[i];

	 for(ElemType *cur = &L.elem[L.length];cur > temp;cur--){
		 *cur = *(cur - 1);
	 }
	 *(L.elem + i) = e;
	 L.length += 1;
	 return 1;
}

Status deleteListItem(SqList &L, ElemType &e, int i){
	if(i < 1 || i > L.length) return -1;//i means the i-th element in SqList.
	e = *(L.elem + i-1);
	ElemType *cur = L.elem + i -1;
	ElemType *end = L.elem + L.length -1;
	for(;cur < end;cur++){
		*cur = *(cur + 1);
	}
	--L.length;
	return 1;
}

Status priorElem(SqList &L, ElemType &e, int i){
	if(i <= 1 || i > L.length) return -1;
	ElemType *cur = L.elem + i -1;
	e = *(cur - 1);
	return 1;
}

Status getElem(SqList &L, ElemType &e, int i){
	if (i < 1 || i > L.length) return -1;
	ElemType *cur = L.elem + i - 1;
	e = *cur;
	return 1;
}

Status nextElem(SqList &L, ElemType &e, int i){
	if(i < 1 || i >= L.length) return -1;
	ElemType *cur = L.elem + i - 1;
	e = *(cur + 1);
	return 1;
}

Status mergeList(SqList &La, SqList &Lb, SqList &Lc){
	initList(Lc);
	int i =1; 
	int j = 1, k = 0;
	int len_La = La.length;
	int len_Lb = Lb.length;
	ElemType elem_La, elem_Lb;

	while((i <= len_La) && (j <= len_Lb)){
		getElem(La, elem_La, i);
		getElem(Lb, elem_Lb, j);
		if( elem_La.Chinese < elem_Lb.Chinese){
			insertList(Lc, elem_La, k++);
			i++;
		}
		else{
			insertList(Lc, elem_Lb, k++);
			j++;
		}
	}
	while(i <= len_La){
		getElem(La, elem_La, i++);
		insertList(Lc, elem_La, k++);
	}
	while(j <= len_Lb){
		getElem(Lb, elem_Lb, j++);
		insertList(Lc, elem_Lb, k++);
	}
	return 1;
}

int locateElem(SqList &La, ElemType e, Status (*compare)(ElemType, ElemType)){
	int i = 1;
	ElemType *cur = La.elem;
	while(i <= La.length && !(*compare)(*cur++, e)) ++i;

	if (i <= La.length)
		return i;
	return -1;//mismatch
}

Status elemCompare(ElemType elem1, ElemType elem2){
	//find the first student who scores much more than the referenced one.
	if (elem1.Chinese >= elem2.Chinese && elem1.Math >= elem2.Math && elem1.English >= elem2.English)
		return 1;
	return 0;
}

Status printList(SqList &L){
	/*cout<<"It's printing SqList"<<endl;*/
	for (int i = 0;i < L.length; i++){
		cout<<L.elem[i];	
	}
	return 1;
}

Status destroyList(SqList &L){
	delete []L.elem;
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	SqList List;
	int length = 3;

	initList(List);
	ElemType tempElem,reference_one;

	reference_one.courseNum = "0000";
	reference_one.studentName = "reference_one";
	reference_one.Chinese = 60;
	reference_one.Math = 60;
	reference_one.English = 60;

	cout<<"please input scores of your teching students with the form:"<<endl;
	cout<<"courseNum studentName Chinese Math English"<<endl;
	for (int i = 0; i < length; i++){
		
		cin>>tempElem;
		insertList(List, tempElem, i);
	}
	cout<<"original List is :"<<endl;
	printList(List);

	int (*ptrFunc)(ElemType, ElemType);
	ptrFunc = elemCompare;

	int j = locateElem(List, reference_one, ptrFunc);
	if (j < 1 || j > List.length){
		cout<<"Matches None!"<<endl;
	}
	else{
		cout<<"The first student who scores much more than the referenced one is:"<<endl;
		getElem(List, tempElem, j);
		cout<<tempElem<<endl;
	}
	cout<<"try to insert one element"<<endl;
	cin>>tempElem;
	insertList(List, tempElem, 2);
	printList(List);

	cout<<"try to delete one element"<<endl;
	deleteListItem(List, tempElem, 2);
	printList(List);
	cout<<"the element erased is:"<<endl;
	cout<<tempElem<<endl;

	SqList List1, List2;
	initList(List1);
	cout<<"please input scores of your teching students from another class with the form:"<<endl;
	cout<<"courseNum studentName Chinese Math English"<<endl;
	for (int i = 0; i < length + 1; i++){
		cin>>tempElem;
		insertList(List1, tempElem, i);
	}

	cout<<"List1 is :"<<endl;
	printList(List1);

	mergeList(List, List1, List2);
	cout<<"mergeList is:"<<endl;
	printList(List2);

	cout<<"Try to destroy SqList"<<endl;
	destroyList(List);
	destroyList(List1);
	destroyList(List2);

	system("pause");
	return 0;

}

