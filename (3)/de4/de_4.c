//Đề 04 Sử dụng hàm và con trỏ trong ngôn ngữ C thực hiện
//1. Đọc tọa độ các điểm (x, y, z) từ tệp và in ra.
//2. Tính khoảng cách giữa các cặp điểm liên tiếp.
//3. Tìm căp điểm có khoảng cách xa nhất

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x, y, z;
} Point;

float distance(const Point *a, const Point *b) {
    return sqrtf((a->x - b->x)*(a->x - b->x) +
                 (a->y - b->y)*(a->y - b->y) +
                 (a->z - b->z)*(a->z - b->z));
}

void print_points(Point *points, int n) {
    printf("Danh sach cac diem:\n");
    for (int i = 0; i < n; ++i) {
        printf("Diem %d: (%.2f, %.2f, %.2f)\n", i+1, points[i].x, points[i].y, points[i].z);
    }
}

void print_distances(Point *points, int n) {
    printf("\nKhoang cach giua cac cap diem lien tiep:\n");
    for (int i = 0; i < n-1; ++i) {
        float d = distance(&points[i], &points[i+1]);
        printf("Diem %d va Diem %d: %.4f\n", i+1, i+2, d);
    }
}

void find_max_distance(Point *points, int n) {
    float max_dist = 0.0f;
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
    printf("\nCap diem co khoang cach xa nhat: Diem %d (%.2f, %.2f, %.2f) va Diem %d (%.2f, %.2f, %.2f)\n",
           idx1+1, points[idx1].x, points[idx1].y, points[idx1].z,
           idx2+1, points[idx2].x, points[idx2].y, points[idx2].z);
    printf("Khoang cach: %.4f\n", max_dist);
}

int main() {
    FILE *f = fopen("points.txt", "r");
    if (!f) {
        printf("Khong mo duoc tep points.txt\n");
        return 1;
    }
    int n;
    fscanf(f, "%d", &n);
    Point *points = (Point*)malloc(n * sizeof(Point));
    for (int i = 0; i < n; ++i) {
        fscanf(f, "%f%f%f", &points[i].x, &points[i].y, &points[i].z);
    }
    fclose(f);

    print_points(points, n);
    print_distances(points, n);
    find_max_distance(points, n);

    free(points);
    return 0;
}