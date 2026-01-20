#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>

// a, Nhap vao mot chuoi gom 100 ky tu
void NhapChuoi(char s[]){
    printf("Nhap chuoi: ");
    fgets(s, 100, stdin);
    // Xoa ky tu xuong dong neu co
    size_t len = strlen(s);
    if(len > 0 && s[len -1] == '\n'){
        s[len -1] = '\0';
    }
}

// b, Dem so ly tu la chu so trong chuoi
int DemSoChuSo(char s[]){
    if(*s == '\0') return 0;
    if(isdigit(*s))
        return 1 + DemSoChuSo(s +1);
    else
        return DemSoChuSo(s +1);
}

//c, Dem so ky tu in hoa trong chuoi
int DemSoKyTuInHoa(char s[]){
    if(*s == '\0') return 0;
    if(isupper(*s))
        return 1 + DemSoKyTuInHoa(s +1);
    else
        return DemSoKyTuInHoa(s +1);
}

// d, kiem tra day cos tang dan theo ma ASCII
bool KiemTraTangDan(char s[]){
    if(s[0] == '\0' || s[1] == '\0') return true;
    if(s[0] <= s[1])
        return KiemTraTangDan(s +1);
    else
        return false;
}
int main(){
    char s[100];
    NhapChuoi(s);
    printf("Chuoi vua nhap la: %s\n", s);
    printf("So chu so trong chuoi la: %d\n", DemSoChuSo(s));
    printf("So ky tu in hoa trong chuoi la: %d\n", DemSoKyTuInHoa(s));
    if(KiemTraTangDan(s))
        printf("Day ky tu tang dan theo ma ASCII\n");
    else
        printf("Day ky tu khong tang dan theo ma ASCII\n");
    return 0;
}