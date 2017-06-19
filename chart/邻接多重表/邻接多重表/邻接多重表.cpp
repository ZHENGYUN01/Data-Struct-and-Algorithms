// 邻接多重表.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

#define MAX_VERTEX_NUM 20

typedef int infoType;
typedef char vertexType;
typedef int Status;

typedef struct edgeNode{
	int iVex, jVex;
	struct edgeNode *iLink, *jLink;
	infoType *info;
}edgeNode;

typedef struct vertexNode{
	vertexType data;
	edgeNode *firstEdge;
}vertexNode;

typedef struct{
	vertexNode adjmultiList[MAX_VERTEX_NUM];
	int vexNum, edgeNum;
}AMLGraph;

int locateNode(AMLGraph &G, vertexNode node){
	for(int i=0; i<G.vexNum;i++){
		if(node.data == G.adjmultiList[i].data)
			return i;
	}
	return -1;
}

Status insertEdge(AMLGraph &G, vertexNode node1, vertexNode node2);

Status createAMLGraph(AMLGraph &G, int vexNum){
	G.vexNum = vexNum;
	G.edgeNum = 0;
	for(int i = 0; i< G.vexNum; i++){
		cin>>G.adjmultiList[i].data;
		G.adjmultiList[i].firstEdge = NULL;
	}

	cout<<"Try to input arcs info"<<endl;
	while(1){
		char SWITCH;
		cout<<"are you going to add a edge into AMLGraph?(y?n)"<<endl;
		
		cin>>SWITCH;
		if(SWITCH == 'y'){
			cout<<"please input two nodes of "<<G.edgeNum+1<<"-th arc"<<endl;

			vertexNode node1, node2;
			cin>>node1.data>>node2.data;
			insertEdge(G, node1, node2);
			G.edgeNum++;
		}
		else
			break;
	}
	return 1;
}

void insertEdgeAction(AMLGraph &G, int index1, int index2){
	edgeNode *p, *q;
	edgeNode *edge = new edgeNode[1];
	
	edge->iVex = index1;
	edge->jVex = index2;

	p = G.adjmultiList[index1].firstEdge;//相当于链表的插入
	if(!p){
		G.adjmultiList[index1].firstEdge = edge;
		edge->iLink = NULL;
	}
	else{
		G.adjmultiList[index1].firstEdge = edge;

		edge->iLink = p;
	}

	q = G.adjmultiList[index2].firstEdge;//相当于链表的插入
	if(!q){
		G.adjmultiList[index2].firstEdge = edge;
		edge->jLink = NULL;
	}
	else{
		G.adjmultiList[index2].firstEdge = edge;
		edge->jLink = q;
	}
}

Status insertEdge(AMLGraph &G, vertexNode node1, vertexNode node2){
	int index1 = locateNode(G, node1);//i和j表示AdjList[MAX_VERTEX_NUM]中的位置
	int index2 = locateNode(G, node2);
	if(index1<0 || index2<0) exit(-1);
	
	insertEdgeAction(G, index1, index2);

	return 1;
}

Status printAMLGraph(AMLGraph &G){
	for(int i = 0; i<G.vexNum; i++){
		cout<<i<<" "<<G.adjmultiList[i].data;
		edgeNode *edge = G.adjmultiList[i].firstEdge;

		while(edge){
			cout<<"-->|"<<edge->iVex<<"|"<<edge->jVex<<"|";
			if(edge->iVex == i){
				edge = edge->iLink;
			}
			else{
				edge = edge->jLink;
			}
		}
		cout<<"-->NULL"<<endl;
	}
	return 1;
}

Status insertNode(AMLGraph &G, vertexNode node){
	G.adjmultiList[G.vexNum].data = node.data;
	G.adjmultiList[G.vexNum].firstEdge = NULL;
	G.vexNum++;
	return 1;
}

Status deleteEdgeAction(AMLGraph &G, int index1, int index2){
	edgeNode *curEdge = G.adjmultiList[index1].firstEdge;
	edgeNode *preEdge = curEdge;
	int count = 0;

	if(!curEdge) return 1;
	else{
		while(curEdge){
			count++;
			if((curEdge->iVex == index1&&curEdge->jVex == index2)||(curEdge->iVex == index2&&curEdge->jVex == index1)){
				break;
			}
			preEdge = curEdge;
			if(curEdge->iVex ==index1)
				curEdge = curEdge->iLink;
			else
				curEdge = curEdge->jLink;
		}
	}

	if(!curEdge)
		return 1;
	else if(count<=1){
		if(preEdge->iVex == index1)
			G.adjmultiList[index1].firstEdge = preEdge->iLink;
		else 
			G.adjmultiList[index1].firstEdge = preEdge->jLink;
	}
	else{
		if(preEdge->iVex == index1){ 
			if (curEdge->iVex == index1)
				preEdge->iLink = curEdge->iLink;
			else
				preEdge->iLink = curEdge->jLink;
		}
		else{
			if (curEdge->iVex == index1)
				preEdge->jLink = curEdge->iLink;
			else
				preEdge->jLink = curEdge->jLink;
		}
	}
	return 1;
}

Status deleteEdge(AMLGraph &G, vertexNode node1, vertexNode node2){
	int index1 = locateNode(G, node1);
	int index2 = locateNode(G, node2);

	deleteEdgeAction(G, index1, index2);
	deleteEdgeAction(G, index2, index1);

	return 1;
}

Status deleteNode(AMLGraph &G, vertexNode node){
	//删除结点时，结点不真实删除而只是删除结点相关的边以及赋值该结点的data为特殊值‘0’
	int index = locateNode(G, node);

	for(int i = 0; i<G.vexNum; i++){
		if(i == index) continue;
		else{
			deleteEdge(G, G.adjmultiList[index], G.adjmultiList[i]);
		}
	}
	G.adjmultiList[index].firstEdge = NULL;
	G.adjmultiList[index].data = '0';
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int vexNum = 5;
	AMLGraph G;
	cout<<"Try to create a adjacence multilist of a graph ..."<<endl;
	createAMLGraph(G, vexNum);
	printAMLGraph(G);

	cout<<"Try to insert a node into the graph..."<<endl;
	vertexNode node;
	cout<<"   please input the data of the node to insert:"<<endl;
	cin>>node.data;
	insertNode(G, node);
	printAMLGraph(G);

	cout<<"Try to insert a edge into the graph..."<<endl;
	vertexNode node1, node2;
	cout<<"   please choose two node:"<<endl;
	cin>>node1.data>>node2.data;
	insertEdge(G, node1, node2);
	printAMLGraph(G);

	cout<<"Try to delete the edge between two nodes..."<<endl;
	vertexNode node3, node4;
	cout<<"   please choose a edge with specifing two nodes:"<<endl;
	cin>>node3.data>>node4.data;
	deleteEdge(G, node3, node4);
	printAMLGraph(G);

	cout<<"Try to delete a node of the graph..."<<endl;
	vertexNode node5;
	cout<<"   please choose a node:"<<endl;
	cin>>node5.data;
	deleteNode(G, node5);
	printAMLGraph(G);

	system("pause");
	return 0;
}

