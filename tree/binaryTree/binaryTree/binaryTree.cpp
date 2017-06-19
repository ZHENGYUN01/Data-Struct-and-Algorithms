// binaryTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

typedef struct Node{
	string courseNum;
	string studentName;
	float Chinese;
	float Math;
	float English;
}Node;

//typedef Node tElemType;
typedef string tElemType;
typedef int Status;

typedef struct binaryTreeNode{
	tElemType data;
	struct binaryTreeNode *lchild, *rchild;
}binaryTreeNode, *binaryTree;

Status createBinaryTree(binaryTree &T){
	string starts;
	cin>>starts;
	if(starts == "#") T = NULL;
	else{
		T = new binaryTreeNode;
		if (!T) exit(-1);

		T->data = starts;
		createBinaryTree(T->lchild);
		createBinaryTree(T->rchild);
	}
	return 1;
}

Status preOrderTraverse(binaryTree T){
	if(T){
		cout<<(T->data)<<" ";
		preOrderTraverse(T->lchild);
		preOrderTraverse(T->rchild);
	}
	return 1;
}

Status inOrderTraverse(binaryTree T){
	if(T){
		inOrderTraverse(T->lchild);
		cout<<(T->data)<<" ";
		inOrderTraverse(T->rchild);
	}
	return 1;
}

Status postOrderTraverse(binaryTree T){
	if(T){
		postOrderTraverse(T->lchild);
		postOrderTraverse(T->rchild);
		cout<<(T->data)<<" ";
	}
	return 1;
}

Status levelTraverse(binaryTree T){
	binaryTree temp = T;
	queue<binaryTree> queue;

	if(T){
		queue.push(temp);
		while(!queue.empty()){
			temp = queue.front();
			cout<<temp->data<<" ";
			queue.pop();
			if(temp->lchild) queue.push(temp->lchild);
			if(temp->rchild) queue.push(temp->rchild);
		}
	}
	return 1;
}

Status preOrderTraverse_1(binaryTree T){
	//traverse the binary tree without recursive algorithm.
	stack<binaryTree> stack;
	binaryTree p = T;

	while(p || !stack.empty()){
		if(p){
			stack.push(p);
			cout<<p->data<<" ";
			p = p->lchild;
		}
		else{
			p = stack.top();
			stack.pop();
			p = p->rchild;
		}
	}
	return 1;
}

Status inOrderTraverse_1(binaryTree T){
	//traverse the binary tree without recursive algorithm.
	stack<binaryTree> stack;
	binaryTree p = T;

	while(p || !stack.empty()){
		if(p){
			stack.push(p);
			p = p->lchild;
		}
		else{
			p = stack.top();
			stack.pop();
			cout<<(p->data)<<" ";
			p = p->rchild;
		}
	}
	return 1;
}

Status postOrderTraverse_1(binaryTree T){

	stack<binaryTree> s1 , s2;      
	binaryTree curr ;// 指向当前要检查的节点    
	s1.push(T);    
	while(!s1.empty())// 栈空时结束      
	{    
		curr = s1.top();    
		s1.pop();    
		s2.push(curr);    
		if(curr->lchild)    
			s1.push(curr->lchild);    
		if(curr->rchild)    
			s1.push(curr->rchild);    
	}    
	while(!s2.empty())    
	{    
		cout<<s2.top()->data<<" ";    
		s2.pop();    
	}    
	return 1;
}    

int countNode(binaryTree T){
	if(!T)
		return 0;
	else{
		return (1 + countNode(T->lchild) + countNode(T->rchild));
	}
}

int depth(binaryTree T){
	int lDepth, rDepth;
	if(!T)
		return 0;
	else{
		lDepth = depth(T->lchild);
		rDepth = depth(T->rchild);
		return (lDepth > rDepth ? lDepth : rDepth) + 1;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	binaryTree T;
	cout<<"Try to create a binary tree..."<<endl;
	createBinaryTree(T);

	cout<<"Try to traverse a binary tree in pre-order..."<<endl;
	preOrderTraverse(T);
	cout<<endl;
	cout<<"Try to traverse a binary tree in pre-order without recursive algorithm"<<endl;
	preOrderTraverse_1(T);
	cout<<endl;

	cout<<"Try to traverse a binary tree in in-order..."<<endl;
	inOrderTraverse(T);
	cout<<endl;
	cout<<"Try to traverse a binary tree in in-order without recursive algorithm"<<endl;
	inOrderTraverse_1(T);
	cout<<endl;

	cout<<"Try to traverse a binary tree in post-order..."<<endl;
	postOrderTraverse(T);
	cout<<endl;
	cout<<"Try to traverse a binary tree in post-order without recursive algorithm"<<endl;
	postOrderTraverse_1(T);
	cout<<endl;

	cout<<"Try to traverse a binary tree in level..."<<endl;
	levelTraverse(T);

	cout<<"Try to count number of nodes of the binary tree..."<<endl;
	cout<<"The Number of nodes is: "<<countNode(T)<<endl;

	cout<<"Try to figure out the depth of binary tree..."<<endl;
	cout<<"The depth of binary tree is: "<<depth(T)<<endl;

	system("pause");
	return 0;
}

