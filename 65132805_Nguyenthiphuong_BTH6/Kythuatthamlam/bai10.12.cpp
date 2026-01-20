/*Cho n thành phố đánh số từ 1 đến n và các tuyến đường giao thông hai chiều giữa chúng.
Mạng giao thông này được cho bởi mảng hai chiều C, với C[i][j]=C[j][i] là chi phí đi trên
đoạn đường nối thành phố i và thành phố j.
Một người du lịch xuất phát từ thành phố 1, muốn đi thăm tất cả các thành phố còn lại mỗi
thành phố đúng một lần và cuối cùng về thành phố xuất phát. Hãy chỉ ra hành trình với chi
phí ít nhất (theo kỹ thuật tham lam).*/
#include <stdio.h>
#define MAX 20
#define VO_CUC 1000000

int n;                       // số thành phố
int C[MAX][MAX];             // ma trận chi phí
int daTham[MAX];             // đánh dấu thành phố đã đi
int hanhTrinh[MAX];          // lưu hành trình
int tongChiPhi;              // tổng chi phí

// Hàm nhập dữ liệu
void Nhap() {
    printf("Nhap so thanh pho n: ");
    scanf("%d", &n);

    printf("Nhap ma tran chi phi:\n");
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &C[i][j]);
}

// Hàm giải bài toán người du lịch theo tham lam
void NguoiDuLich_ThamLam() {
    for (int i = 1; i <= n; i++)
        daTham[i] = 0;

    int hienTai = 1;
    hanhTrinh[1] = 1;
    daTham[1] = 1;
    tongChiPhi = 0;

    for (int i = 2; i <= n; i++) {
        int keTiep = -1;
        int chiPhiMin = VO_CUC;

        for (int j = 1; j <= n; j++) {
            if (!daTham[j] && C[hienTai][j] < chiPhiMin) {
                chiPhiMin = C[hienTai][j];
                keTiep = j;
            }
        }

        hanhTrinh[i] = keTiep;
        daTham[keTiep] = 1;
        tongChiPhi += chiPhiMin;
        hienTai = keTiep;
    }

    // Quay về thành phố xuất phát
    tongChiPhi += C[hienTai][1];
}

// Hàm in kết quả
void InKetQua() {
    printf("Hanh trinh: ");
    for (int i = 1; i <= n; i++)
        printf("%d -> ", hanhTrinh[i]);
    printf("1\n");

    printf("Tong chi phi: %d\n", tongChiPhi);
}

int main() {
    Nhap();
    NguoiDuLich_ThamLam();
    InKetQua();
    return 0;
}
