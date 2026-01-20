/*Một người cha muốn chia đều số tiền của mình cho hai người con có tên là A và B.
Ông ta có n tờ tiền (n ≤ 50) với các mệnh giá là t1, t2, .., tn. Bạn hãy giúp ông ấy chia tiền cho
hai người con sao cho số tiền hai người con nhận được là bằng nhau. Nếu chia được thì đưa
ra số cách chia và nêu rõ các cách chia (dùng kỹ thuật quay lui). Kết quả in ra của một cách
chia: tờ tiền ti được chia cho người tên A thì ký tự A sẽ xuất hiện tại vị trí i trong cách chia.
Dữ liệu vào:
- Số tờ tiền n (𝑛 ≤ 50)
- Mệnh giá của các tờ tiền t1, t2, .., tn
Dữ liệu ra:
- Số cách chia, nếu không có cách chia thì ghi “Khong chia duoc”.
- Mỗi dòng sau là kết quả của một cách chia.*/
#include <stdio.h>
#define N 50

int n;
int t[N];
char x[N];        // lưu A hoặc B
int dem = 0;

// In 1 cách chia
void Print() {
    for (int i = 1; i <= n; i++)
        printf("%c", x[i]);
    printf("\n");
}

// Quay lui
void Try(int i, int sumA, int sumB) {
    if (i > n) {
        if (sumA == sumB) {
            dem++;
            Print();
        }
        return;
    }

    // Tờ i cho A
    x[i] = 'A';
    Try(i + 1, sumA + t[i], sumB);

    // Tờ i cho B
    x[i] = 'B';
    Try(i + 1, sumA, sumB + t[i]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &t[i]);

    Try(1, 0, 0);

    if (dem == 0)
        printf("Khong chia duoc\n");
    else
        printf("So cach chia: %d\n", dem);

    return 0;
}
