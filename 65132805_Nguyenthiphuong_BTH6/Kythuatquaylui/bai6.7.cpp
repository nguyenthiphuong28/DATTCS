/*Cho n số nguyên dương với giá trị các phần tử là a1, a2,...an. Hãy điền các dấu cộng
(+) hoặc trừ (-) vào giữa các phần tử của dãy số sao cho kết quả của biểu thức với n toán
hạng và n-1 toán tử có kết quả bằng 0, toán hạng đầu tiên không có dấu ở trước. Hãy cho
biết có bao nhiêu cách điền dấu cộng hoặc trừ thỏa mãn yêu cầu đặt ra của bài toán. (dùng
kỹ thuật quay lui)
- Dữ liệu vào:
+ Số n (2 ≤ n ≤ 20)
+ Giá trị các phần tử a1, a2,...an.
- Dữ liệu ra:
• Số cách điền dấu, nếu không thể điền được thì ghi 0.
• Các dòng sau trong trường hợp điền được, mỗi dòng là 01 biểu thức đúng để giá
trị của biểu thức bằng P.*/
#include <stdio.h>
#define N 20

int n;
int a[N];
char op[N];   // op[i] là dấu trước a[i] (+ hoặc -)
int dem = 0;

// In 1 biểu thức đúng
void Print() {
    printf("%d", a[1]);
    for (int i = 2; i <= n; i++)
        printf(" %c %d", op[i], a[i]);
    printf("\n");
}

// Quay lui đặt dấu
void Try(int i, int sum) {
    if (i > n) {
        if (sum == 0) {
            dem++;
            Print();
        }
        return;
    }

    // Đặt dấu +
    op[i] = '+';
    Try(i + 1, sum + a[i]);

    // Đặt dấu -
    op[i] = '-';
    Try(i + 1, sum - a[i]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    // Số đầu tiên không có dấu
    Try(2, a[1]);

    if (dem == 0)
        printf("0\n");
    else
        printf("So cach: %d\n", dem);

    return 0;
}
