#include <stdio.h>
#include <string.h>

// Cấu trúc sinh viên
struct SinhVien {
    int MaSV;
    char Ten[20];
};

// Hàm in danh sách sinh viên
void InMang(struct SinhVien a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d - %s\n", a[i].MaSV, a[i].Ten);
    }
}

// Hàm sắp xếp chèn (Insertion Sort) theo tên (A → Z)
/* void InsertionSort(struct SinhVien a[], int n) {
    int i, j;
    struct SinhVien x;
    for (i = 1; i < n; i++) {
        x = a[i];
        j = i - 1;

        while (j >= 0 && strcmp(a[j].Ten, x.Ten) > 0) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = x;
    }
}
 */

 // sap xep chen
 void InsertionSort(struct SinhVien a[], int n){
    int i, j;
    struct SinhVien x;
    for (int i = 0; i < n; i++){
        x = a[i];
        j = i -1;
        while (j >= 0 && strcmp(a[j].Ten, x.Ten) > 0){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = x;
        
    }
 }
int main() {
    struct SinhVien a[100];
    int n;

    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);

    // Nhập danh sách sinh viên
    for (int i = 0; i < n; i++) {
        printf("\nNhap thong tin sinh vien thu %d:\n", i + 1);
        printf("Ma sinh vien: ");
        scanf("%d", &a[i].MaSV);
        printf("Ten sinh vien: ");
        scanf("%s", a[i].Ten); // dùng %s cho tên không có khoảng trắng
    }

    printf("\n--- Danh sach truoc khi sap xep ---\n");
    InMang(a, n);

    // Sắp xếp theo tên
    InsertionSort(a, n);

    printf("\n--- Danh sach sau khi sap xep theo ten ---\n");
    InMang(a, n);

    return 0;
}


