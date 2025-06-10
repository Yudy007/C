//Đề 13 Sử dụng hàm và con trỏ trong ngôn ngữ C thực hiện 
//1. Đọc ma trận nhiệt độ từ tệp
//2. Tìm ngày có nhiệt độ cao nhất (theo dòng).
//3. Tính nhiệt độ trung bình của từng ngày.

#include <stdio.h>
#include <stdlib.h>

#define MAX_DAYS 100
#define MAX_HOURS 24

int read_matrix(const char *filename, float a[][MAX_HOURS], int *days, int *hours) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;
    fscanf(f, "%d%d", days, hours);
    for (int i = 0; i < *days; ++i)
        for (int j = 0; j < *hours; ++j)
            fscanf(f, "%f", &a[i][j]);
    fclose(f);
    return 1;
}

int find_max_day(float a[][MAX_HOURS], int days, int hours) {
    float max_temp = a[0][0];
    int max_day = 0;
    for (int i = 0; i < days; ++i) {
        for (int j = 0; j < hours; ++j) {
            if (a[i][j] > max_temp) {
                max_temp = a[i][j];
                max_day = i;
            }
        }
    }
    return max_day;
}

void avg_per_day(float a[][MAX_HOURS], int days, int hours, float *avg) {
    for (int i = 0; i < days; ++i) {
        float sum = 0;
        for (int j = 0; j < hours; ++j)
            sum += a[i][j];
        avg[i] = sum / hours;
    }
}

int main() {
    float a[MAX_DAYS][MAX_HOURS];
    int days, hours;
    if (!read_matrix("input.txt", a, &days, &hours)) {
        printf("Khong mo duoc tep!\n");
        return 1;
    }

    int max_day = find_max_day(a, days, hours);
    printf("Ngay co nhiet do cao nhat: %d\n", max_day + 1);

    float avg[MAX_DAYS];
    avg_per_day(a, days, hours, avg);
    printf("Nhiet do trung binh moi ngay:\n");
    for (int i = 0; i < days; ++i)
        printf("Ngay %d: %.2f\n", i + 1, avg[i]);

    return 0;
}