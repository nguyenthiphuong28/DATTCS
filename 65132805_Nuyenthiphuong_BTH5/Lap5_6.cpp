#include <stdio.h>
#include <limits.h>

/* a) Tìm vị trí phần tử x trong mảng đã sắp xếp  */
int timX(int a[], int left, int right, int x) {
    if (left > right)
        return -1;

    int mid = (left + right) / 2;

    if (a[mid] == x)
        return mid;
    else if (a[mid] > x)
        return timX(a, left, mid - 1, x);
    else
        return timX(a, mid + 1, right, x);
}

/* b) Đếm số lần xuất hiện của x */
int demX(int a[], int left, int right, int x) {
    if (left > right)
        return 0;

    if (left == right)
        return (a[left] == x);

    int mid = (left + right) / 2;
    return demX(a, left, mid, x) + demX(a, mid + 1, right, x);
}

/* c) Tìm vị trí phần tử lớn nhất */
int viTriMax(int a[], int left, int right) {
    if (left == right)
        return left;

    int mid = (left + right) / 2;
    int i1 = viTriMax(a, left, mid);
    int i2 = viTriMax(a, mid + 1, right);

    return (a[i1] > a[i2]) ? i1 : i2;
}

/* d/e) Tìm dãy con có tổng lớn nhất (Maximum Subarray) */

/* Tìm tổng lớn nhất cắt qua mid */
int maxCrossingSum(int a[], int left, int mid, int right) {
    int sum = 0;
    int leftMax = INT_MIN;

    for (int i = mid; i >= left; i--) {
        sum += a[i];
        if (sum > leftMax)
            leftMax = sum;
    }

    sum = 0;
    int rightMax = INT_MIN;
    for (int i = mid + 1; i <= right; i++) {
        sum += a[i];
        if (sum > rightMax)
            rightMax = sum;
    }

    return leftMax + rightMax;
}

/* Hàm đệ quy chính */
int maxSubArray(int a[], int left, int right) {
    if (left == right)
        return a[left];

    int mid = (left + right) / 2;

    int maxLeft = maxSubArray(a, left, mid);
    int maxRight = maxSubArray(a, mid + 1, right);
    int maxCross = maxCrossingSum(a, left, mid, right);

    if (maxLeft >= maxRight && maxLeft >= maxCross)
        return maxLeft;
    else if (maxRight >= maxLeft && maxRight >= maxCross)
        return maxRight;
    else
        return maxCross;
}
int main() {
    int a[] = {1, 2, 2, 3, 5, -1, 4, -2, 6};
    int n = sizeof(a) / sizeof(a[0]);
    int x = 2;

    printf("Mang: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    int pos = timX(a, 0, n - 1, x);
    printf("a) Vi tri phan tu %d: %d\n", x, pos);
    printf("b) So lan xuat hien cua %d: %d\n", x, demX(a, 0, n - 1, x));
    int idxMax = viTriMax(a, 0, n - 1);
    printf("c) Phan tu lon nhat: %d tai vi tri %d\n", a[idxMax], idxMax);
    printf("d/e) Tong day con lon nhat: %d\n", maxSubArray(a, 0, n - 1));

    return 0;
}
