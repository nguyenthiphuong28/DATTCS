#include<stdio.h>
#include<string.h>
struct SinhVien{
    int mssv;
    char Ten[20];
};
void InDSSV(struct SinhVien a[], int n){
    for(int i = 0; i < n; i++){
        printf("%d - %s\n", a[i].mssv, a[i].Ten);
        return;
    }
}