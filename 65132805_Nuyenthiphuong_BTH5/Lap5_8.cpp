#include <stdio.h>

#define MAXN 30
#define MAXM 1000

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    FILE *fin = fopen("Knapsack.txt", "r");
    FILE *fout = fopen("Knapsack_out.txt", "w");

    if (fin == NULL || fout == NULL) {
        printf("Khong mo duoc file!\n");
        return 1;
    }

    int n, M;
    fscanf(fin, "%d %d", &n, &M);

    int v[MAXN + 1], w[MAXN + 1];
    for (int i = 1; i <= n; i++)
        fscanf(fin, "%d", &v[i]);

    for (int i = 1; i <= n; i++)
        fscanf(fin, "%d", &w[i]);

    // Bảng phương án L[i][j]
    int L[MAXN + 1][MAXM + 1];

    // Khởi tạo
    for (int j = 0; j <= M; j++)
        L[0][j] = 0;

    // Quy hoạch động
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= M; j++) {
            if (w[i] <= j)
                L[i][j] = max(L[i - 1][j], L[i - 1][j - w[i]] + v[i]);
            else
                L[i][j] = L[i - 1][j];
        }
    }

    // Truy vết các vật được chọn
    int chosen[MAXN + 1] = {0};
    int j = M;

    for (int i = n; i >= 1; i--) {
        if (L[i][j] != L[i - 1][j]) {
            chosen[i] = 1;
            j -= w[i];
        }
    }

    // Ghi kết quả
    fprintf(fout, "Tong gia tri lon nhat: %d\n", L[n][M]);
    fprintf(fout, "Cac vat duoc chon: ");

    for (int i = 1; i <= n; i++) {
        if (chosen[i])
            fprintf(fout, "%d ", i);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
