//Đề 15 Sử dụng hàm và con trỏ trong ngôn ngữ C thực hiện
//1. Đọc danh sách điểm (x, y) từ tệp.
//2. Tìm điểm ở góc phần tư thứ nhất.
//3. Tính trung bình cộng khoảng cách các điểm đến gốc tọa độ

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x, y;
} Point;

int readPoints(const char *filename, Point **points) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Không mở được tệp.\n");
        return 0;
    }
    int n;
    fscanf(f, "%d", &n);
    *points = (Point*)malloc(n * sizeof(Point));
    for (int i = 0; i < n; ++i) {
        fscanf(f, "%f%f", &((*points)[i].x), &((*points)[i].y));
    }
    fclose(f);
    return n;
}

void printFirstQuadrantPoints(Point *points, int n) {
    printf("Các điểm ở góc phần tư thứ nhất:\n");
    for (int i = 0; i < n; ++i) {
        if (points[i].x > 0 && points[i].y > 0) {
            printf("(%.2f, %.2f)\n", points[i].x, points[i].y);
        }
    }
}

float averageDistanceToOrigin(Point *points, int n) {
    float sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += sqrt(points[i].x * points[i].x + points[i].y * points[i].y);
    }
    return n ? sum / n : 0;
}

int main() {
    Point *points = NULL;
    int n = readPoints("input.txt", &points);
    if (n == 0) return 1;

    printFirstQuadrantPoints(points, n);

    float avg = averageDistanceToOrigin(points, n);
    printf("Trung bình cộng khoảng cách đến gốc tọa độ: %.2f\n", avg);

    free(points);
    return 0;
}