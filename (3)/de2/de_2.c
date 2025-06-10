//Đề 02 Sử dụng hàm và con trỏ trong ngôn ngữ C thực hiện
//1. Đọc ma trận số thực từ tệp và in ra màn hình.
//2. Sắp xếp từng dòng của ma trận theo thứ tự tăng dần.
//3. Tính tổng các phần tử phía dưới đường chéo chínhcủa ma trận.

#include <stdio.h>
#include <stdlib.h>

// Hàm hoán đổi 2 giá trị
void swap(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

// Hàm sắp xếp một dòng tăng dần bằng thuật toán selection sort
void sort_row(float *row, int cols) {
    for (int i = 0; i < cols - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < cols; j++) {
            if (row[j] < row[min_idx]) {
                min_idx = j;
            }
        }
        swap(&row[i], &row[min_idx]);
    }
}

// Hàm tính tổng các phần tử dưới đường chéo chính
float sum_below_diagonal(float **matrix, int rows, int cols) {
    float sum = 0;
    for (int i = 1; i < rows; i++) {
        for (int j = 0; j < i && j < cols; j++) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

// Hàm in ma trận
void print_matrix(float **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%6.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    FILE *fp = fopen("matran.txt", "r");
    if (fp == NULL) {
        printf("Không thể mở file!\n");
        return 1;
    }

    int rows, cols;
    fscanf(fp, "%d %d", &rows, &cols);

    // Cấp phát động cho ma trận
    float **matrix = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (float *)malloc(cols * sizeof(float));
    }

    // Đọc dữ liệu từ file
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fscanf(fp, "%f", &matrix[i][j]);

    fclose(fp);

    // In ma trận ban đầu
    printf("Ma tran ban dau:\n");
    print_matrix(matrix, rows, cols);

    // Sắp xếp từng dòng
    for (int i = 0; i < rows; i++) {
        sort_row(matrix[i], cols);
    }

    // In ma trận sau khi sắp xếp từng dòng
    printf("\nMa tran sau khi sap xep tung dong tang dan:\n");
    print_matrix(matrix, rows, cols);

    // Tính tổng phần tử dưới đường chéo chính
    float sum = sum_below_diagonal(matrix, rows, cols);
    printf("\nTong cac phan tu duoi duong cheo chinh: %.2f\n", sum);

    // Giải phóng bộ nhớ
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);

    return 0;
}