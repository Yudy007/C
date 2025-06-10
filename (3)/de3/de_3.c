//Đề 03 Sử dụng hàm và con trỏ trong ngôn ngữ C thực hiện
//1. Đọc danh sách nhân viên (mã NV, tên, lương) từ tệp và in ra.
//2. Thống kê số nhân viên có lương trên 10 triệu.
//3. Tìm nhân viên có lương thấp nhất.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NV 100
#define MAX_NAME 100

typedef struct {
    char maNV[20];
    char ten[MAX_NAME];
    float luong;
} NhanVien;

// Đọc danh sách nhân viên từ tệp
int docDanhSachNV(const char *filename, NhanVien *ds, int *n) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Không mở được tệp!\n");
        return 0;
    }
    *n = 0;
    while (fscanf(f, "%s %[^\n] %f", ds[*n].maNV, ds[*n].ten, &ds[*n].luong) == 3) {
        (*n)++;
        if (*n >= MAX_NV) break;
    }
    fclose(f);
    return 1;
}

// In danh sách nhân viên
void inDanhSachNV(NhanVien *ds, int n) {
    printf("%-10s %-30s %-10s\n", "MaNV", "Ten", "Luong");
    for (int i = 0; i < n; i++) {
        printf("%-10s %-30s %-10.2f\n", ds[i].maNV, ds[i].ten, ds[i].luong);
    }
}

// Đếm số nhân viên có lương trên 10 triệu
int demLuongTren10tr(NhanVien *ds, int n) {
    int dem = 0;
    for (int i = 0; i < n; i++) {
        if (ds[i].luong > 10000000)
            dem++;
    }
    return dem;
}

// Tìm nhân viên có lương thấp nhất
NhanVien* timLuongThapNhat(NhanVien *ds, int n) {
    if (n == 0) return NULL;
    NhanVien *minNV = &ds[0];
    for (int i = 1; i < n; i++) {
        if (ds[i].luong < minNV->luong)
            minNV = &ds[i];
    }
    return minNV;
}

int main() {
    NhanVien ds[MAX_NV];
    int n;
    char filename[100];

    printf("Nhap ten tep du lieu: ");
    scanf("%s", filename);

    if (!docDanhSachNV(filename, ds, &n)) {
        return 1;
    }

    printf("\nDanh sach nhan vien:\n");
    inDanhSachNV(ds, n);

    int soLuong = demLuongTren10tr(ds, n);
    printf("\nSo nhan vien co luong tren 10 trieu: %d\n", soLuong);

    NhanVien *nvMin = timLuongThapNhat(ds, n);
    if (nvMin) {
        printf("\nNhan vien co luong thap nhat:\n");
        printf("%-10s %-30s %-10.2f\n", nvMin->maNV, nvMin->ten, nvMin->luong);
    }

    return 0;
}