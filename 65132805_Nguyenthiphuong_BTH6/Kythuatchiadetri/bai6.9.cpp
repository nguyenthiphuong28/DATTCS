/*Cho chương trình theo mẫu sau, hãy viết các hàm còn thiếu (mục ghi chú) để thực
hiện các yêu cầu sau:
- Xuất dãy số ra màn hình.
- Tính và trả về phần tử lớn nhất trong dãy số (sử dụng chia để trị).
- Tính và trả về tổng các phần tử dương trong dãy số (sử dụng chia để trị).
- Hàm main() gọi các hàm trên thực hiện kiểm tra kết quả.
#include <stdio.h>
#define MAX 50
// Hàm in dãy số ra màn hình
// Hàm tính và trả về phần tử lớn nhất trong dãy số theo kỹ thuật chia để trị
// Hàm tính và về tổng các phần tử dương trong dãy số theo kỹ thuật chia để trị
int main() {
int a[] = {3.5, 7.1, 9.5, 1.1, 2.4};
int n = sizeof(a)/sizeof(a[0]);
// Gọi hàm in dãy số ra màn hình
// Gọi các hàm
return 0;
}*/
#include <stdio.h>
#define MAX 50

// Hàm in dãy số
void Print(float a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%.1f ", a[i]);
    printf("\n");
}

// Hàm tìm phần tử lớn nhất (chia để trị)
float Max(float a[], int l, int r) {
    if (l == r)
        return a[l];

    int mid = (l + r) / 2;
    float max1 = Max(a, l, mid);
    float max2 = Max(a, mid + 1, r);

    return (max1 > max2) ? max1 : max2;
}

// Hàm tính tổng các phần tử dương (chia để trị)
float SumDuong(float a[], int l, int r) {
    if (l == r)
        return (a[l] > 0) ? a[l] : 0;

    int mid = (l + r) / 2;
    return SumDuong(a, l, mid) + SumDuong(a, mid + 1, r);
}

int main() {
    float a[] = {3.5, 7.1, 9.5, 1.1, 2.4};
    int n = sizeof(a) / sizeof(a[0]);

    // In dãy số
    Print(a, n);

    // Gọi hàm chia để trị
    printf("Phan tu lon nhat: %.1f\n", Max(a, 0, n - 1));
    printf("Tong cac phan tu duong: %.1f\n", SumDuong(a, 0, n - 1));

    return 0;
}
