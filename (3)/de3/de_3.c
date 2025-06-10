//Đề 03 Sử dụng hàm và con trỏ trong ngôn ngữ C thực hiện
//1. Đọc danh sách nhân viên (mã NV, tên, lương) từ tệp và in ra.
//2. Thống kê số nhân viên có lương trên 10 triệu.
//3. Tìm nhân viên có lương thấp nhất.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_LINE 200

typedef struct {
    char maNV[10];
    char ten[MAX_NAME];
    float luong;
} NhanVien;


int demSoDong(const char* tenFile) {
    FILE* f = fopen(tenFile, "r");
    if (!f) {
        printf("Không thể mở file %s\n", tenFile);
        exit(1);
    }
    int dem = 0;
    char buffer[MAX_LINE];
    while (fgets(buffer, sizeof(buffer), f)) {
        if (strlen(buffer) > 1) dem++;
    }
    fclose(f);
    return dem;
}


NhanVien* docDanhSachNV(const char* tenFile, int* soLuong) {
    *soLuong = demSoDong(tenFile);
    FILE* f = fopen(tenFile, "r");
    if (!f) {
        printf("Không thể mở file %s\n", tenFile);
        exit(1);
    }

    NhanVien* ds = (NhanVien*)malloc((*soLuong) * sizeof(NhanVien));
    char line[MAX_LINE];

    for (int i = 0; i < *soLuong; i++) {
        fgets(line, sizeof(line), f);
        line[strcspn(line, "\n")] = '\0'; // Xóa ký tự newline

        char* token = strtok(line, "/");
        if (token) strcpy(ds[i].maNV, token);

        token = strtok(NULL, "/");
        if (token) strcpy(ds[i].ten, token);

        token = strtok(NULL, "/");
        if (token) ds[i].luong = atof(token);
    }

    fclose(f);
    return ds;
}

void inDanhSach(NhanVien* ds, int soLuong) {
    printf("Danh sách nhân viên:\n");
    for (int i = 0; i < soLuong; i++) {
        printf("MaNV: %s\tTen: %s\tLuong: %.0f\n", ds[i].maNV, ds[i].ten, ds[i].luong);
    }
}

int demLuongCao(NhanVien* ds, int soLuong) {
    int dem = 0;
    for (int i = 0; i < soLuong; i++) {
        if (ds[i].luong > 10000000)
            dem++;
    }
    return dem;
}

NhanVien timLuongThapNhat(NhanVien* ds, int soLuong) {
    NhanVien min = ds[0];
    for (int i = 1; i < soLuong; i++) {
        if (ds[i].luong < min.luong)
            min = ds[i];
    }
    return min;
}

int main() {
    int soNV;
    NhanVien* danhSach = docDanhSachNV("nhanvien.txt", &soNV);

    inDanhSach(danhSach, soNV);

    int soLuongCao = demLuongCao(danhSach, soNV);
    printf("\nSố nhân viên có lương > 10 triệu: %d\n", soLuongCao);

    NhanVien minLuong = timLuongThapNhat(danhSach, soNV);
    printf("\nNhân viên có lương thấp nhất:\n");
    printf("MaNV: %s\tTen: %s\tLuong: %.0f\n", minLuong.maNV, minLuong.ten, minLuong.luong);

    free(danhSach);
    return 0;
}
