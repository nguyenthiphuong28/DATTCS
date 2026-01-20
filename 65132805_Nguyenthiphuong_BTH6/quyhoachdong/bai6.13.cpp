/*
Bài 6.13 Dùng kỹ thuật quy hoạch động tìm Dãy con con tăng đơn điệu dài nhất
Cho một dãy số nguyên gồm n phần tử a[1], a[2], .. , a[N].
Biết rằng dãy con tăng đơn điệu là 1 dãy a[i1],... a[ik] thỏa mãn i1 < i2 < ... < ik và a[i1] <
a[i2] < .. < a[ik].
Hãy in ra màn hình dãy con tăng đơn điệu dài nhất của dãy đã cho.
*/

#include <stdio.h>
#define MAX 100
int a[] = {12,1,4,7,5,8,7,9,16}; // day so ban dau
int n;
int l [MAX]; // luu lai do dai day con tang don dieu tai vi tri i
int t[MAX]; // luu vi tri truoc i
int lmax; // do dai day con tang don dieu lon nhat (khong can thiet, co the bo)
void Init(){
    n = sizeof(a)/sizeof(a[0]);
    for (int i = 0; i < n; i++){
        l[i] = 1;
        t[i] = -1;
    }
}
void Dynamic(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < i; j++){
            if (a[j] < a[i] && l[i] < l[j] + 1){
                l[i] = l[j] + 1;
                t[i] = j;
            }
        }
    }
}
// truy vet
void Track(){
    int max_len = l[0], p = 0;
    for (int i = 1; i < n; i++){
        if (l[i] > max_len){
            max_len = l[i];
            p = i;
        }
    }
    printf("\nDo dai day tang dan la %d", max_len);
    int kq[MAX], idx = 0; // luu vi tri cac phan tu
    while (p >= 0){
        kq[idx++] = p;
        p = t[p];
    }
    printf("\nDay con tang dan dai nhat: ");
    for (int k = idx-1; k >= 0; k--){
        printf("%d ", a[kq[k]]);
    }
    printf("\n");
}

int main(){
    Init();
    Dynamic();
    Track();
    return 0;
}