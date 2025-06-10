//Đề 14 Sử dụng hàm và con trỏ trong ngôn ngữ C thực hiện Cấu trúc sách
//1. Đọc danh sách sách (tên sách, năm xuất bản, số trang) từ tệp.
//2. Tìm sách xuất bản gần nhất.
//3. Thống kê số sách trên 300 trang.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_BOOKS 100

typedef struct {
    char title[MAX_TITLE];
    int year;
    int pages;
} Book;

int readBooks(const char *filename, Book *books, int *n) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Cannot open file %s\n", filename);
        return 0;
    }
    int count = 0;
    while (fgets(books[count].title, MAX_TITLE, f)) {
        books[count].title[strcspn(books[count].title, "\n")] = 0;
        if (fscanf(f, "%d", &books[count].year) != 1) break;
        if (fscanf(f, "%d", &books[count].pages) != 1) break;
        fgetc(f); 
        count++;
        if (count >= MAX_BOOKS) break;
    }
    fclose(f);
    *n = count;
    return 1;
}

Book* findNewestBook(Book *books, int n) {
    if (n == 0) return NULL;
    Book *newest = &books[0];
    for (int i = 1; i < n; i++) {
        if (books[i].year > newest->year) {
            newest = &books[i];
        }
    }
    return newest;
}

int countBooksOver300Pages(Book *books, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (books[i].pages > 300) count++;
    }
    return count;
}

int main() {
    Book books[MAX_BOOKS];
    int n;
    if (!readBooks("books.txt", books, &n)) {
        return 1;
    }

    printf("Danh sach sach:\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s | Nam: %d | So trang: %d\n", i+1, books[i].title, books[i].year, books[i].pages);
    }

    Book *newest = findNewestBook(books, n);
    if (newest) {
        printf("\nSach xuat ban gan nhat: %s | Nam: %d | So trang: %d\n", newest->title, newest->year, newest->pages);
    }

    int count = countBooksOver300Pages(books, n);
    printf("\nSo sach co tren 300 trang: %d\n", count);

    return 0;
}