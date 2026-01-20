#include <stdio.h>
#include <limits.h>

#define MAX 30

int main() {
    FILE *fin = fopen("dulich", "r");
    FILE *fout = fopen("dulich_out", "w");

    if (fin == NULL || fout == NULL) {
        printf("Khong mo duoc file!\n");
        return 1;
    }

    int N;
    fscanf(fin, "%d", &N);

    int C[MAX][MAX];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            fscanf(fin, "%d", &C[i][j]);

    int visited[MAX] = {0};
    int path[MAX + 1];
    int totalCost = 0;

    int current = 0; // thành phố 1 (index 0)
    visited[current] = 1;
    path[0] = current;

    for (int step = 1; step < N; step++) {
        int nextCity = -1;
        int minCost = INT_MAX;

        for (int j = 0; j < N; j++) {
            if (!visited[j] && C[current][j] > 0 && C[current][j] < minCost) {
                minCost = C[current][j];
                nextCity = j;
            }
        }

        if (nextCity == -1) {
            fprintf(fout, "-1");
            fclose(fin);
            fclose(fout);
            return 0;
        }

        visited[nextCity] = 1;
        path[step] = nextCity;
        totalCost += minCost;
        current = nextCity;
    }

    // quay về thành phố 1
    if (C[current][0] <= 0) {
        fprintf(fout, "-1");
        fclose(fin);
        fclose(fout);
        return 0;
    }

    totalCost += C[current][0];
    path[N] = 0;

    // In kết quả
    fprintf(fout, "Duong di: ");
    for (int i = 0; i <= N; i++) {
        fprintf(fout, "%d ", path[i] + 1);
    }
    fprintf(fout, "\nTong chi phi: %d", totalCost);

    fclose(fin);
    fclose(fout);
    return 0;
}