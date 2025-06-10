//Câu 1: Nhập dãy điểm x1,y1,...,xn,yn từ tệp.
//In dãy điểm ra màn hình. Tìm đoạn xa gốc tọa độ nhất.
//Đếm số điểm nằm ở góc phần tư thứ 2.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Point;


int is_in_quadrant_2(Point p) {
    return (p.x < 0 && p.y > 0);
}

int main() {
    FILE *f = fopen("input.txt", "r");
    if (!f) {
        printf("Không mở được file!\n");
        return 1;
    }

    int n, i, count_q2 = 0, max_idx = 0;
    fscanf(f, "%d", &n);
    Point *arr = (Point*)malloc(n * sizeof(Point));
    double max_dist = 0;

    for (i = 0; i < n; ++i) {
        fscanf(f, "%d%d", &arr[i].x, &arr[i].y);
    }
    fclose(f);

    printf("Danh sach diem:\n");
    for (i = 0; i < n; ++i) {
        printf("(%d, %d)\n", arr[i].x, arr[i].y);
    }


    for (i = 0; i < n; ++i) {
        double dist = sqrt(arr[i].x * arr[i].x + arr[i].y * arr[i].y);
        if (dist > max_dist) {
            max_dist = dist;
            max_idx = i;
        }
        if (is_in_quadrant_2(arr[i])) count_q2++;
    }

    printf("Diem xa goc toa do nhat: (%d, %d), khoang cach = %.2lf\n", arr[max_idx].x, arr[max_idx].y, max_dist);
    printf("So diem nam o goc phan tu thu 2: %d\n", count_q2);

    free(arr);
    return 0;
}