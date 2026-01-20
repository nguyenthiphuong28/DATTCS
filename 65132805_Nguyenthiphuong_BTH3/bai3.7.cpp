#include<stdio.h>
#include<math.h>
// a, Nhap day so thuc bang de quy 
void NhapDaySo(double a[], int n){
    if(n == 0) return;
    NhapDaySo(a, n -1);
    printf("Nhap a[%d]: ", n -1);
    scanf("%lf", &a[n -1]);
}

//b, Tinh tong cac phan tu o vi tri le (tuc la a[1], a[3], a[5], ...)
double TongViTriLe(double a[], int n){
    if(n == 0) return 0.0;
    if((n -1) % 2 == 1)
        return TongViTriLe(a, n -1) + a[n -1];
    else
        return TongViTriLe(a, n -1);
}

// c, tinh tich cac phan tu trong day
double TichDaySo(double a[], int n){
    if(n == 0) return 1.0;
    return TichDaySo(a, n -1) * a[n -1];
}

//d, dem so phan tu lon hon gia tri x cho truoc
int DemSoPhanTuLonHonX(double a[], int n, double x){
    if(n == 0) return 0;
    if(a[n -1] > x)
        return DemSoPhanTuLonHonX(a, n -1, x) + 1;
    else
        return DemSoPhanTuLonHonX(a, n -1, x);
}

//e, kiem tra day so co toan duong khong
bool KiemTraDaySoToanDuong(double a[], int n){
    if(n == 0) return 1;
    if(a[n -1] <= 0) return 0;
    return KiemTraDaySoToanDuong(a, n -1);
}


// f, ham main
int main(){
    int n;
    printf("Nhap so luong phan tu cua day so: ");
    scanf("%d", &n);
    double a[n];
    NhapDaySo(a, n);
    printf("Tong cac phan tu o vi tri le: %.2f\n", TongViTriLe(a, n));
    printf("Tich cac phan tu trong day: %.2f\n", TichDaySo(a, n));
    double x;
    printf("Nhap gia tri x de dem so phan tu lon hon x: ");
    scanf("%lf", &x);
    printf("So phan tu lon hon %.2f la: %d\n", x, DemSoPhanTuLonHonX(a, n, x));
    if(KiemTraDaySoToanDuong(a, n))
        printf("Day so toan duong\n");
    else
        printf("Day so khong toan duong\n");
    return 0;
}