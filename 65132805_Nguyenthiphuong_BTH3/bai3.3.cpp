/*
Viết hàm đệ quy thực hiện các yêu cầu:
a) Nhập vào một dãy số nguyên gồm n phần tử, với 2 ≤ n < 50;
b) Đếm số phần tử chẵn trong dãy số;
c) Kiểm tra dãy số có chứa số nguyên tố hay không;
d) Tìm vị trí đầu tiên của phần tử x trong dãy số (3 < n < 20);
e) Bài toán tháp Hà Nội;
f) Hàm main() gọi các hàm trên thực hiện để kiểm tra kết quả.

b, đk dừng n == 0 -> 0
    đệ quy Dem(a,n) nếu (a[n-1])%2== 0 -> 1 + Dem(a,n-1)
                    ngược lại -> Dem(a, n-1)
c, đk dừng n = 0 ->0
    đệ quy:
*/

#include <stdio.h>
#include <math.h>

// Nhập dãy
void NhapDS(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }
}

// Đếm phần tử chẵn (đệ quy)
int DemPTChan(int a[], int n) {
    if (n == 0) return 0;
    int dem = (a[n - 1] % 2 == 0) ? 1 : 0;
    return dem + DemPTChan(a, n - 1);
}

// Kiểm tra 1 số có phải số nguyên tố
int laSoNguyenTo(int x) {
    if (x < 2) return 0;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return 0;
    return 1;
}

// Kiểm tra dãy có số nguyên tố không (đệ quy)
int CoSoNguyenTo(int a[], int n) {
    if (n == 0) return 0;
    if (laSoNguyenTo(a[n - 1])) return 1;
    return CoSoNguyenTo(a, n - 1);
}

// Tìm vị trí đầu tiên của x (đệ quy)
int TimX(int a[], int n, int i, int x) {
    if (i == n) return -1;         // không tìm thấy
    if (a[i] == x) return i;       // tìm thấy
    return TimX(a, n, i + 1, x);   // tiếp tục tìm
}

// Hàm tháp Hà Nội (đệ quy)
void ThapHaNoi(int n, char a, char b, char c) {
    if (n == 1) {
        printf("Chuyen dia 1 tu cot %c sang cot %c\n", a, c);
        return;
    }
    ThapHaNoi(n - 1, a, c, b);
    printf("Chuyen dia %d tu cot %c sang cot %c\n", n, a, c);
    ThapHaNoi(n - 1, b, a, c);
}

// Main
int main() {
    int a[50], n, x;

    do {
        printf("Nhap so phan tu n (2 ≤ n < 50): ");
        scanf("%d", &n);
    } while (n < 2 || n >= 50);

    printf("Nhap day so:\n");
    NhapDS(a, n);

    printf("Dem phan tu chan: %d\n", DemPTChan(a, n));
    printf("Day co chua so nguyen to khong? %d\n", CoSoNguyenTo(a, n));

    printf("Nhap gia tri x can tim: ");
    scanf("%d", &x);
    int vt = TimX(a, n, 0, x);
    if (vt == -1)
        printf("Khong tim thay x trong day.\n");
    else
        printf("Vi tri dau tien cua x: %d\n", vt);

    printf("\nThap Ha Noi (3 dia):\n");
    ThapHaNoi(3, 'A', 'B', 'C');

    return 0;
}
