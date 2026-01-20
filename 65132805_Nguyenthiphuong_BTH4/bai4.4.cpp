#include <stdio.h>
#include <string.h>

int n, k;
int mang[100];    // lưu tổ hợp/chỉnh hợp hiện tại
int daDung[100];  // đánh dấu phần tử đã dùng (chỉ dùng cho chỉnh hợp)

// mode = 0: tổ hợp, mode = 1: chỉnh hợp
void quay_lui(int bac, int batDau, int mode) {
    if (bac == k) {  // nếu đã đủ k phần tử
        printf("(");
        for (int i = 0; i < k; i++) {
            if (i) printf(",");
            printf("%d", mang[i]);
        }
        printf(") ");
        return;
    }

    for (int i = batDau; i <= n; i++) {
        if (mode == 0) {  // TỔ HỢP
            mang[bac] = i;
            quay_lui(bac + 1, i + 1, mode); // start tăng dần để tránh lặp
        } else {          // CHỈNH HỢP KHÔNG LẶP
            if (!daDung[i]) {
                mang[bac] = i;
                daDung[i] = 1;
                quay_lui(bac + 1, 1, mode); // start = 1 vì thứ tự quan trọng
                daDung[i] = 0;
            }
        }
    }
}

int main() {
    n = 3; k = 2;

    printf("Cac to hop chap %d cua %d phan tu:\n", k, n);
    quay_lui(0, 1, 0); // mode = 0: tổ hợp
    printf("\n");

    printf("Cac chinh hop khong lap chap %d cua %d phan tu:\n", k, n);
    memset(daDung, 0, sizeof(daDung));
    quay_lui(0, 1, 1); // mode = 1: chỉnh hợp không lặp
    printf("\n");

    return 0;
}
