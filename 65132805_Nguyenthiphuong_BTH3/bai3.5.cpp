#include<stdio.h>
// a, Doc noi dung file "Dayso.35.inp" ra mang a
int DocFile(double a[], int *n){
    FILE *f = fopen("Dayso35.inp", "r");
    if(f == NULL){
        printf("Khong mo duoc file\n");
        return 0;
    }
    fscanf(f, "%d", n);
    for(int i = 0; i < *n; i++){
        fscanf(f, "%lf", &a[i]);
    }
    fclose(f);
    return 1;
}

//b, Xuat mang
void XuatMang(double a[], int n){
    printf("Mang vua doc: ");
    for(int i = 0; i < n; i++){
        printf("%.2lf ", a[i]);
    }
    printf("\n");
}

//c, dung vong lap 
double MinFor(double a[], int n){
    double min = a[0];
    for(int i = 1; i < n; i++){
        if(a[i] < min)
            min = a[i];
    }
    return min;
}

//c, Tim so nho nhat de quy
double MinDe(double a[], int n){
    if(n == 1) return a[0];
    double min = MinDe(a, n-1);
    return (a[n -1] < min) ? a[n -1] : min;
}

// d, Tinh tong bang de quy dau
double TongDeDau(double a[], int n){
    if(n == 0) return 0;
    return a[n -1] + TongDeDau(a, n-1);
}

// d, Tinh tong de quy duoi
double TongDeDuoi(double a[], int n){
    if(n == 0) return 0;
    return a[n -1] +TongDeDau(a, n -1);
}

int main(){
    double a[50];
    int n;
    if(!DocFile(a,&n)) return 1;
    XuatMang(a, n);

    printf("So nho nhat dung vong lap: %.2lf\n", MinFor(a,n));
    printf("So nho nhat dung de quy: %.2f\n", MinDe(a,n));
    printf("Tong de quy dau: %.2lf\n", TongDeDau(a,n));
    printf("Tong de quy duoi: %.2lf\n", TongDeDuoi(a,n));
}
