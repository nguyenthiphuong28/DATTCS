/*Dùng kỹ thuật quy hoạch động tìm Dãy con có tổng bằng S
Cho dãy số a có n phần tử, bài toán yêu cầu tìm dãy con của dãy a sao cho tổng các phần tử
của dãy con bằng S. Dãy con của một dãy số là dãy có được sau khi loại bớt một số phần tử,
các phần tử khác giữ nguyên vị trí.*/
#include <stdio.h>
#define MAXN 100
#define MAXS 1000

int n, S;
int a[MAXN];
int dp[MAXN][MAXS];

// Hàm nhập dữ liệu
void Nhap() {
    printf("Nhap n va S: ");
    scanf("%d%d", &n, &S);

    printf("Nhap day a:\n");
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
}

// Hàm quy hoạch động
void QuyHoachDong() {
    // Khởi tạo
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= S; j++)
            dp[i][j] = 0;

    dp[0][0] = 1;

    // Xây dựng bảng dp
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= S; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= a[i] && dp[i - 1][j - a[i]])
                dp[i][j] = 1;
        }
    }
}

// Hàm truy vết dãy con
void TruyVet() {
    if (!dp[n][S]) {
        printf("Khong ton tai day con co tong bang %d\n", S);
        return;
    }

    printf("Day con co tong bang %d: ", S);
    int j = S;

    for (int i = n; i >= 1; i--) {
        if (j >= a[i] && dp[i - 1][j - a[i]]) {
            printf("%d ", a[i]);
            j -= a[i];
        }
    }
    printf("\n");
}

int main() {
    Nhap();
    QuyHoachDong();
    TruyVet();
    return 0;
}
