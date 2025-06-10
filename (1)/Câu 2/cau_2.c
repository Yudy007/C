//Câu 2: Nhập ma trận nguyên vuông từ tệp. 
//in ma trận đọc được ra màn hình đồng thời in vào tệp. 
//Tính trung cộng các phần tử nằm phía dưới đường chéo chính và chia hết cho 3 hoặc 4. 
//Tính tổng của từng cột. Kết quả đó cũng in ra màn hình và in lên tệp

#include <stdio.h>
#define MAX 100

int main() {
    int n, i, j, matrix[MAX][MAX], sum = 0, count = 0;
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    if (!fin || !fout) return 1;

    fscanf(fin, "%d", &n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            fscanf(fin, "%d", &matrix[i][j]);

    printf("Ma tran:\n");
    fprintf(fout, "Ma tran:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
            fprintf(fout, "%d ", matrix[i][j]);
        }
        printf("\n");
        fprintf(fout, "\n");
    }


    sum = 0; count = 0;
    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (matrix[i][j] % 3 == 0 || matrix[i][j] % 4 == 0)
                sum += matrix[i][j], count++;

    double avg = count ? (double)sum / count : 0;
    printf("Trung cong: %.2lf\n", avg);
    fprintf(fout, "Trung cong: %.2lf\n", avg);


    for (j = 0; j < n; j++) {
        int col_sum = 0;
        for (i = 0; i < n; i++) col_sum += matrix[i][j];
        printf("Cot %d: %d\n", j + 1, col_sum);
        fprintf(fout, "Cot %d: %d\n", j + 1, col_sum);
    }

    fclose(fin); fclose(fout);
    return 0;
}
