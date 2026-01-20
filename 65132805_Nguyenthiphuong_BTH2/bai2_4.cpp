#include<stdio.h>
#include<stdlib.h>

// a) Tạo file DaySo2_4.txt
void TaoFile() {
    FILE *f;
    int n;
    float x;

    f = fopen("DaySo2_4.txt", "w");
    if (!f) {
        printf("Khong tao duoc file!\n");
        return;
    }

    printf("Nhap so luong phan tu n (3 ≤ n ≤ 40): ");
    scanf("%d", &n);

    if (n < 3 || n > 40) {
        printf("n khong hop le!\n");
        fclose(f);
        return;
    }

    fprintf(f, "%d\n", n);
    printf("Nhap %d so thuc:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%f", &x);
        fprintf(f, "%.2f ", x);
    }

    fclose(f);
    printf("Da ghi du lieu vao file DaySo2_4.txt!\n");
}

// b) Đọc dữ liệu từ file vào mảng
int DocFile(float a[], int *n) {
    FILE *f = fopen("DaySo2_4.txt", "r");
    if (!f) {
        printf("Khong mo duoc file!\n");
        return 0;
    }

    fscanf(f, "%d", n);
    for (int i = 0; i < *n; i++) {
        fscanf(f, "%f", &a[i]);
    }

    fclose(f);
    return 1;
}

// c) Xuất dãy số ra màn hình
void XuatDay(float a[], int n) {
    printf("Day so: ");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", a[i]);
    }
    printf("\n");
}

// d) Đếm số lượng phần tử nhỏ hơn x
int DemNhoHonX(float a[], int n, float x) {
    int dem = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < x)
            dem++;
    }
    return dem;
}
// e) Hàm main kiểm tra
int main() {
    float a[40];
    int n;
    float x;

    TaoFile(); // tạo file

    if (DocFile(a, &n)) {
        XuatDay(a, n);
        printf("Nhap gia tri x: ");
        scanf("%f", &x);
        int kq = DemNhoHonX(a, n, x);
        printf("So phan tu co gia tri nho hon %.2f la: %d\n", x, kq);
    }

    return 0;
}