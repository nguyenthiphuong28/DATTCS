#include<stdio.h>
#include<stdbool.h>

#define MAX 50
// a, Nhập dãy số nguyên
void Nhapmang(int a[], int *n){
    do{
        printf ("Nhap so luong phan tu n (3 < n < 50):");
        scanf ("%d", n);
    }while(*n <= 3 || *n >= MAX);
    for (int i = 0; i < *n; i++){
        printf ("Nhap a[%d]: ", i);
        scanf ("%d", &a[i]);
    }
}
// b, tim so am dau tien trong day so, neu co in ra vi tri va gia tri(dung ki thuat linh canh)
void Timsoam(int a[], int n){// ky thuat linh canh
    a[n] = -1; // linh canh
    int i = 0;
    while (a[i] >= 0) i++;
    if (i == n){
        printf ("khong co so am nao trong mang\n");
    }else{
        printf ("So am dau tien: %d tai vi tri %d\n", a[i], i);
    }
}
// c, Kiem tra cos phan tu x nao trong mang hay khong(dun ky thuat linh canh)
void KiemTraGiaTriX(int a[],int n,int x){
    a[n] = x; // linh canh
    int i = 0;
    while (a[i] != x) i++;
    if (i == n){
        printf ("Khong co phan tu x nao trong mang\n");
    }else{
        printf ("Co phan tu x trong mang tai vi tri %d\n", i);
    }
}
//d, su dung ky thuat co hiru de kien tra day so co giam dan hay khong
 int KiemTraGiamDan(int a[], int n){
    int flag = 1; // mac dinh la giam dan
    for (int i = 0; i < n - 1; i++){
        if (a[i] < a[i + 1]){
            flag = 0; // khong phai giam dan
            break;
        }
    }
    return flag;
}
 //e, su dung ky thuat co hieu de kiem tra day so co hoan toan la so nguyen duong khong
 int KiemTraNguyenDuong(int a[], int n){
    int flag = 1; // mac dinh la so nguyen duong
    for (int i = 0; i < n; i++){
        if (a[i] < 0){
            flag = 0; // khong phai so nguyen duong
            break;
        }
    }
    return flag;
}


int main(){
    int n;
    int a[MAX + 1];
    int x;
    Nhapmang(a, &n);
    Timsoam(a, n);
    KiemTraGiaTriX(a, n, x);
    // kiem tra giam dan
    if (KiemTraGiamDan(a,n))
        printf ("Day so giam dan\n");
    else
        printf ("Day so khong giam dan\n");
    
    // kiem tra so nguyen duong
    if (KiemTraNguyenDuong(a,n))
        printf ("Day so toan la so nguyen duong\n");
    else
        printf ("Day so khong phai toan la so nguyen duong\n");
    
    return 0;
}