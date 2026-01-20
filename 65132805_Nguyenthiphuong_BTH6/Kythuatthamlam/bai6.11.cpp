/*
Câu 6.11 Bài toán sắp balo (bài toán cái túi)
Trong cửa hàng có N gói hàng, gói hàng thứ i có trọng lượng là Wi và giá trị là Vi. Một tên
trộm đột nhập vào cửa hàng, tên trộm mang theo một cái túi có thể mang được tối đa trọng
lượng là M. Hỏi tên trộm sẽ lấy đi những gói hàng nào để được tổng giá trị là lớn nhất. (dùng
kỹ thuật tham lam)
Ý tưởng:
- Tính đơn giá cho các loại đồ vật.
- Xét các loại đồ vật theo thứ tự đơn giá từ lớn đến nhỏ.
- Với mỗi đồ vật được xét sẽ lấy một số lượng tối đa mà trọng lượng còn lại của ba lô
cho phép.
- Xác định trọng luợng còn lại của ba lô và quay lại bước 3 cho đến khi không còn có
thể chọn được đồ vật nào nữa.
*/
#include <stdio.h>  
#define MAX 50
#define SWAP(a, b, c) {c = a; a = b; b = c;}

float v[] = {4, 7, 10,2}; // gia tri cua tung mon hang
float w[] = {5, 3, 6,4}; // trong luong tung mon hang
int n = sizeof(v) / sizeof(v[0]); // so mon hang
float p[MAX]; // tri gia cua cac don hang
int x[MAX]; // nghiem cua bai toan
float T, M = 9; // trong luong toi da cua balo
void init(){
    T = M;
    // tinh don gia: gia tri tren mot don vi trong luong
    for (int i = 0; i < n; i++)
        p[i] = v[i] / w[i];
    
    // sap xep theo chieu giam dan
    float temp;
    for (int i = 0; i  < n; i ++)
    for (int j = i+1; j < n; j++)
        if (p[i] < p[j]){
            SWAP(p[i], p[j], temp);
            SWAP(v[i], v[j], temp);
            SWAP(w[i], w[j], temp);
        }
}
// in nghiem
void inNghiem(){
    printf("Tong trong luong tui dung do vat: %.1f\n", M - T);
    T = 0;
    float  k= 0;
    for (int i = 0; i < n; i++){
        if (x[i] != 0){
            printf("x : %d v: %.2f | w: %.2f\n", x[i], v[i], w[i]);
            T += x[i] * v[i];
            k += x[i] * w[i];
        }
    }
}

// tim phan tu nghiem thu i
void Greedy(){
    int i = 0; // vat thu i
    while (T > 0 && i < n){
        // chon ung vien tot nhat
        if (T >= w[i]){
           x[i]++; // neu mot vayt chi lay dung mot lan thi x[i] = 1;
        }
        else
            i++;
    }
}

// chuong trinh chinh
int main(){
    init();
    Greedy();
    inNghiem();
    return 0;
}