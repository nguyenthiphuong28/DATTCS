/*Cho chương trình theo mẫu sau, hãy viết các hàm còn thiếu (mục ghi chú) để thực
hiện các yêu cầu sau:
- Xuất dãy số ra màn hình.
- Đếm và trả về số lượng phần tử lớn hơn x trong dãy số (sử dụng chia để trị).
Bài thực hành số 6 – Kỹ thuật lập trình –66.CNTT-2,3 3
- Tính và trả về tổng các phần tử ở vị trí chẵn trong dãy số (sử dụng chia để trị).
- Hàm main() gọi các hàm trên thực hiện kiểm tra kết quả.
#include <stdio.h>
#define MAX 50
// Hàm in dãy số ra màn hình
// Hàm đếm và trả về số lượng phần tử lớn hơn x trong dãy số theo kỹ thuật chia
để trị
// Hàm tính và về tổng các phần tử ở vị trí chẵn trong dãy số theo kỹ thuật
chia để trị
int main() {
int a[] = {3.5, 7.1, 9.5, 1.1, 2.4};
int n = sizeof(a)/sizeof(a[0]);
// Gọi hàm in dãy số ra màn hình
// Gọi các hàm
return 0;
}*/
#include <stdio.h>
#define MAX 50

// Hàm in dãy số ra màn hình
void Print(float a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%.1f ", a[i]);
    printf("\n");
}

// Hàm đếm số phần tử lớn hơn x (chia để trị)
int CountGreater(float a[], int l, int r, float x) {
    if (l == r)
        return (a[l] > x) ? 1 : 0;

    int mid = (l + r) / 2;
    return CountGreater(a, l, mid, x)
         + CountGreater(a, mid + 1, r, x);
}

// Hàm tính tổng các phần tử ở vị trí chẵn (chia để trị)
// Vị trí chẵn: index 0, 2, 4,...
float SumEvenPos(float a[], int l, int r) {
    if (l == r)
        return (l % 2 == 0) ? a[l] : 0;

    int mid = (l + r) / 2;
    return SumEvenPos(a, l, mid)
         + SumEvenPos(a, mid + 1, r);
}

int main() {
    float a[] = {3.5, 7.1, 9.5, 1.1, 2.4};
    int n = sizeof(a) / sizeof(a[0]);
    float x = 5.0;

    // In dãy số
    Print(a, n);

    // Gọi các hàm
    printf("So phan tu > %.1f: %d\n", x,
           CountGreater(a, 0, n - 1, x));

    printf("Tong cac phan tu o vi tri chan: %.1f\n",
           SumEvenPos(a, 0, n - 1));

    return 0;
}
