//phan tich so
#include<stdio.h>
#define MAX 50

//xuat nghiem
void xuatNghiem(int k, int x[], int n){
	for(int i=1;i<=k;i++)
		if (i!=k)
			printf("%d + ",x[i]);
		else
			printf("%d ",x[i]);
	printf("\n");	
}
//
void phanTichSo(int i,int x[],int n, int s[]){
	for(int j=x[i-1];j<=n-s[i-1];j++){
		x[i]=j;	
		s[i] = s[i-1]+j;
		if(s[i]==n)//x[i]==n-s[i-1]) 
			xuatNghiem(i,x,n);	
		else 
			phanTichSo(i+1,x,n,s);		
	}
}
//
int main(){
	int x[MAX],s[MAX];//x luu nghiem, s luu tong
	int n;
	printf("so n:");
	scanf("%d",&n);
	
	x[0]=1;s[0]=0; //khoi tao
	phanTichSo(1,x,n,s);
	return 0;
}
