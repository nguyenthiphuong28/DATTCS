//Bai 5.5 day con chung dai nhat dung quy hoach dong
#include <stdio.h>
#include <string.h>

#define MAX 100

// Ham t�nh bang DP cho LCS
void LCS(char *A, char *B, int dp[][MAX], int n, int m) {
    for (int i = 0; i <= n; i++) dp[i][0] = 0;
    for (int j = 0; j <= m; j++) dp[0][j] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
}

// Truy vet
void Tracking(char *A, char *B, int dp[][MAX], int n, int m) {
    char lcs[MAX];
    int len = 0;
    int i = n, j = m;

    while (i > 0 && j > 0) {
        if (A[i - 1] == B[j - 1]) {
            lcs[len++] = A[i - 1];
            i--; j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // In ket qua dao nguoc
    printf("LCS: ");
    for (int k = len - 1; k >= 0; k--) {
        printf("%c", lcs[k]);
    }
    printf("\n");
}

int main() {
    char A[MAX], B[MAX];
    printf("Nhap chuoi A: ");
    scanf("%s", A);
    printf("Nhap chuoi B: ");
    scanf("%s", B);

    int n = strlen(A), m = strlen(B);
    int dp[MAX][MAX];

    LCS(A, B, dp, n, m);
    printf("Do dai LCS: %d\n", dp[n][m]);
    Tracking(A, B, dp, n, m);

    return 0;
}

