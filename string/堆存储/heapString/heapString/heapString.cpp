// heapString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#pragma pack(1)

using namespace std;

typedef struct{
	char *ch;
	int length;
}heapString;

typedef int Status;

ostream& operator <<(ostream& output, heapString &S){
	output<<S.ch<<endl;
	return output;
}

istream& operator >>(istream& input, heapString &S){
	input>>S.ch;
	return input;
}

Status strInsert(heapString &S, int pos, heapString T){
	if(T.length){
		char* newbase = new char [(S.length + T.length) * sizeof(char)];

		if(!newbase) exit(-1);
		//memcpy(newbase, S.ch, S.length * sizeof(char));
		strcpy(newbase, S.ch);

		S.ch = newbase;
		S.length += T.length;

		for(int i = S.length - 1;i>= pos -1; --i){
			S.ch[i + T.length] = S.ch[i];
		}
		for(int j = 0;j <= T.length - 1; j++){
			S.ch[pos - 1 + j] = T.ch[j];
		}
	}
	return 1;
}

Status initHeapString(heapString &S, char *ch = NULL){
	if(ch){
		S.ch = ch;
		S.length = strlen(ch);
	}
	else{
		S.ch = NULL;
		S.length = 0;
	}
	return 1;
}

Status destroyHeapString(heapString &S){
	if(S.ch){
		delete []S.ch;
		S.ch = NULL;
	}
	return 1;
}

Status contactTwoHeapString(heapString &T, heapString S1, heapString S2){
	char* newbase = new char [(S1.length + S2.length) * sizeof(char)];
	if(!newbase) exit(-1);
	
	strcpy(newbase, S1.ch);

	T.length = S1.length + S2.length;
	T.ch = newbase;

	strcpy(T.ch + S1.length, S2.ch);

	return 1;
}

Status subHeapString(heapString &Sub, heapString S, int pos, int len){
	if(pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1) exit(-1);

	char* newbase = new char [(len + 1) * sizeof(char)];
	if(!newbase) exit(-1);

	Sub.ch = newbase;	

	if(len){
		int i = 0;
		for( ; i < len; i++)
			Sub.ch[i] = S.ch[pos - 1 + i];
		Sub.ch[++i] = '\0';
		Sub.length = strlen(Sub.ch);
	}
	else{
		Sub.ch = NULL;
		Sub.length = 0;
	}
		return 1;

}

int _tmain(int argc, _TCHAR* argv[])
{
	heapString T;
	char *ch2 = "zy";
	initHeapString(T,ch2);

	for (int i = 1;i<= 6; i++){
		heapString S;
		char *ch1 = "hello";
		initHeapString(S,ch1);
		cout<<"Try to insert a string into "<<i<<"-th position of target string"<<endl;
		strInsert(S, i, T);
		cout<<S<<endl;
	}
	
	cout<<"Try to contact two heapString (S1 and S2) into a long heapString"<<endl;
	heapString longheap;
	initHeapString(longheap, NULL);

	heapString S1;
	initHeapString(S1, "zy");

	heapString S2;
	initHeapString(S2, " hello");
	contactTwoHeapString(longheap, S1, S2);
	cout<<longheap<<endl;

	cout<<"Try to get a sub-string of heapString..."<<endl;
	heapString Sub;
	initHeapString(Sub, NULL);
	int pos = 4;
	int len = 5;
	heapString S3;
	initHeapString(S3, "ChinaEnglish");

	subHeapString(Sub, S3, pos, len);
	cout<<Sub<<endl;

	system("pause");
	return 0;
}

