#include <stdio.h>

// a) Hàm tính lũy thừa a^b bằng đệ quy
int luyThua(int a, int b) {
    if (b == 0) return 1;              
    return a * luyThua(a, b - 1);     
}

// b) Hàm đếm số ký tự trong chuỗi
int demKyTu(char *s) {
    if (*s == '\0') return 0;         
    return 1 + demKyTu(s + 1);         
}

// c) Hàm tính tổng các số từ 1 đến n
int tong(int n) {
    if (n == 0) return 0;              
    return n + tong(n - 1);           
}

// d) Hàm đếm ký tự là chữ thường trong chuỗi
int demKTThuong(const char *s) {
    if (*s == '\0') return 0;          
    int dem = (*s >= 'a' && *s <= 'z') ? 1 : 0;  
    return dem + demKTThuong(s + 1);
}


int main() {
    // a) Kiểm tra lũy thừa
    int a = 2, b = 5;
    printf("a) %d^%d = %d\n", a, b, luyThua(a, b));

    // b) Kiểm tra đếm ký tự
    char s1[] = "Hello123";
    printf("b) So ky tu trong chuoi \"%s\" = %d\n", s1, demKyTu(s1));

    // c) Kiểm tra tính tổng
    int n = 10;
    printf("c) Tong cac so tu 1 den %d = %d\n", n, tong(n));

    // d) Kiểm tra đếm chữ thường
    char s2[] = "HeLloWorld";
    printf("d) So ky tu thuong trong chuoi \"%s\" = %d\n", s2, demKTThuong(s2));

    return 0;
}
