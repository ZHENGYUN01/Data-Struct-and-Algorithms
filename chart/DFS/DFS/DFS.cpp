// DFS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

#define MAX_VERTEX_NUM 20
#define INT_FIN 500

using namespace std;

typedef int infoType;//����Ϣ
typedef char vertexType;//���㱣���ַ���Ϣ
typedef int Status;

typedef struct ArcNode{
	int adjvex;
	struct ArcNode *nextArc;
	infoType *info;
}ArcNode;

typedef struct VertexNode{
	vertexType data;
	ArcNode *firstArc;
}VertexNode, AdjList[MAX_VERTEX_NUM];

typedef struct ALGraph{
	AdjList vertices;
	int vertexNum, arcNum;
	string kind;
}ALGraph;

int locateNode(ALGraph &G, VertexNode node){
	for(int i=0; i<G.vertexNum;i++){
		if(node.data == G.vertices[i].data)
			return i;
	}
	return -1;
}

void insertArcAction(ALGraph &G, int nodeNum1, int nodeNum2);
Status insertArc(ALGraph &G, VertexNode node1, VertexNode node2);

Status createGraph(ALGraph &G, string kind, int vertexNum, int arcNum){
	//�����ڽӱ���ͼ�����������ͼ��
	G.kind = kind;

	G.vertexNum = vertexNum;
	G.arcNum = arcNum;
	
	//��ʼ��������Ϣ
	for(int i = 0; i<G.vertexNum; i++){
		cin>>G.vertices[i].data;
		G.vertices[i].firstArc = NULL;
	}

	cout<<"Try to input arcs info"<<endl;
	for(int j = 0; j<G.arcNum; j++){
		cout<<"please input two nodes of "<<j+1<<"-th arc"<<endl;

		VertexNode node1, node2;
		cin>>node1.data>>node2.data;
		insertArc(G, node1, node2);
	}
	return 1;
}

Status insertVertex(ALGraph &G, VertexNode node){
	G.vertexNum = G.vertexNum + 1;
	G.vertices[G.vertexNum - 1].data = node.data;
	G.vertices[G.vertexNum - 1].firstArc = NULL;
	return 1;
}

void insertArcAction(ALGraph &G, int nodeNum1, int nodeNum2){
	ArcNode *p;
	ArcNode *arc;

	arc = new ArcNode[1];
	arc->adjvex = nodeNum2;

	p = G.vertices[nodeNum1].firstArc;//�൱������Ĳ���
	if(!p){
		G.vertices[nodeNum1].firstArc = arc;
		arc->nextArc = NULL;
	}
	else{
		G.vertices[nodeNum1].firstArc = arc;
		arc->nextArc = p;
	}
}

Status insertArc(ALGraph &G, VertexNode node1, VertexNode node2){
	int nodeNum1 = locateNode(G, node1);//i��j��ʾAdjList[MAX_VERTEX_NUM]�е�λ��
	int nodeNum2 = locateNode(G, node2);
	if(nodeNum1<0 || nodeNum2<0) exit(-1);
	
	if(G.kind == "DG")
		insertArcAction(G, nodeNum1, nodeNum2);
	else{
		insertArcAction(G, nodeNum1, nodeNum2);
		insertArcAction(G, nodeNum2, nodeNum1);
	}
	return 1;
}

Status printALGraph(ALGraph &G){
	for(int i = 0; i<G.vertexNum; i++){
		cout<<i<<" "<<G.vertices[i].data;
		ArcNode *arc = G.vertices[i].firstArc;

		while(arc){
			cout<<"-->"<<arc->adjvex;
			arc = arc->nextArc;
		}
		cout<<"-->NULL"<<endl;
	}
	return 1;
}

void deleteArcAction(ALGraph &G, int index1, int index2);
Status deleteArc(ALGraph &G, VertexNode node1, VertexNode node2);

Status deleteVertex(ALGraph &G, VertexNode node){
	int index = locateNode(G, node);
	
	for(int i = 0; i<G.vertexNum; i++){
		if(i == index)
			continue;
		else{
			VertexNode node1 = G.vertices[i];
			deleteArc(G, node1, node);//ɾ���Ըý��Ϊ��ͷ��Ӧ�Ļ�
		}
	}
	G.vertices[index].firstArc = NULL;//ɾ�����иý������Ļ�
	G.vertices[index].data = INT_FIN;//��һ���ܴ������ʾ�ý�㱻ɾ��
	return 1;
}

void deleteArcAction(ALGraph &G, int index1, int index2){
	ArcNode *cur = G.vertices[index1].firstArc;
	ArcNode *pre = cur;
	int count = 0;
	if(!cur)
		return;
	else{
		while(cur){
			count++;

			if(cur->adjvex == index2)
				break;
			pre = cur;
			cur = cur->nextArc;
		}
	}
	if(!cur)
		return;//�ý��û�ж�Ӧ�Ļ�
	else if(count <=1)
		G.vertices[index1].firstArc = pre->nextArc;
	else
		pre->nextArc = cur->nextArc;
}

Status deleteArc(ALGraph &G, VertexNode node1, VertexNode node2){
	//node1Ϊ��β��node2Ϊ��ͷ��node1 ----> node2
	
	int index1 = locateNode(G, node1);
	int index2 = locateNode(G, node2);
	if(index1 < 0 || index2 < 0) exit(-1);

	if(G.kind == "DG"){
		//����ͼɾ������ɾ��һ��
		deleteArcAction(G, index1, index2);
	}
	else{
		//����ͼɾ������ɾ������
		deleteArcAction(G, index1, index2);
		deleteArcAction(G, index2, index1);
	}
	return 1;
}

bool visited[MAX_VERTEX_NUM];

int FirstAdjVex(ALGraph G, int j){
	ArcNode *firstArc = G.vertices[j].firstArc;
	if(firstArc)
		return (firstArc->adjvex);
	else 
		return -1;
}

int NextAdjVex(ALGraph G, int j, int k){
	ArcNode *firstArc = G.vertices[j].firstArc;
	ArcNode *cur = firstArc;

	if(!firstArc)
		return -1;
	else{
		while(cur){
			if(cur->adjvex == k)
				break;
			cur = cur->nextArc;
		}
	}
	if(cur->nextArc)
		return (cur->nextArc->adjvex);
	else
		return -1;
}

void DFS(ALGraph G, int j){
	visited[j] = true;
	cout<<"node: "<<G.vertices[j].data<<" ";
	for(int k = FirstAdjVex(G, j); k>=0; k = NextAdjVex(G, j, k)){
		if(!visited[k])
			DFS(G, k);
	}
}

Status DFGTraverse(ALGraph G){
	//�ݹ���ʽ������ȷ�����
	for(int i = 0;i<G.vertexNum; i++) visited[i] = false;
	for(int j = 0;j<G.vertexNum; j++)
		if(!visited[j])
			DFS(G,j);
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ALGraph G;
	string kind = "UDG";
	int vertexNum = 9;
	int arcNum = 9;

	cout<<"Try to create a Adjacency list Graph ..."<<endl;
	createGraph(G, kind, vertexNum, arcNum);
	
	cout<<"Try to print a Adjacence list Graph ..."<<endl;
	printALGraph(G);

	cout<<"Try to traverse a undigraph ..."<<endl;
	DFGTraverse(G);

	system("pause");
	return 0;
}


