#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Hàm kiểm tra số nguyên tố
int KiemTraNguyenTo(int x) {
    if (x < 2)
        return 0;
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0)
            return 0;
    }
    return 1;
}

// (b) Hàm đọc dữ liệu từ file vào mảng
int DocFile(int a[], int *n) {
    FILE *f = fopen("DaySoNguyen.txt", "r");
    if (f == NULL) {
        printf("Khong mo duoc file DaySoNguyen.txt!\n");
        return 0;
    }

    fscanf(f, "%d", n); // Đọc số lượng phần tử n
    if (*n < 2 || *n >= 50) {
        printf("Gia tri n khong hop le!\n");
        fclose(f);
        return 0;
    }

    for (int i = 0; i < *n; i++) {
        fscanf(f, "%d", &a[i]);
    }

    fclose(f);
    return 1;
}

// (c) Hàm xuất mảng ra màn hình
void XuatMang(int a[], int n) {
    printf("Day so trong file la:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// (d) Hàm tính tổng các phần tử là số nguyên tố
int TongNguyenTo(int a[], int n) {
    int tong = 0;
    for (int i = 0; i < n; i++) {
        if (KiemTraNguyenTo(a[i]))
            tong += a[i];
    }
    return tong;
}

// Hàm main: gọi các hàm trên
int main() {
    int a[50];
    int n;

    if (DocFile(a, &n)) {
        XuatMang(a, n);
        int tong = TongNguyenTo(a, n);
        printf("Tong cac so nguyen to trong day la: %d\n", tong);
    }

    return 0;
}
