//Đề 01 Sử dụng hàm và con trỏ trong ngôn ngữ C thực hiện
//1. Đọc danh sách điểm (x, y) từ tệp và in ra màn hình.
//2. Tính khoảng cách đến gốc tọa độ cho từng điểm.
//3. Tìm điểm gần gốc tọa độ nhất.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x, y;
} Point;

int readPoints(const char *filename, Point **points) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Không mở được tệp!\n");
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

void printPoints(Point *points, int n) {
    printf("Danh sách điểm:\n");
    for (int i = 0; i < n; ++i) {
        printf("Điểm %d: (%.2f, %.2f)\n", i+1, points[i].x, points[i].y);
    }
}

float distanceToOrigin(Point *p) {
    return sqrt(p->x * p->x + p->y * p->y);
}

int findNearestPoint(Point *points, int n) {
    int idx = 0;
    float minDist = distanceToOrigin(&points[0]);
    for (int i = 1; i < n; ++i) {
        float dist = distanceToOrigin(&points[i]);
        if (dist < minDist) {
            minDist = dist;
            idx = i;
        }
    }
    return idx;
}

int main() {
    Point *points = NULL;
    int n = readPoints("input.txt", &points);
    if (n == 0) return 1;

    printPoints(points, n);

    printf("\nKhoảng cách đến gốc tọa độ:\n");
    for (int i = 0; i < n; ++i) {
        printf("Điểm %d: %.4f\n", i+1, distanceToOrigin(&points[i]));
    }

    int nearest = findNearestPoint(points, n);
    printf("\nĐiểm gần gốc tọa độ nhất: (%.2f, %.2f)\n", points[nearest].x, points[nearest].y);

    free(points);
    return 0;
}