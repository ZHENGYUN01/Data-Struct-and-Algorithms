// ʮ������.cpp : Defines the entry point for the console application.
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
}arcBox;//�����

typedef struct vexNode{
	vertexType data;
	arcBox *firstIn, *firstOut;
}vexNode;//����ڵ�

typedef struct{
	vexNode xList[MAX_VERTEX_NUM];
	int vexNum, arcNum;
}OLGraph;//ʮ����

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
	}//��ʼ��

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

		//��ӡ�Խ��iΪ��β����
		cout<<"�Խ��"<<i<<"Ϊ��β���� "<<G.xList[i].data;
		while(ptail){
			cout<<"-->"<<"|"<<ptail->tailVex<<"|"<<ptail->headVex;
			ptail = ptail-> tLink;
		}
		cout<<"-->NULL"<<endl;

		//��ӡ�Խ��iΪ��ͷ����

		cout<<"�Խ��"<<i<<"Ϊ��ͷ���� "<<G.xList[i].data;
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

	G.xList[index1].firstOut = pArc;//��ͷ�����뻡���
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
	//ɾ�����󣬸�xList���������иý�����Ľ�㲻ǰ�ƣ���ֻ�ǽ��ñ�ɾ���Ľ���data���ó�Ϊһ���ϴ��ֵ
	int index = locateVertex(G, node);

	for(int i = 0; i<G.vexNum; i++){
		if(i == index)
			continue;
		else{
			deleteArc(G, G.xList[index], G.xList[i]);//ɾ���Ըý��Ϊ��β�Ļ�
			deleteArc(G, G.xList[i], G.xList[index]);//ɾ���Ըý��Ϊ��ͷ�Ļ�
		}
	}
	G.xList[index].data = '0';//��'0'��ʾ�ý�㱻ɾ��
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
		return;//�ý��û�ж�Ӧ�Ļ�
	else if(count <=1)
		G.xList[index1].firstOut = pre->tLink;//ɾ����һ�������
	else
		pre->tLink = cur->tLink;//ɾ���ǵ�һ�������
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
		return;//�ý��û�ж�Ӧ�Ļ�
	else if(count <=1)
		G.xList[index2].firstIn = pre->hLink;
	else
		pre->hLink = cur->hLink;
}

Status deleteArc(OLGraph &G, vexNode node1, vexNode node2){
	//ɾ���ӽ��1�����2�Ļ����з���
	int index1 = locateVertex(G, node1);
	int index2 = locateVertex(G, node2);

	deleteOutArcAction(G, index1, index2);//ɾ���������������ֵ
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