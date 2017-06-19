// sqString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

typedef int Status;

Status Substring(string source, string &sub , int i , int m){
	int length = source.length();
	char *p = &source[0];
	p = p + i - 1;
	char *q = p;
	int temp = m;

	if(m > length || i > length)
		return -1;
	while(m){
		*(q++) = *(p++);
		m--;
	}
	*(q) = '\0';
	sub = q - temp;
	return 1;
}

Status StrCompare(string sub, string S){
	if(S.compare(sub) != 0)
		return 1;
	else
		return 0;
}

int Index(string S, string T, int pos){
	//pos: starts from 1 rather than 0.
	if(pos > 0){
		int n = S.length();
		int  m = T.length();
		int i = pos;
		while(i <= n-m+1){
			string sub;
			Substring(S, sub, i, m);
			if(StrCompare(sub, T) != 0)
				++i;
			else
				return i;
		}
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{

	string source = "IliveinHunan";
	string subString = "inHunan";
	int pos = 2;

	cout<<"Try to locate substring location..."<<endl;
	int index = Index(source, subString, pos);
	cout<<index<<endl;

	system("pause");
	return 0;
}

