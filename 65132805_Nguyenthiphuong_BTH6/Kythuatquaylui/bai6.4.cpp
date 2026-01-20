/*Trò chơi phi tiêu với luật chơi như sau: người chơi tham gia phóng n mũi tên cho
trước vào một mục tiêu, người chơi sẽ chiến thắng khi không có m lần liên tiếp phóng mũi
tên không trúng mục tiêu và có ít nhất k mũi tên trúng mục tiêu. Hãy đưa ra tất cả các cách
để trở thành người chiến thắng trong trò chơi này.*/
#include <stdio.h>
#define N 20

int x[N];        // 1: trúng, 0: trượt
int n, k, m;
int dem = 0;     // đếm số cách thắng

// Hàm kiểm tra và in kết quả
void Print() {
    int demTrung = 0;
    int demTruot = 0;
    int kq = 1;

    for (int i = 1; i <= n; i++) {
        if (x[i] == 1) {
            demTrung++;
            demTruot = 0;
        } else {
            demTruot++;
            if (demTruot == m) {
                kq = 0;
                break;
            }
        }
    }

    if (kq && demTrung >= k) {
        dem++;
        for (int i = 1; i <= n; i++) {
            if (x[i] == 1)
                printf("x");
            else
                printf("_");
        }
        printf("\n");
    }
}

// Hàm quay lui sinh chuỗi nhị phân
void Try(int i) {
    for (int j = 0; j <= 1; j++) {
        x[i] = j;
        if (i == n)
            Print();
        else
            Try(i + 1);
    }
}

int main() {
    printf("Nhap n, m, k: ");
    scanf("%d%d%d", &n, &m, &k);

    Try(1);

    if (dem == 0)
        printf("-1\n");
    else
        printf("So cach thang: %d\n", dem);

    return 0;
}
