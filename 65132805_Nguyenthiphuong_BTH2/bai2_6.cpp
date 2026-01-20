#include <stdio.h>

// a) Hàm nhập dãy số nguyên
void NhapMang(int a[], int *n) {
    do {
        printf("Nhap so phan tu n (3 < n < 50): ");
        scanf("%d", n);
    } while (*n <= 3 || *n >= 50);

    printf("Nhap %d so nguyen:\n", *n);
    for (int i = 0; i < *n; i++) {
        scanf("%d", &a[i]);
    }
}

// Hàm xuất dãy số
void XuatMang(int a[], int n) {
    printf("Day so: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// b) Hàm tìm số chẵn đầu tiên (dùng kỹ thuật lính canh)
int SoChanDauTien(int a[], int n) {
    a[n] = -1;  // Gán lính canh (số lẻ chắc chắn)
    int i = 0;
    while (a[i] % 2 != 0 && i < n)
        i++;
    if (i == n)
        return -1; // Không có số chẵn
    return a[i];   // Trả về số chẵn đầu tiên
}

// c) Hàm kiểm tra dãy giảm dần (kỹ thuật cờ hiệu)
int KiemTraGiamDan(int a[], int n) {
    int flag = 1; // Giả sử dãy giảm dần
    for (int i = 0; i < n - 1; i++) {
        if (a[i] < a[i + 1]) {
            flag = 0; // Gặp cặp tăng, dãy không giảm
            break;
        }
    }
    return flag;
}

// d) Hàm main() gọi các hàm trên để kiểm tra kết quả
int main() {
    int a[51]; // +1 phần tử để làm lính canh
    int n;

    NhapMang(a, &n);
    XuatMang(a, n);

    int chan = SoChanDauTien(a, n);
    if (chan == -1)
        printf("Khong co so chan trong day!\n");
    else
        printf("So chan dau tien trong day la: %d\n", chan);

    if (KiemTraGiamDan(a, n))
        printf("Day so la day giam dan.\n");
    else
        printf("Day so KHONG giam dan.\n");

    return 0;
}
