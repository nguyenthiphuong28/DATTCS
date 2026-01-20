//bai 5.3
#include<stdio.h>
#define N 20

int DocFile(int w[], int &n, int &m);
void XuatDS(int w[], int n, int m);
void SapXep(int w[], int n);
void XuatNghiem(int w[],int n, int x[],int m,int c);
void Can(int w[],int n,int x[],int m,int c); //so qua can han che

int main(){
	int w[N], n, m;
	int x[N];//luu cac thanh phan nghiem
	
	if (DocFile(w,n,m)){
		XuatDS(w,n,m);
		SapXep(w,n);
		for(int i=0;i<n;i++)
			x[i] = 0;					
		Can(w,n,x,m,0);
	}
	else
		printf("Loi mo file!");		
}
//Doc dl tu file vao chuong trinh
int DocFile(int w[], int &n, int &m){
	FILE* f=fopen("CAN.inp","r");
	if(f==NULL){
		printf("Err!"); return 0;
	}		
	else{
		int i;
		fscanf(f,"%d",&n);//so n
		fscanf(f,"%d",&m);//khoi luong vat 
		for(i=0;i<n;i++)
			fscanf(f,"%d",&w[i]);
		fclose(f);
		return 1;
	}
}
//xuat day so
void XuatDS(int w[], int n, int m){
	int i;
	printf("Khoi luong vat can m: %d\nCac qua can:",m);
	for(i=0;i<n;i++)
		printf("%8d",w[i]);
	printf("\n");
}
// Sap xep giam dan
void SapXep(int w[], int n) {
	int tmp;
    for (int i = 0; i < n - 1; i++) 
        for (int j = i+1; j < n ; j++) 
            if (w[i] < w[j]) {               
                tmp = w[i];
                w[i] = w[j];
                w[j] = tmp;
            }    
}
//xuat ra m�n h�nh
void XuatNghiem(int w[],int n, int x[],int m,int c){
	printf("Vat can %d \n",m);
	printf("Cach chon cac qua can gom %d qua:\n",c);
	for(int i=0;i<n;i++)
		if(x[i]!=0)
			printf("%d:%d\t",i,w[i]);	
}
// Tham lam tim nghiem
void Can(int w[],int n,int x[],int m,int c){
	int i=0; 
	int m1=m; //s1 so tien con lai
	while(i<n && m1>0){
		if(m1>=w[i]){  //chon qua can lon nhat
			x[i] = 1;
			m1 -= w[i];
			c +=x[i];
		}
		i++;
	}
	if(m1==0)
		XuatNghiem(w,n,x,m,c);
	else
		printf("khong can duoc");
}

