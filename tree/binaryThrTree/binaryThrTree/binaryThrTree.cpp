// binaryThrTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

typedef string tElemType;
typedef int Status;
typedef enum PointerTag{Link, Thread};

typedef struct binaryThrNode{
	tElemType data;
	struct binaryThrNode *lchild, *rchild;
	PointerTag lTag, rTag;
}binaryThrNode, *binaryThrTree;

Status createthrTree(binaryThrTree &thrT){
	//create a thread binary tree in pre-order.
	//after this work finished, the attributes lTag and rTag of this thread binary tree is not initialised. 

	string starts;
	cin>>starts;
	if(starts == "#") thrT = NULL;
	else{
		thrT = new binaryThrNode;
		if (!thrT) exit(-1);

		thrT->data = starts;
		thrT->lTag = Link;
		thrT->rTag = Link;
		createthrTree(thrT->lchild);
		createthrTree(thrT->rchild);
	}
	return 1;
}

Status inOrderTraverse(binaryThrTree T){
	if(T){
		inOrderTraverse(T->lchild);
		cout<<(T->data)<<" ";
		inOrderTraverse(T->rchild);
	}
	return 1;
}

void InThreading(binaryThrTree p, binaryThrTree &pre){
	
	if(p){
		InThreading(p->lchild, pre);
		if(!p->lchild){p->lTag = Thread;p->lchild = pre;}
		if(!pre->rchild){pre->rTag = Thread;pre->rchild = p;}
		pre = p;
		InThreading(p->rchild, pre);
	}
}

Status inOrderThreading(binaryThrTree &thrT, binaryThrTree T){
	binaryThrTree pre;

	thrT = new binaryThrNode;
	if(!thrT) exit(-1);

	thrT->lTag = Link;
	thrT->rTag = Thread;
	thrT->rchild = thrT;

	if(!T)thrT->lchild = thrT;
	else{
		thrT->lchild = T;
		pre = thrT;

		InThreading(T ,pre);

		pre->rchild = thrT;
		pre->rTag = Thread;
		thrT->rchild = pre;
	}
	return 1;
}

Status InOrderTraverse_Threads(binaryThrTree thrT){
	binaryThrTree p = thrT->lchild;
	while(p != thrT){
		while(p->lTag == Link) p = p->lchild;
		cout<<p->data<<" ";
		while(p->rTag == Thread && p->rchild!= thrT){
			p = p->rchild;
			cout<<p->data<<" ";
		}
		p = p->rchild;
	}
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	binaryThrTree T = new binaryThrNode;
	if(!T) exit(-1);
	
	cout<<"Try to create a thread binary tree..."<<endl;
	createthrTree(T);
	cout<<"creation is finished!"<<endl;
	cout<<"Try to traverse it:"<<endl;
	inOrderTraverse(T);

	binaryThrTree thrT;
	
	cout<<endl<<"Try to thread the binary thread tree..."<<endl;
	inOrderThreading(thrT, T);
	cout<<"Try to traverse the binary thread tree with threads:"<<endl;
	InOrderTraverse_Threads(thrT);
	
	delete thrT;
	delete T;

	system("pause");
	return 0;
}

