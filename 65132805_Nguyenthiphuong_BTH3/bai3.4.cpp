#include<stdio.h>
#include<string.h>
#include<ctype.h>

//a Nhap chuoi
void NhapChuoi(char s[]){
    printf("Nhap chuoi (toi da 100 ky tu): ");
    fgets(s,101,stdin);
    // xos ky ru \n do fgets luu lai
    s[strcspn(s, "\n")] = '\0';
}

//b) Dem so ky tu trong chuoi(de quy)
int DemKT(char s[]){
    if(*s == '\0') return 0;
    return 1 + DemKT(s + 1);
}

// c) Dem chu cai thuong (a-z)

int DemCT(char s[]){
    if(*s == '\0') return 0;
    int dem = (islower(*s)) ? 1:0;
    return dem + DemCT(s + 1);
}

//d) Kiem tra chuoi doi xung
int KTDX(char s[], int trai, int phai){
    if(trai >= phai) return 1;
    if(s[trai] != s[phai]) return 0;
    return KTDX(s, trai + 1, phai -1);
}

// e)  Tinh tong chu so trong chuoi
int TongCS(char s[]){
    if(*s == '\0') return 0;
    int so = (isdigit(*s)) ?(*s - '0') : 0;
    return so + TongCS(s + 1);
}
int main(){
    char s[101];
    NhapChuoi(s);
    printf("\nChuoi vua nhap: \"%s\"\n", s);
    printf("So ky tu trong chuoi: %d\n", DemKT(s));
    printf("So chu cai thuong: %d\n", DemCT(s));
    printf("Chuoi %s doi xung.\n", KTDX(s, 0, strlen(s)-1) ? "la": "khong la");
    printf("Tong cac chu trong chuoi: %d\n", TongCS(s));
    return 0;
}