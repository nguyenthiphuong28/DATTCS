#include<stdio.h>
#include<math.h>

// a, giai thua n! (0 < n < 20)
long long GiaiThua(int n){
    if(n == 0 || n == 1) return 1;
    return n * GiaiThua(n -1);
}

// b, chuyen doi co so 10 sang 2
void ChuyenDoi(int n){
    if(n == 0) return;
    ChuyenDoi(n/2);
    printf("%d", n%2);
}

// c, Tinh so pell thu n
long long SoPell(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    return 2 * SoPell(n -1) + SoPell(n -2);
}

// d, tinh tong nghich dao s(n) = s(n-1) + 1/n
double TongNghichDao(int n){
    if(n == 1) return 1.0;
    return TongNghichDao(n -1) + 1.0/n;
}

//e, Tinh tong s(n) = 1^2 + 2^3 + 3^4 + ... + n^(n - 1)
long long luythua(int a, int b){
    if(b == 0) return 1;
    return a * luythua(a, b -1);
}
long long TongLuyThua(int n){
    if(n == 1) return 1;
    return TongLuyThua(n -1) + luythua(n, n -1);
}

//f, Uoc so lon nhat (euclid)
int UocSoLonNhat(int a, int b){
    if(b == 0) return a;
    return UocSoLonNhat(b, a % b);
}

// g, tinh tong giai thua S(n) = 1! + 2! + 3! + ... + n!
long long TongGiaiThua(int n){
    if(n == 1) return 1;
    return TongGiaiThua(n -1) + GiaiThua(n);
}

// h, tinh tong n so fibonacci dau tien 
long long Fibonacci(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    return Fibonacci(n -1) + Fibonacci(n -2);
}
long long TongFibonacci(int n){
    if(n == 0) return 0;
    return TongFibonacci(n -1) + Fibonacci(n);
}

//i, tinh tong s(n) = 1/2 + 2/3 + 3/4 + ... + n/(n+1)
double TongPhanSo(int n){
    if(n == 1) return 1.0/2;
    return TongPhanSo(n -1) + (double)n/(n +1);
}

// j, tinh tong s(n) = 1x2 + 2x3 + 3x4 + ... + nx(n+1)
long long TongTich(int n){
    if(n == 1) return 2;
    return TongTich(n -1) + n * (n +1);
}

int main(){
    int n;
    printf("Nhap n (0 < n < 20): ");
    scanf("%d", &n);
    printf("Gia thua %d! = %lld\n", n, GiaiThua(n));

    printf("Doi %d sang nhi phan: ", n);
    if(n == 0) printf ("0");
    else ChuyenDoi(n);
    printf("\n");
    printf("So Pell thu %d la: %lld\n", n, SoPell(n));
    printf("Tong nghich dao S(%d) = %.6f\n", n, TongNghichDao(n));
    printf("Tong luy thua S(%d) = %lld\n", n, TongLuyThua(n));
    printf("Nhap hai so a, b de tinh Uoc so lon nhat: ");
    int a, b;
    scanf("%d%d", &a, &b);
    printf("Uoc so lon nhat cua %d va %d la: %d\n", a, b, UocSoLonNhat(a, b));
    printf("Tong giai thua S(%d) = %lld\n", n, TongGiaiThua(n));
    printf("Tong %d so Fibonacci dau tien = %lld\n", n, TongFibonacci(n));
    printf("Tong phan so S(%d) = %.6f\n", n, TongPhanSo(n));
    printf("Tong tich S(%d) = %lld\n", n, TongTich(n));
    return 0;
}