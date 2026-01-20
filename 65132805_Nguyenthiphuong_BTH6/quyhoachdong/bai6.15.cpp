/*Bài toán sắp balo (Knapsack)
Trong cửa hàng có N gói hàng, gói hàng thứ i có trọng lượng là Wi và giá trị là Vi. Một tên
trộm đột nhập vào cửa hàng, tên trộm mang theo một cái túi có thể mang được tối đa trọng
lượng là M. Hỏi tên trộm sẽ lấy đi những gói hàng nào để được tổng giá trị là lớn nhất. (dùng
kỹ thuật quy hoạch động)
- Đầu vào file gồm:
▪ Giá trị n (n<30) và M
▪ Giá trị của các đồ vật v1, v2, .., vn
▪ Trọng lượng của các đồ vật w1, w2, .., wn
- Đầu ra: Đưa ra các vật được chọn với giá trị lớn nhất.*/
#include <stdio.h>
#define MAXN 30
#define MAXM 1000

int n, M;
int w[MAXN], v[MAXN];
int dp[MAXN][MAXM];

// Hàm nhập dữ liệu
void Nhap() {
    printf("Nhap n va M: ");
    scanf("%d%d", &n, &M);

    printf("Nhap gia tri cac goi hang:\n");
    for (int i = 1; i <= n; i++)
        scanf("%d", &v[i]);

    printf("Nhap trong luong cac goi hang:\n");
    for (int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
}

// Hàm quy hoạch động giải bài toán balo
void QuyHoachDong() {
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= M; j++)
            dp[i][j] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= M; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= w[i] && dp[i - 1][j - w[i]] + v[i] > dp[i][j])
                dp[i][j] = dp[i - 1][j - w[i]] + v[i];
        }
    }
}

// Hàm truy vết các gói hàng được chọn
void TruyVet() {
    printf("Gia tri lon nhat lay duoc: %d\n", dp[n][M]);
    printf("Cac goi hang duoc chon:\n");

    int j = M;
    for (int i = n; i >= 1; i--) {
        if (j >= w[i] && dp[i][j] == dp[i - 1][j - w[i]] + v[i]) {
            printf("Goi %d (w = %d, v = %d)\n", i, w[i], v[i]);
            j -= w[i];
        }
    }
}

int main() {
    Nhap();
    QuyHoachDong();
    TruyVet();
    return 0;
}
