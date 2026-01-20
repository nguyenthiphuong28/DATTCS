#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 30
#define FILE_NAME "DaySo.inp"
//a, Tao day so nguyen [0,1000] va ghi vao file
void ghiFile(){
    FILE *f = fopen(FILE_NAME, "w");
    if (f != NULL){ // 
        int n;
        do{
            printf ("Nhap so luong phan tu n (2 <= n <= 30): ");
            scanf ("%d", &n);
        }while(n < 2 || n > 30);  // nên để n >= 2 thay vì n > 2

        fprintf (f, "%d\n", n); // ghi n vào file

        srand(time(NULL)); // khởi tạo bộ sinh số ngẫu nhiên
        for (int i = 0; i < n; i++){
            int x = rand() % 1001; // số ngẫu nhiên [0,1000]
            fprintf (f, "%d ", x);
        }

        fclose(f);
        printf ("Ghi file thanh cong!\n");
    }
    else {
        printf ("Khong the mo file\n");
    }
}
//b, doc so nguyen tu file vao chuong trinh
void docFile(int a[], int &n){
    FILE *f = fopen(FILE_NAME, "r");
    if (f != NULL){
        fscanf (f, "%d", &n); // doc n tu file
        for (int i = 0; i < n; i++){
            fscanf (f, "%d", &a[i]); // doc tung phan tu vao mang
        }
        fclose(f);
        printf ("Doc file thanh cong!\n");
    }else{
        printf ("Khong the mo file\n");
    }
}
//c, in day so
void  inDaySo(int a[], int n){
    printf ("Day so nguyen doc tu file:\n");
    for (int i = 0; i < n; i++){
        printf ("%d ", a[i]);
    }
    printf ("\n");
}
//d, tinh tong so nguyen duong chan trong day so
int TongSoNguyenDuongChan(int a[], int n){
    int tong = 0;
    for (int i = 0; i < n; i++){
        if (a[i] > 0 && a[i] % 2 == 0){
            tong += a[i];
        }
    }
    printf ("Tong cac so nguyen duong chan trong day so: %d\n", tong);
    return tong;
}

int main(){
    int n;
    int a[MAX];
    ghiFile();
    docFile(a, n);
    inDaySo(a, n);
    TongSoNguyenDuongChan(a, n);
    return 0;
}