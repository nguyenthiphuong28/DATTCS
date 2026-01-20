#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 30
#define INF 1000000000

int n;
int C[MAX][MAX];         // ma trận chi phí
int x[MAX];              // hành trình hiện tại
int visited[MAX];        // đánh dấu thành phố đã đi
int bestCost = INF;      // chi phí tốt nhất
int bestPath[MAX];       // lưu hành trình tốt nhất

// Hàm mở và đọc file input
int DocFile(const char* tenFile) {
    FILE *fin = fopen(tenFile, "r");
    if (!fin) {
        printf("Khong mo duoc file %s!\n", tenFile);
        return 0; // lỗi
    }
    fscanf(fin, "%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fscanf(fin, "%d", &C[i][j]);
    fclose(fin);
    return 1; // thành công
}

// Hàm ghi file output
int GhiFile(const char* tenFile) {
    FILE *fout = fopen(tenFile, "w");
    if (!fout) {
        printf("Khong mo duoc file %s!\n", tenFile);
        return 0;
    }

    if (bestCost == INF) {
        fprintf(fout, "-1\n");
    } else {
        fprintf(fout, "Chi phi thap nhat: %d\n", bestCost);
        fprintf(fout, "Hanh trinh: 1 ");
        for (int i = 1; i <= n; i++)
            fprintf(fout, "%d ", bestPath[i]);
        fprintf(fout, "1\n");
    }

    fclose(fout);
    return 1;
}

// Hàm quay lui với nhánh cận
void TryPath(int k, int currentCost) {
    for (int i = 2; i <= n; i++) { // xét các thành phố chưa đi
        if (!visited[i] && C[x[k-1]][i] > 0) {
            x[k] = i;
            visited[i] = 1;
            int tempCost = currentCost + C[x[k-1]][i];

            // Nhánh cận: chỉ xét nếu chi phí hiện tại < bestCost
            if (tempCost < bestCost) {
                if (k == n) { // đã đi hết n thành phố
                    if (C[i][1] > 0) { // có đường về 1
                        int totalCost = tempCost + C[i][1];
                        if (totalCost < bestCost) {
                            bestCost = totalCost;
                            for (int j = 1; j <= n; j++)
                                bestPath[j] = x[j];
                        }
                    }
                } else {
                    TryPath(k + 1, tempCost);
                }
            }

            visited[i] = 0; // backtrack
        }
    }
}

int main() {
    if (!DocFile("Dulich.inp")) return 1; // mở file không thành công

    // khởi tạo
    x[1] = 1;
    for (int i = 1; i <= n; i++) visited[i] = 0;
    visited[1] = 1;

    TryPath(1, 0);

    // ghi kết quả ra file
    GhiFile("Dulich.out");

    return 0;
}
