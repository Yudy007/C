//Đề 01 Sử dụng hàm và con trỏ trong ngôn ngữ C thực hiện
//1. Đọc danh sách nhân viên (mã NV, tên, lương) từ tệp và in ra.
//2. Thống kê số nhân viên có lương trên 40 triệu.
//3. Tìm nhân viên có lương thấp nhất.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char maNV[20];
    char ten[100];
    float luong;
} NhanVien;

int docDanhSachNV(const char *filename, NhanVien *ds, int *n) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Không mở được file.\n");
        return 0;
    }
    *n = 0;
    while (fscanf(f, "%19[^/]/%99[^/]/%f\n", ds[*n].maNV, ds[*n].ten, &ds[*n].luong) == 3) {
        (*n)++;
    }
    fclose(f);
    return 1;
}


void inDanhSachNV(NhanVien *ds, int n) {
    printf("Danh sach nhan vien:\n");
    for (int i = 0; i < n; i++) {
        printf("%s/%s/%.2f\n", ds[i].maNV, ds[i].ten, ds[i].luong);
    }
}


int demLuongTren40tr(NhanVien *ds, int n) {
    int dem = 0;
    for (int i = 0; i < n; i++) {
        if (ds[i].luong > 40000000)
            dem++;
    }
    return dem;
}


int timLuongThapNhat(NhanVien *ds, int n) {
    if (n == 0) return -1;
    int minIdx = 0;
    for (int i = 1; i < n; i++) {
        if (ds[i].luong < ds[minIdx].luong)
            minIdx = i;
    }
    return minIdx;
}

int main() {
    NhanVien ds[100];
    int n;
    if (!docDanhSachNV("nhanvien.txt", ds, &n)) {
        return 1;
    }
    inDanhSachNV(ds, n);

    int soLuongTren40tr = demLuongTren40tr(ds, n);
    printf("So nhan vien co luong tren 40 trieu: %d\n", soLuongTren40tr);

    int idxMin = timLuongThapNhat(ds, n);
    if (idxMin != -1) {
        printf("Nhan vien co luong thap nhat: %s/%s/%.2f\n", ds[idxMin].maNV, ds[idxMin].ten, ds[idxMin].luong);
    }
    return 0;
}