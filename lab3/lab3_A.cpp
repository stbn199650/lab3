#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>
//#include<iomanip>
#include"lab3_A.h"
using namespace std;

void vec::fileIn(){ 

	vc.clear();
	vc.resize(9);
	ifstream inFile("file.in",ios::in);
	while(!inFile){
		cout<<"open file error"<<endl;
		exit(1);
	}
	inFile>>amount;
	for(int i=0;i<amount;i++){
		inFile>>vc[i];
	}
}
void vec::sort(){

	int j,temp,total=0;

	for(int i=1;i<amount;i++){
		temp=vc[i];
		j=i-1;
		while(j>-1 && temp<vc[j]){
			vc[j+1]=vc[j];
			j--;
		}
		vc[j+1]=temp;
	}
	for(int i=amount-1;i>amount-6;i--){
		total+=vc[i];
	}
	cout<<total<<endl;
}
