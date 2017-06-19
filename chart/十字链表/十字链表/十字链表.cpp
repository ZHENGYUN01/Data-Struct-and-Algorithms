// 十字链表.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

#define MAX_VERTEX_NUM 20

typedef int Status;
typedef int infoType;
typedef char vertexType;

typedef struct arcBox{
	int tailVex, headVex;
	struct arcBox *hLink, *tLink;
	infoType *info;
}arcBox;//弧结点

typedef struct vexNode{
	vertexType data;
	arcBox *firstIn, *firstOut;
}vexNode;//顶点节点

typedef struct{
	vexNode xList[MAX_VERTEX_NUM];
	int vexNum, arcNum;
}OLGraph;//十字链

int locateVertex(OLGraph &G, vexNode node){
	int index = -1;
	for(int i = 0; i<G.vexNum; i++){
		if(node.data == G.xList[i].data){
			index = i;
			break;
		}
	}
	return index;
}

void insertArcAction(OLGraph &G, int index1, int index2);
Status insertArc(OLGraph &G, vexNode node1, vexNode node2);

Status createDG(OLGraph &G, int vexNum, int arcNum){
	G.vexNum = vexNum;
	G.arcNum = arcNum;

	for(int i = 0; i<G.vexNum; i++){
		cin>>G.xList[i].data;
		G.xList[i].firstIn = NULL;
		G.xList[i].firstOut = NULL;
	}//初始化

	for(int i = 0; i<G.arcNum; i++){
		vexNode node1, node2;
		cout<<"please input two nodes of "<<i+1<<"-th arc"<<endl;
		cin>>node1.data>>node2.data;

		insertArc(G, node1, node2); 
	}
	return 1;
}

Status printDG(OLGraph &G){
	for(int i = 0; i<G.vexNum; i++){
		arcBox *ptail = G.xList[i].firstOut;
		arcBox *phead = G.xList[i].firstIn;

		//打印以结点i为弧尾的链
		cout<<"以结点"<<i<<"为弧尾的链 "<<G.xList[i].data;
		while(ptail){
			cout<<"-->"<<"|"<<ptail->tailVex<<"|"<<ptail->headVex;
			ptail = ptail-> tLink;
		}
		cout<<"-->NULL"<<endl;

		//打印以结点i为弧头的链

		cout<<"以结点"<<i<<"为弧头的链 "<<G.xList[i].data;
		while(phead){
			cout<<"-->"<<"|"<<phead->tailVex<<"|"<<phead->headVex;
			phead = phead->hLink;
		}
		cout<<"-->NULL"<<endl;
	}
	return 1;
}

void insertArcAction(OLGraph &G, int index1, int index2){

	arcBox* pArc = new arcBox[1];
	pArc->tailVex = index1;
	pArc->headVex = index2;
	pArc->info = NULL;

	arcBox *ptail = G.xList[index1].firstOut;
	arcBox *phead = G.xList[index2].firstIn;

	if(!ptail){pArc->tLink = NULL;}
	else{pArc->tLink = ptail;}

	if(!phead){pArc->hLink = NULL;}
	else{pArc->hLink = phead;}

	G.xList[index1].firstOut = pArc;//链头部插入弧结点
	G.xList[index2].firstIn = pArc;
}

Status insertArc(OLGraph &G, vexNode node1, vexNode node2){

	int index1 = locateVertex(G, node1);
	int index2 = locateVertex(G, node2);

	insertArcAction(G, index1, index2);
	return 1;
}

Status insertNode(OLGraph &G, vexNode node){

	G.xList[G.vexNum].data = node.data;
	G.xList[G.vexNum].firstIn = NULL;
	G.xList[G.vexNum].firstOut = NULL;
	G.vexNum = G.vexNum + 1;
	return 1;
}

Status deleteArc(OLGraph &G, vexNode node1, vexNode node2);

Status deleteNode(OLGraph &G, vexNode node){
	//删除结点后，该xList顶点数组中该结点后面的结点不前移，而只是将该被删除的结点的data设置成为一个较大的值
	int index = locateVertex(G, node);

	for(int i = 0; i<G.vexNum; i++){
		if(i == index)
			continue;
		else{
			deleteArc(G, G.xList[index], G.xList[i]);//删除以该结点为弧尾的弧
			deleteArc(G, G.xList[i], G.xList[index]);//删除以该结点为弧头的弧
		}
	}
	G.xList[index].data = '0';//置'0'表示该结点被删除
	G.xList[index].firstIn = NULL;
	G.xList[index].firstOut = NULL;

	return 1;
}

void deleteOutArcAction(OLGraph &G, int index1, int index2){
	arcBox *cur = G.xList[index1].firstOut;
	arcBox *pre = cur;

	int count = 0;
	if(!cur)
		return;
	else{
		while(cur){
			count++;
			if(cur->headVex == index2)
				break;
			pre = cur;
			cur = cur->tLink;
		}
	}
	if(!cur)
		return;//该结点没有对应的弧
	else if(count <=1)
		G.xList[index1].firstOut = pre->tLink;//删除第一个弧结点
	else
		pre->tLink = cur->tLink;//删除非第一个弧结点
}

void deleteInArcAction(OLGraph &G, int index1, int index2){
	arcBox *cur = G.xList[index2].firstIn;
	arcBox *pre = cur;

	int count = 0;
	if(!cur)
		return;
	else{
		while(cur){
			count++;
			if(cur->tailVex == index1)
				break;
			pre = cur;
			cur = cur->hLink;
		}
	}
	if(!cur)
		return;//该结点没有对应的弧
	else if(count <=1)
		G.xList[index2].firstIn = pre->hLink;
	else
		pre->hLink = cur->hLink;
}

Status deleteArc(OLGraph &G, vexNode node1, vexNode node2){
	//删除从结点1到结点2的弧（有方向）
	int index1 = locateVertex(G, node1);
	int index2 = locateVertex(G, node2);

	deleteOutArcAction(G, index1, index2);//删除两条链表里面的值
	deleteInArcAction(G, index1, index2);

	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{	
	int vexNum = 4;
	int arcNum = 7;

	OLGraph G;
	
	cout<<"Try to create a Orthogonal List of a graph..."<<endl;
	createDG(G, vexNum, arcNum);
	cout<<"Try to print the Orthogonal List of the very graph..."<<endl;
	printDG(G);
	
	cout<<"Try to insert a node into the graph..."<<endl;
	vexNode node;
	cout<<"   please input the data of the node to insert:"<<endl;
	cin>>node.data;
	insertNode(G, node);
	printDG(G);

	cout<<"Try to insert a arc into the graph..."<<endl;
	vexNode node1, node2;
	cout<<"   please choose two node:"<<endl;
	cin>>node1.data>>node2.data;
	insertArc(G, node1, node2);
	printDG(G);

	cout<<"Try to delete the arc between two nodes..."<<endl;
	vexNode node3, node4;
	cout<<"   please choose a arc with specifing two nodes:"<<endl;
	cin>>node3.data>>node4.data;
	deleteArc(G, node3, node4);
	printDG(G);

	cout<<"Try to delete a node of the graph..."<<endl;
	vexNode node5;
	cout<<"   please choose a node:"<<endl;
	cin>>node5.data;
	deleteNode(G, node5);
	printDG(G);

	system("pause");

	return 0;
}