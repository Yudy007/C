//Đề 12 Sử dụng hàm và con trỏ trong ngôn ngữ C thực hiện
//1. Đọc tọa độ các thiết bị (x, y) từ tệp và in ra.
//2. Đếm số thiết bị trong bán kính R từ gốc.
//3. Sắp xếp theo khoảng cách đến gốc tăng dần.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Device;

int readDevices(const char *filename, Device **devices) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Không mở được tệp.\n");
        return 0;
    }
    int n, i;
    fscanf(f, "%d", &n);
    *devices = (Device*)malloc(n * sizeof(Device));
    for (i = 0; i < n; ++i) {
        fscanf(f, "%lf%lf", &((*devices)[i].x), &((*devices)[i].y));
    }
    fclose(f);
    return n;
}

void printDevices(Device *devices, int n) {
    printf("Danh sách thiết bị:\n");
    for (int i = 0; i < n; ++i) {
        printf("Thiết bị %d: (%.2lf, %.2lf)\n", i+1, devices[i].x, devices[i].y);
    }
}

double distance(Device d) {
    return sqrt(d.x * d.x + d.y * d.y);
}

int countInRadius(Device *devices, int n, double R) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (distance(devices[i]) <= R)
            count++;
    }
    return count;
}

int cmp(const void *a, const void *b) {
    double da = distance(*(Device*)a);
    double db = distance(*(Device*)b);
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}

int main() {
    Device *devices = NULL;
    int n = readDevices("devices.txt", &devices);
    if (n == 0) return 1;

    printDevices(devices, n);

    double R;
    printf("Nhập bán kính R: ");
    scanf("%lf", &R);
    int count = countInRadius(devices, n, R);
    printf("Số thiết bị trong bán kính %.2lf là: %d\n", R, count);

    qsort(devices, n, sizeof(Device), cmp);
    printf("Danh sách thiết bị sau khi sắp xếp theo khoảng cách đến gốc:\n");
    printDevices(devices, n);

    free(devices);
    return 0;
}