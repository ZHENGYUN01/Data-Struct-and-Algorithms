// DFSForest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


void DFSForest(Graph G, CSTree &T){

	T = NULL;
	for(int v = 0; v<G.vexNum; ++v){
		visited[v] = FALSE;
	}
	
	for(int v = 0; v<G.vexNum; ++v){
		if(!visited[v]){
			p = new CSTree[1];
			//¸øp¸³Öµ
			*p = 1;
			if(!T) T = p;
			else
				q->nextsibling = p;
			q = p;
			DFSTree(G, v, p);
		}
	}
}

void DFSTree(Graph G, int v, CSTree &T){
	visited[v] = TRUE;
	first = TRUE;
	for(int w = FirstAdjVex(G,v); w >= 0; w = NextAdjVex(G, v, w)){
		if(!visited[w]){
			p = new CSTree[1];
			//¸³Öµ
			*p = 1;
			if(first){
				T->lchild = p;
				first = FALSE;
			}
			else{
				q->nextsibling = p;
			}
			q = p;
			DFSTree(G, w, q);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	system("pause");
	return 0;
}

