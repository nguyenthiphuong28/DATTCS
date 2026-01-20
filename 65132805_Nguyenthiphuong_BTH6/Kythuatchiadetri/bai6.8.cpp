/*
Bài 6.8 Cho chương trình theo mẫu sau, hãy viết các hàm còn thiếu (mục ghi chú) để thực
hiện các yêu cầu sau:
- Xuất dãy số ra màn hình.
- Kiểm tra dãy số có đang được sắp theo chiều tăng dần không (sử dụng chia để trị).
- Hàm main() gọi các hàm trên thực hiện kiểm tra kết quả.
#include <stdio.h>
#define MAX 50
// Hàm in dãy số ra màn hình
// Hàm Kiểm tra dãy số có tăng dần hay không theo kỹ thuật chia để trị
int main() {
int a[] = {5, 7, 9, 11, 24, 10};
int n = sizeof(a)/sizeof(a[0]);
// Gọi hàm in dãy số ra màn hình
// Gọi hàm Kiểm tra dãy số có tăng dần
return 0;
*/
#include <stdio.h>
#define MAX 50
// Hàm in dãy số
void inDS(int a[], int n){
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}
// Hàm kiểm tra dãy số có tăng dần hay không theo kỹ thuật chia để trị
int tangdan(int a[], int l, int r){
  if(l == r) return 1; // mang mot phan tu thu thoa man dieu kien tang dan
  // chia 2. mang con
  int m = (l + r) / 2;
  int trai = tangdan(a, l, m);
  int phai = tangdan(a, m + 1, r);
  if (trai != 1 || phai != 1)
    return 0;
// kiem tra duong noi giua 2 mang con
    if (a[m] > a[m + 1])
      return 0;
    return 1;

}
int main(){
    int a[] = {5, 7, 9, 11, 24, 10};
    int n = sizeof(a) / sizeof(a[0]);
    // Gọi hàm in dãy số ra màn hình
    inDS(a, n);
    // Gọi hàm Kiểm tra dãy số có tăng dần
    if (tangdan(a, 0, n - 1) == 1)
        printf("Day so tang dan\n");
    else
        printf("Day so khong tang dan\n");
    return 0;
}