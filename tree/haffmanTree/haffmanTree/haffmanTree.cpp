// haffmanTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

typedef struct {
	int weight;
	int parent, lchild, rchild;
}huffmanTreeNode, *huffmanTree;

typedef char** huffmanCode;

void select(huffmanTree &hT, int i, int &s1, int &s2){
	int index = 1;
	int temp = hT[index].weight;
	while( index <=i){
		if(hT[index].parent == 0)
			break;
		index++;
	}
	s1 = index;
	for(int j = 1;j<=i;j++){
		if(hT[j].weight < hT[s1].weight && hT[j].parent == 0){
			s1 = j;
			j++;
		}
	}

	index = 1;
	temp = hT[index].weight;
	while( index <=i){
		if(hT[index].parent == 0 && index != s1)
			break;
		index++;
	}
	s2 = index;
	for(int j = 1;j<=i;j++){
		if(hT[j].weight < hT[s2].weight && j != s1 && hT[j].parent == 0){
			s2 = j;
			j++;
		}
	}
	int min, max;
	min = (s1 < s2)?s1:s2;
	max = (s1 > s2)?s1:s2;
	s1 = min;
	s2 = max;
}

void huffmancoding(huffmanTree &hT, huffmanCode &hC, int *w, int n){
	if (n<1) return ;
	int m = 2*n - 1;//number of nodes
	hT = new huffmanTreeNode [m+1];
	huffmanTree p;
	p = hT; 
	p++;
	
	for(int i = 1; i<=n; ++i,++p,++w){
		//*p = {*w, 0, 0, 0};
		p->weight = *w;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for(int i = n+1;i<=m;++i,++p){
		//*p = {0, 0, 0, 0};
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}

	//打印初始的huffman HT
	cout<<"Try to print the initial huffman Tree table."<<endl;

	for(int i = 1;i<=m;++i){
		cout<<hT[i].weight<<" "<<hT[i].parent<<" "<<hT[i].lchild<<" "<<hT[i].rchild<<endl;
	}
	int s1, s2;
	//构造huffman
	for(int i = n+1;i<=m;++i){
		select(hT, i-1, s1, s2);
		if (s1<0 || s2<0)
			cout<<"ERROR"<<endl;

		hT[s1].parent = i;
		hT[s2].parent = i;
		hT[i].lchild = s1;
		hT[i].rchild = s2;
		hT[i].weight = hT[s1].weight + hT[s2].weight;
	}

	//打印huffman
	cout<<"Try to print the created huffman Tree table."<<endl;
	for(int i = 1;i<=m;++i){
		cout<<hT[i].weight<<" "<<hT[i].parent<<" "<<hT[i].lchild<<" "<<hT[i].rchild<<endl;
	}

	hC = new char* [(m + 1)*sizeof(char*)];
	char *cd = new char [n*sizeof(char)];
	cd[n-1] = '\0';
	int start;
	int c , f;
	for(int i = 1; i<=n; i++){
		start = n-1;
		for(c = i,f = hT[i].parent; f!=0; c = f, f = hT[f].parent){
			if(hT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		}
		hC[i] = new char [(n-start)*sizeof(char)];
		strcpy(hC[i], &cd[start]);
	}
	delete []cd;
	//打印huffman编码
	cout<<"Try to print huffman code"<<endl;
	for(int i = 1; i <= n; i++){
		cout<<hC[i]<<endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int w[8] = {5,29,7,8,14,23,3,11};
	int n = 8;
	huffmanTree hT;
	huffmanCode hC;
	huffmancoding(hT, hC, w, n);

	system("pause");
	return 0;
}

