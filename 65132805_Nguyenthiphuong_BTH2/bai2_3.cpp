#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 20
#define FILE_INPUT "Matran.inp"
#define FILE_OUTPUT "KetQua.out"
void ghiFile(){
    FILE *f = fopen(FILE_INPUT, "w");
    if(f != NULL){
        //nhap ma tran nxn
        int n,m;
        do{
            printf ("Nhap so dong n (2 <= n <= 20): ");
            scanf ("%d", &n);
        }while(n < 2 || n > 20);
        fprintf (f, "%d\n", n);// ghi n vao file

        printf ("Nhap cac phan tu ma tran:\n");
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                printf ("A[%d][%d]: ", i, j);
                scanf ("%d", &m);
                fprintf (f, "6%d ", m);// ghi phan tu vao file
            }
            fprintf (f, "\n");
        }
        fclose(f);
        printf ("Ghi file thanh cong!\n");
    }
    else 
        printf ("Khong the mo file\n");
}
// doc ma tran tu file vao chuong trinh
int docFile(int A[MAX][MAX], int *n) {
    FILE *f = fopen(FILE_INPUT, "r");
    if (f != NULL) {
        fscanf(f, "%d", n); // đọc n từ file
        for (int i = 0; i < *n; i++) {
            for (int j = 0; j < *n; j++) {
                fscanf(f, "%d", &A[i][j]);
            }
        }
        fclose(f);
        return 1;
    } else {
        printf(" Khong the mo file\n");
        return 0;
    }
}
// xuat ma tran
void xuatMaTran(int A[MAX][MAX], int n) {
    printf("Ma tran:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5d ", A[i][j]);
        }
        printf("\n");
    }
}
// tinh tong so nam tren duong cheo
int TongDuongCheoChinh(int A[MAX][MAX], int n) {
    int tong = 0;
    for (int i = 0; i < n; i++) 
        tong += A[i][i];
    FILE *f = fopen(FILE_OUTPUT, "w");
    if (f !=NULL){
        fprintf (f, "Tong duong cheo chinh: %d\n", tong);
        fclose(f);
        printf ("Da ghi ket qua vao file thanh cong!\n");
    }
    else 
        printf ("Khong the mo file\n");
    return tong;
}
// f, tim so lon nhat va ghi vao file
void TimMax(int A[MAX][MAX], int n){
    int max = A[0][0];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (A[i][j] > max){
                max = A[i][j];
            }
        }
    }
    FILE *f = fopen(FILE_OUTPUT, "a");
    if (f != NULL){
        fprintf (f, "So lon nhat trong ma tran: %d\n", max);
        fclose(f);
        printf ("Da ghi ket qua vao file thanh cong!\n");
    }else{
        printf ("Khong the mo file\n");
    }
}
int main(){
    int n, m, A[MAX][MAX];
    ghiFile();
    if (docFile(A, &n)) {
        printf("Ma tran doc tu file:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }
    }
    xuatMaTran(A, n);
    TongDuongCheoChinh(A, n);
    TimMax(A, n);
    return 0;
}
