/*
Bài 4.2 Bài toán rút tiền ATM. Một máy ATM hiện có n (n ≤ 20) tờ tiền với mệnh giá t1, t2,
…, tn. Hãy đưa ra các cách trả tiền với số tiền đúng bằng S (dùng kỹ thuật quay lui)
- Đầu vào file văn bản (ATM.inp) chứa 2 dòng
o Dòng đầu chứa giá trị n, s (n<30)
o Dòng sau chứa mệnh giá trị của các tờ tiền t1, t2, .., tn
- Đầu ra: file văn bản (ATM_out.out) nếu có thể trả đúng s thì đưa ra cách trả, không
có cách trả thì ghi -1.

* bài này có 2 dạng - số tờ không hạn chê
                    - số tờ giới hạn
*/

#include<stdio.h>
#define N 50

FILE* fout = fopen("ATM_out.out", "w");
int s1 = 0;

void DocFile (char* st, int t[], int &n, int &s){
    FILE* f = fopen(st, "r");
    if(f == NULL)
        printf("Err!");
    else{
        int i;
        fscanf(f, "%d", &n); // so n
        fscanf(f, "%d", &s); // tong tien
        for (i = 0; i < n; i++)
            fscanf(f, "%d", &t[i]);
        fclose(f);
    }
}
// Xuat day so
void Xuat(int a[], int n, int s){
    int i;
    printf("Tong tien can rut s: %d\nCac so tien co trong atm:",s);
    for(i = 0; i < n; i++)
        printf("%8d", a[i]);
    printf("\n");
}

// in nghiem ra man hinh
void XuatNghiem(int t[], int x[], int n, int s){
    int sum = 0, i;
    for(i = 0; i < n; i++)
        sum += x[i] * t[i];
    if(sum == s){
        for(i = 0; i < n; i++)
            if(x[i] == 1)
                printf("%d: %d\t", i, t[i]);
            printf("\n");
    }
}

// quay lui c1
void ATM_1(int i, int t[], int x[], int n, int s){
    for (int j = 0; j <= 1; j++){
        x[i] = j;
        if(i == n-1)
            XuatNghiem(t,x,n,s);
        else
            ATM_1(i+1, t,x,n,s);
    }
}

// ghi file
void GhiFile(int t[], int x[], int n, int s){
    int sum = 0, i;
    for(i = 0; i < n; i++)
        sum += x[i]*t[i];
    if(sum == s){
        for(i = 0; i<n; i++)
            if(x[i] == 1)
                fprintf(fout, "%d: %d\t", i, t[i]);
            fprintf(fout, "\n");
    }
}

//c2
void ATM_2(int i, int t[], int x[], int n, int s,int tong){
    if (tong > s) return; // vuot qua s
    if(i == n){
        GhiFile(t,x,n,s);//Xuat Nghiem (t,x,n,s)
        return;
    }
    // khong cho to thu i
    x[i] = 0;
    ATM_2(i + 1, t,x,n,s,tong);
    // chon to thu i
    x[i]= 1;
    ATM_2(i + 1,t,x,n,s,tong + t[i]);
}
void XuatNghiem21(int t[], int x[], int n){
    for(int i = 0; i < n; i++){
        if (x[i] == 1)
            printf("%d: %d\t", i,t[i]);
    }
    printf("\n");
}

// ham quy lui
void ATM_21 (int i, int t[],int x[], int n, int s){
    if(s1 > s) return; // neu tong > s thi dung

    if (i == n){
        if(s1 == s){
            XuatNghiem21(t,x,n);
            return;
        }
        x[i] = 1; s1 += t[i]; ATM_21(i + 1, t, x,n,s);
        s1 -= t[i]; 
        x[i] = 0; ATM_21(i + 1, t,x,n,s);
    }
}
// ham main
int main(){
    int t[N], n, s;
    int x[N]; // luu tat ca cac nghiem
    DocFile("ATM.inp",t,n,s);
    Xuat(t, n, s);
    ATM_1(0,t,x,n,s);
    if (fout == NULL){
        printf("Err!"); return 0;
    }
    else 
    ATM_2(0,t,x,n,s,0);
    ATM_21(0,t,x,n,s);
}