#include<iostream>
#include<cstdlib>
#include<ctime>
#include"Sudoku.h"
using namespace std;
int add=0;
void Sudoku::giveQuestion(){
	
	int n;
	int hole[55];
	int in[82]={8,4,2,1,3,5,6,7,9,6,1,9,2,7,8,4,3,5,
		7,3,5,4,6,9,1,8,2,1,2,4,6,5,7,8,9,3,5,7,8,3,9,4,2,6,1,
		3,9,6,8,2,1,5,4,7,4,5,1,7,8,3,9,2,6,2,8,3,9,1,6,7,5,4,
		9,6,7,5,4,2,3,1,8};

	srand(time(NULL));
	n=rand()%11+40;		//the amounts of the hole
	for(int i=0;i<n;i++){
		hole[i]=rand()%81;		//decide which number of the hole is 0
		for(int j=0;j<i;j++){
			if(hole[i]==hole[j]){i--;break;}	//if the number same,reproduce
		}
	}
	for(int i=0;i<n;i++){	//dig hole
		in[hole[i]]=0;
	}
	for(int i=0;i<81;i++){
		cout << in[i];
		(i%9)==8?cout<<endl:cout<<' ';
	}
}
void Sudoku::readIn(){
	for(int i=0;i<81;i++){cin>>in[i];}
}
void Sudoku::solve1(){
	int check=0;
	
	for(int i=0;i<81;i++){
		if(in[i]==0){
			check++;
		}
	}
	if(check==0){
		add++;
		if(add>=2){
			cout<<"2"<<endl;
			return;
		}
		return;
	}
	for(int i=0;i<81;i++){
		if(in[i]==0){
			for(int k=1;k<10;k++){
				in[i]=k;
				if(checkRow(i,k)==1 && checkCol(i,k)==1 && checkBlock(i,k)==1){
					in[i]=k;
					solve1();
					in[i]=0;
				}
			}
			if(add==2)return;
		}
		return;
	}
}
void Sudoku::solve(){
	int check=0,add=0,count=0;	//add:填到第幾格
	int re[82]={0};	//計算這格一次迴圈填了幾次
	int last[82]={0};
	int arr[81][200]={0};
	for(int i=0;i<81;i++){map[i]=in[i];}
	for(int i=0;i<81;i++){out[i]=0;}
	solve1();
	if(add==2){goto print;}
	if(out[0]==0){
		cout<<"0"<<endl;
	}
print:
	if(add==1){
		cout<<"1"<<endl;
		for(int i=0;i<81;i++){
			cout<<in[i];
			(i%9)==8?cout<<endl:cout<<' ';
		}
	}
}
/*	for(int i=0;i<81;i++){
		if(map[i]==0){
			for(int k=last[i]+1;k<10;k++){
				re[i]++;
				cout<<"i="<<i<<"k="<<k;
				if(checkRow(i,k)==1 && checkCol(i,k)==1 && checkBlock(i,k)==1){
					in[i]=k;	//條件符合才會把數字填進去
					add++;
					cout<<"succeed";
					re[i]=0;
					if(k==9)last[i]=0;	//k==9，下次從1開始填
					else last[i]=k;
					break;
				}
				if(in[i]!=0 && k==9){
					i=findzero(i);
					break;
				}
			cout<<"checkRow="<<checkRow(i,k);
			cout<<"checkCol="<<checkCol(i,k);
			cout<<"checkBlock="<<checkBlock(i,k)<<endl;
				if(k==9 && add==0){	//無解條件
					cout<<"0"<<endl;
					exit(0);
				}
				if(k==9){
					in[i]=0;
					for(int j=1;j<=i;j++){
						if(map[i-j]==0){i-=j;break;}	//回到上一個原本是0的地方
					}
					i--;	//因為for會再+1
					break;
				}
				if(k==9 && re[i]<8){
					last[i]=0;	//不是從1開始填，填到9都不行，再回到1開始填
					i--;
					add--;
					break;
				}
				if((in[i]!=0 && re[i]==8) || (in[i]==0 && re[i]==9)){
					re[i]=0;	//從1開始填，填到9都不行，回上一格填
					i=findzero(i);
					break;
				}
			}
		}
		if(i==80 && in[i]!=0)count++;
	}
}*/
int Sudoku::findzero(int n){
	for(int j=1;j<=n;j++){
		if(map[n-j]==0){n-=j;break;}	//回到上一個原本是0的地方
	}
	n--;	//因為for會再+1
	return n;
}
int Sudoku::checkRow(int num,int n){	//num:第幾個  n:1~9
	int k=num/9,row=9*k;
	for(int i=0;i<9;i++){
		if((in[row+i]==n) && ((row+i)!=num))
			return 0;
	}
	return 1;
}
int Sudoku::checkCol(int num,int n){
	int col=num%9,k;
	for(int i=0;i<9;i++){
		k=i*9+col;
		if((in[k]==n) && (k!=num))
			return 0;
	}
	return 1;
}
int Sudoku::checkBlock(int num,int n){
	int row=num/9,col=num%9;
	int k,l,m,p;
	if(row<=2){l=0;}
	else if(row<=5){l=1;}
	else{l=2;}

	if(col<=2){m=0;}
	else if(col<=5){m=1;}
	else{m=2;}

	k=27*l+3*m;	//block 左上角的數字
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			p=k+9*i+j;
			if(in[p]==n && p!=num){
				return 0;
			}
		}
	}
	return 1;
}
void Sudoku::changeNum(int a,int b){
	int x,y;
	for(int i=0;i<81;i+=9){		//remember the array address to exchange
		for(int j=0;j<9;j++){
			if(in[i+j]==a){x=i+j;}
			if(in[i+j]==b){y=i+j;}
		}
		swap(in[x],in[y]);
	}
}
void Sudoku::changeRow(int a,int b){
	int temp;
	int x=27*a,y=27*b;
	if(a != b){
		for(int i=x;i<x+27;i++){
			temp=in[i];
			in[i]=in[y];
			in[y]=temp;
			y++;
		}
	}
}
void Sudoku::changeCol(int a,int b){
	int temp;
	if(a != b){
		for(int i=a;i<81;i+=9){
			temp=in[i];
			in[i]=in[b];
			in[b]=temp;
			b+=9;
		}
	}
}
void Sudoku::rotate(int n){

	int k,m;
	if(n%4 == 1){
		for(int i=0;i<81;i++){
			m=i/9;
			if(m == 0){k=9*(i+1)-1;  fp[k]=in[i];}
			else if(m == 1){k=9*(i-8)-2;  fp[k]=in[i];}
			else if(m == 2){k=9*(i-17)-3; fp[k]=in[i];}
			else if(m == 3){k=9*(i-26)-4; fp[k]=in[i];}
			else if(m == 4){k=9*(i-35)-5; fp[k]=in[i];}
			else if(m == 5){k=9*(i-44)-6; fp[k]=in[i];}
			else if(m == 6){k=9*(i-53)-7; fp[k]=in[i];}
			else if(m == 7){k=9*(i-62)-8; fp[k]=in[i];}
			else if(m == 8){k=9*(i-72);   fp[k]=in[i];}
		}
	}
	else if(n%4 == 2){
		for(int i=0;i<81;i++){
			fp[i]=in[80-i];
		}
	}
	else if(n%4 == 3){
		for(int i=0;i<81;i++){
			if(i/9 == 0){fp[72-i*9]=in[i];}
			if(i/9 == 1){fp[154-i*9]=in[i];}
			if(i/9 == 2){fp[236-i*9]=in[i];}
			if(i/9 == 3){fp[318-i*9]=in[i];}
			if(i/9 == 4){fp[400-i*9]=in[i];}
			if(i/9 == 5){fp[482-i*9]=in[i];}
			if(i/9 == 6){fp[564-i*9]=in[i];}
			if(i/9 == 7){fp[646-i*9]=in[i];}
			if(i/9 == 8){fp[728-i*9]=in[i];}
		}
	}
	for(int i=0;i<81;i++){in[i]=fp[i];}
}
void Sudoku::flip(int n){

	int k;
	if(n==0){
		for(int i=0;i<81;i++){
			if(i/9 == 0){k=9*(i+1)-1;  fp[k]=in[i];}
			else if(i/9 == 1){k=9*(i-8)-2;  fp[k]=in[i];}
			else if(i/9 == 2){k=9*(i-17)-3; fp[k]=in[i];}
			else if(i/9 == 3){k=9*(i-26)-4; fp[k]=in[i];}
			else if(i/9 == 4){k=9*(i-35)-5; fp[k]=in[i];}
			else if(i/9 == 5){k=9*(i-44)-6; fp[k]=in[i];}
			else if(i/9 == 6){k=9*(i-53)-7; fp[k]=in[i];}
			else if(i/9 == 7){k=9*(i-62)-8; fp[k]=in[i];}
			else if(i/9 == 8){k=9*(i-72);   fp[k]=in[i];}
		}
	}
	if(n == 1){
		for(int i=0;i<81;i++){
			if(i%9 == 0){fp[i+8]=in[i];}
			if(i%9 == 1){fp[i+6]=in[i];}
			if(i%9 == 2){fp[i+4]=in[i];}
			if(i%9 == 3){fp[i+2]=in[i];}
			if(i%9 == 4){fp[i] = in[i];}
			if(i%9 == 5){fp[i-2]=in[i];}
			if(i%9 == 6){fp[i-4]=in[i];}
			if(i%9 == 7){fp[i-6]=in[i];}
			if(i%9 == 8){fp[i-8]=in[i];}
		}
	}
	for(int i=0;i<81;i++){in[i]=fp[i];}
}
void Sudoku::transform(){
	readIn();
	change();
	printOut();
}
void Sudoku::change(){
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
}
void Sudoku::printOut(){
	for(int i=0;i<81;i++){
		cout << in[i];
		(i%9)==8?cout<<endl:cout<<' ';
	}
}
