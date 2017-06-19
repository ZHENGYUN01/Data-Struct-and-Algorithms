// Index.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int index(string source, string sub, int pos){
	char *ptrSource = &source[0];
	char *ptrSub = &sub[0];

	int len_source = source.length();
	int len_sub = sub.length();

	int i = pos, j = 1;
	while(i <= len_source && j<= len_sub){
		if(*(ptrSource + i - 1) == *(ptrSub + j - 1))
		{
			i++;
			j++;
		}
		else{
			i = i - j + 2;//i = (i - (j - 1) + 1)
			j = 1;
		}
	}
	if(j > len_sub)
		return (i - len_sub);
	else
		return 0;
}

void getNext(string sub, int next[]){
	int i = 1;
	next[0] = 0;
	int j = 0;
	char *p = &sub[0];
	int len_sub = sub.length();

	while (i < len_sub){
		if(j == 0 || *(p + i - 1) == *(p + j - 1)){
			++i;
			++j;
			next[i-1] = j;
		}
		else
			j = next[j-1];
	}

}

int KMP(string source, string sub, int pos){
	char *ptrSource = &source[0];
	char *ptrSub = &sub[0];
	
	int len_source = source.length();
	int len_sub = sub.length();
	
	int *next = new int [len_sub];
	if(!next) exit(-1);

	getNext(sub, next);

	int i = pos, j = 1;

	while(i <= len_source && j <= len_sub){
		if(j == 0 || *(ptrSource + i - 1) == *(ptrSub + j - 1)){
			i++;
			j++;
		}
		else{
			j = next[j-1];
		}
	}
	if (j > len_sub) return (i - len_sub);
	else return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string source = "acabaabaabcacaabc";
	string sub = "abaabcac";
	int pos = 2;
	cout<<index(source, sub, pos)<<endl;

	int pos2 = KMP(source, sub, pos);
	cout<<pos2<<endl;
	system("pause");
	return 0;
}

