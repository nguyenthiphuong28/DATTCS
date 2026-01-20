#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

#define MAX 50

// a) Khai báo cấu trúc SinhVien
typedef struct {
    char maSV[10];
    char hoTen[50];
    int namSinh;
} SinhVien;

// Hàm nhập danh sách sinh viên
void NhapDanhSach(SinhVien sv[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin sinh vien thu %d ---\n", i + 1);
        printf("Ma SV: ");
        fflush(stdin);
        fgets(sv[i].maSV, sizeof(sv[i].maSV), stdin);
        sv[i].maSV[strcspn(sv[i].maSV, "\n")] = '\0'; // xóa ký tự '\n'

        printf("Ho ten: ");
        fgets(sv[i].hoTen, sizeof(sv[i].hoTen), stdin);
        sv[i].hoTen[strcspn(sv[i].hoTen, "\n")] = '\0'; // xóa ký tự '\n'

        printf("Nam sinh: ");
        scanf("%d", &sv[i].namSinh);
        getchar(); // đọc ký tự '\n' còn lại
    }
}

// b) Ghi danh sách sinh viên vào file nhị phân
void GhiFile(SinhVien sv[], int n, const char *tenFile) {
    FILE *f = fopen(tenFile, "wb");
    if (f == NULL) {
        printf("Khong the mo file de ghi!\n");
        return;
    }

    fwrite(&n, sizeof(int), 1, f);           // Ghi số lượng sinh viên
    fwrite(sv, sizeof(SinhVien), n, f);      // Ghi danh sách
    fclose(f);

    printf("\nDa ghi %d sinh vien vao file '%s'.\n", n, tenFile);
}

// c) Đọc sinh viên thứ p từ file
void DocSinhVienThuP(const char *tenFile, int p) {
    FILE *f = fopen(tenFile, "rb");
    if (f == NULL) {
        printf("Khong the mo file de doc!\n");
        return;
    }

    int n;
    fread(&n, sizeof(int), 1, f);

    if (p < 1 || p > n) {
        printf("Chi so khong hop le! File chi co %d sinh vien.\n", n);
        fclose(f);
        return;
    }

    SinhVien sv;
    fseek(f, sizeof(int) + (p - 1) * sizeof(SinhVien), SEEK_SET);
    fread(&sv, sizeof(SinhVien), 1, f);
    fclose(f);

    printf("\n--- Thong tin sinh vien thu %d ---\n", p);
    printf("Ma SV   : %s\n", sv.maSV);
    printf("Ho ten  : %s\n", sv.hoTen);
    printf("Nam sinh: %d\n", sv.namSinh);
}

// Hàm main kiểm tra chương trình
int main() {
    SinhVien ds[MAX];
    int n, p;

    printf("Nhap so luong sinh vien (2 <= n < 50): ");
    scanf("%d", &n);
    getchar(); // đọc bỏ ký tự '\n' sau khi nhập n

    NhapDanhSach(ds, n);
    GhiFile(ds, n, "SinhVien.inp");

    printf("\nNhap vi tri sinh vien muon doc (1..%d): ", n);
    scanf("%d", &p);

    DocSinhVienThuP("SinhVien.inp", p);

    return 0;
}
