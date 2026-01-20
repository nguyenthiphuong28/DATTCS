/*
Bài 4.1 Dùng kỹ thuật quay lui để thực hiện in ra màn hình tất cả các chuỗi nhị phân có độ
dài n, với n nhập vào từ bàn phím (0 < n ≤ 10)

*/
#include <stdio.h>
#define N 10

void Print(int x[], int n){
    for (int j = 1; j <= n; j++)
        printf("%d", x[j]);
    printf("\n");
}

// cach 1
void Try_1(int i, int x[], int n){
    for(int j = 0; j <= 1; j++)
    {
        x[i] = j;
        if (i == n)
            Print(x,n);
        else
            Try_1(i + 1, x, n);
    }
}

// cach 2
void Try_2(int i, int x[], int n){
    if(i == n + 1) { Print(x,n); return;}

    x[i] = 0; Try_2(i + 1, x,n);
    x[i] = 1; Try_2(i + 1, x, n);
}

// ham main
int main(){
    int x[N]; // luu ket qua
    int n;
    printf("Nhap vap do dai chuoi nhi phan: ");
    scanf("%d", &n);
    printf("Cach 1:\n");
    Try_1(1, x, n);
    printf("Cach 2:\n");
    Try_2(1, x, n);
}
