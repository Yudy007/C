//Đề 02 Sử dụng hàm và con trỏ trong ngôn ngữ C thực hiện
//1. Đọc tọa độ các điểm (x, y, z) từ tệp và in ra.
//2. Tính khoảng cách giữa các cặp điểm liên tiếp.
//3. Tìm cặp điểm có khoảng cách xa nhất.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x, y, z;
} Point;

float distance(Point *a, Point *b) {
    return sqrtf((a->x - b->x)*(a->x - b->x) +
                 (a->y - b->y)*(a->y - b->y) +
                 (a->z - b->z)*(a->z - b->z));
}

int read_points(const char *filename, Point **points) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;
    int n, i;
    fscanf(f, "%d", &n);
    *points = (Point*)malloc(n * sizeof(Point));
    for (i = 0; i < n; ++i) {
        fscanf(f, "%f%f%f", &((*points)[i].x), &((*points)[i].y), &((*points)[i].z));
    }
    fclose(f);
    return n;
}

void print_points(Point *points, int n) {
    printf("Danh sach cac diem:\n");
    for (int i = 0; i < n; ++i) {
        printf("Diem %d: (%.2f, %.2f, %.2f)\n", i+1, points[i].x, points[i].y, points[i].z);
    }
}

void print_distances(Point *points, int n) {
    printf("Khoang cach giua cac cap diem lien tiep:\n");
    for (int i = 0; i < n-1; ++i) {
        printf("Diem %d va Diem %d: %.4f\n", i+1, i+2, distance(&points[i], &points[i+1]));
    }
}

void find_max_distance(Point *points, int n) {
    float max_dist = 0;
    int idx1 = 0, idx2 = 1;
    for (int i = 0; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {
            float d = distance(&points[i], &points[j]);
            if (d > max_dist) {
                max_dist = d;
                idx1 = i;
                idx2 = j;
            }
        }
    }
    printf("Cap diem co khoang cach xa nhat: Diem %d (%.2f, %.2f, %.2f) va Diem %d (%.2f, %.2f, %.2f), khoang cach = %.4f\n",
        idx1+1, points[idx1].x, points[idx1].y, points[idx1].z,
        idx2+1, points[idx2].x, points[idx2].y, points[idx2].z,
        max_dist);
}

int main() {
    Point *points = NULL;
    int n = read_points("input.txt", &points);
    if (n == 0) {
        printf("Khong the mo tep hoac tep rong!\n");
        return 1;
    }
    print_points(points, n);
    print_distances(points, n);
    find_max_distance(points, n);
    free(points);
    return 0;
}