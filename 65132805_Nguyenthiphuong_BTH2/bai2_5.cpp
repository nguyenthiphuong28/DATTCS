#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char maHP[10];
    char tenHP[50];
    int soTinChi;
} HocPhan;

// (c) Đọc danh sách học phần từ file
int DocFile(HocPhan ds[], int *n) {
    FILE *f = fopen("HocPhan.txt", "r");
    if (f == NULL) {
        printf("Khong mo duoc file HocPhan.txt!\n");
        return 0;
    }

    fscanf(f, "%d", n); // đọc số lượng học phần

    for (int i = 0; i < *n; i++) {
        fscanf(f, "%s", ds[i].maHP);
        fscanf(f, "%s", ds[i].tenHP);
        fscanf(f, "%d", &ds[i].soTinChi);
    }

    fclose(f);
    return 1;
}

// (d) Xuất danh sách học phần ra màn hình
void XuatDanhSach(HocPhan ds[], int n) {
    printf("\nDanh sach hoc phan:\n");
    printf("%-10s | %-25s | %-10s\n", "Ma HP", "Ten HP", "Tin chi");
    printf("----------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10s | %-25s | %10d\n", ds[i].maHP, ds[i].tenHP, ds[i].soTinChi);
    }
}

// (e) Hàm main gọi các hàm trên
int main() {
    HocPhan ds[50];
    int n;

    if (DocFile(ds, &n)) {
        XuatDanhSach(ds, n);
    }

    return 0;
}
