/*
Viết hàm đệ quy thực hiện các yêu cầu:
a) Tính tổng các số chẵn từ 2 đến n: S = 2 + 4 + 6 +⋯+ n (2 ≤ n < 500, n chẵn);
b) Tính tổng các chữ số của số nguyên n (1000 ≤ n < 1000000);
Ví dụ: n = 1234 → tổng là 1 + 2 + 3 + 4 = 10
c) Tính tổng dãy số hình học: S = a + a*r + a*r2 +⋯+ a*rn (2 ≤ n < 10)
d) Tính tổng các số chia hết cho 3 từ 1 đến n (2 ≤ n < 500)
e) Tính tổng biểu thức phân số: S=1/1 + 1/2 + 1/3 +⋯+ 1/n (2 ≤ n < 50)
f) Hàm main() gọi các hàm trên thực hiện để kiểm tra kết quả.


a,đk dừng n == 0;
    đệ quy s(n) = s(n-2) +n
b, đk dừng (n = 0 => 0 hoặc  n < 10 => n)
    đệ quy s(n) = s(n/10)+n %10
c, đệ quy S(a,n,r) = S(a,r,n-1) + pow(r,n)
    đk dừng (n == 0 => a)
d, đk dừng (n < 3 -> 0)
    đệ quy -nếu n %3 ==0 -> S(n-1) +n
            - ngược lại => S(n-1)
*/

#include<stdio.h>
#include <math.h>

// a, tính tổng chẵn
int TongChan(int n){
    if (n == 0)
        return 0;
    else
        return TongChan(n -2) + n;
}

// b, tong cac chu so nguyen
int TongChuSo(int n){
    if (n == 0)
        return 0;
    else
        return TongChuSo(n/10) + n %10;
}

//c, tong day so hinh hoc
int TongHH(int a, int n, int r){
    if(n == 0)
        return a;
    else
        return TongHH(a,r,n-1) + pow(r,n);
}

// d, tong so chi het cho3
int TongChia3(int n){
    if(n < 3)
        return 0;
    if( n % 3 == 0)
        return TongChia3(n-1) + n;
    else 
        return TongChia3(n-1);
}

// e, TongPS
double TongPS(int n){
    if(n == 1)
        return 1.0;
    else
        return 1.0/n + TongPS(n-1);
}

// ham chinh
int main(){
    int n;
    int a;
    int r;
    // a
    do{
        printf("Nhap n la so chan: ");
        scanf("%d", &n);
    }while(n < 2 || n >= 500 || n%2 != 0);
    printf("Tong cac so chan %d\n", TongChan(n));

    //b 
    printf("Tong cac chu so trong n %d\n", TongChuSo(n));
    // c 
    printf("Tong day so hinh hoc %d\n", TongHH(a,n,r));
    //d 
    printf("Tong so chia het cho 3 %d\n", TongChia3(n));
    // e 
    printf("Tong bieu thuc phan so %2f\n", TongPS(n));
}