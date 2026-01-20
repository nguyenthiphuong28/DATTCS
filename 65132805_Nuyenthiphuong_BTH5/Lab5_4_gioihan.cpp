//so to tien cua moi menh gia la huu han
#include <stdio.h>
#include <limits.h>
#define N 30      // so to tien toi da
#define MAXS 2000    // so tien toi da rut
#define INF (INT_MAX/4)

void KhoiTao();
void ATM_QHD();
int TruyVet();

int t[]={1, 2, 2, 5, 5, 10}; //cac to tien              
int dp[N+1][MAXS+1];      // dp[i][x] = it to nhat
int chon[N+1][MAXS+1]; // chon[i][x] = 1 neu chon to i 
int n, S;
 
int main() {   
    printf("Nhap so  tien S: ");
    scanf("%d", &S); 
    
    KhoiTao();
    ATM_QHD();
    TruyVet();
}
// Khoi tao dp 
void KhoiTao(){
	for (int x = 0; x <= S; x++) {
        dp[0][x] = (x == 0) ? 0 : INF;
        chon[0][x] = 0;
    }
} 
// Quy hoach dong
void ATM_QHD(){
    for (int i = 1; i <= n; i++) {
        for (int x = 0; x <= S; x++) {
            // Khong lay to i
            dp[i][x] = dp[i-1][x];
            chon[i][x] = 0;

            // Lay to i neu co the
            int w = t[i-1];
            if (x >= w && dp[i-1][x - w] + 1 < dp[i][x]) {
                dp[i][x] = dp[i-1][x - w] + 1;
                chon[i][x] = 1;
            }
        }
    }
}
//truy vet
int TruyVet(){
    if (dp[n][S] >= INF) {
        printf("Khong co cach tra dung so tien %d\n", S);
        return 0;
    }
    // Truy vet nghiem
    printf("So to it nhat: %d\n", dp[n][S]);  
    int i = n, x = S;
    while (i > 0 && x >= 0) {
        if (chon[i][x]) {
            printf("%d ", t[i-1]);
            x -= t[i-1];
        }
        i--;
	} 
}

