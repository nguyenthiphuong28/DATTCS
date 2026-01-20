/*
Dùng một trình soạn thảo tạo file lưu trữ số phần tử của mảng gồm n số nguyên (2 ≤
n ≤ 50) có tên “Lab3_1.inp” với cấu trúc như sau:
Viết các hàm thực hiện các yêu cầu sau:
a) Đọc nội dung trong file “Lab3_1.inp” ra mảng a;
b) Xuất mảng a ra màn hình;
c) Tìm và xuất ra màn hình số lớn nhất trong mảng a (dùng vòng lặp, đệ quy);
d) Hàm main() gọi các hàm trên thực hiện để kiểm tra kết quả.
 */
// nên viết hàm có gtri trả về

/*
c, hàm đệ quy => tìm đk dừng-n =1 -> a[0] (a[n-1]) or n == 0 ->0
            ==> đệ quy 
 * nếu n <= 0 <= 50 thì chỉ có 1 đk dừng là n == 0 => 0
*/
 #include<stdio.h>
 #define Max 50

 //hàm đọc file 
 int docFile (int a [], int &n){
    FILE *f = fopen("Lap3_1.inp", "r");
    if (f != NULL){
        fscanf(f, "%d", &n);
        if (n < 3 || n > Max){
            printf ("so luong phan tu khong hop le");
            fclose(f);
            return 0;
        }
        // doc cac phan tu trong day so ra mang
        for(int i = 0; i < n; i++)
            fscanf(f, "%d", &a[i]);
        fclose(f);
        return 1;
    }
    else
    {
        printf ("khong the mo file");
        return 0;
    }
 }

 // ham xuat mang
 void xuatMang(int a[], int n) {
    printf("Mang a gom %d phan tu:\n", n);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

//tim phan tu lon nhat
int TimMaxFor(int a[], int n){
    int max = a[0];
    for(int i = 0; i < n; i++)
        if(max < a[i])
            max = a[i];
    return max;
}

int TimMaxDe(int a[], int n){
    if ( n==1)
        return a[n-1];
    else
        if(a[n - 1] > TimMaxDe(a, n-1))
            return a[n-1];
        else return TimMaxDe(a,n-1);
}

 int main(){
    int n;
    int a[Max];
    //docFile(a,n);
    //xuatMang(a,n);
    if(docFile(a,n)){
        xuatMang(a,n);
        printf ("so lon nhat bang vong lap: %d\n", TimMaxFor(a,n));
        printf ("so lon nhat bang de quy: %d\n", TimMaxDe(a,n));
    }

 }


