/**
 * @file Excercise 1
 * @author Truong Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief 
 * Quản lý sinh viên của một trường đại học dùng danh sách liên kết đơn. Mỗi sinh viên có nhiều thông tin cần quản lý, tuy nhiên,
 * trong bài tập này, để cho đơn giản ta chỉ quản lý các thông tin sau: Mã sinh viên, 
 * họ tên, giới tính, ngày tháng năm sinh, địa chỉ, lớp và khoa. Viết chương trình cài đặt thực hiện các yêu cầu sau
 * 1. Khai báo cấu trúc dữ liệu cho bài toán.


2. Nhập vào Danh sách sinh viên ListSV, và in ra Danh sách sinh viên được sắp xếp tăng dần theo mã sinh viên. 
Hãy viết hàm thêm một sinh viên mới vào danh sách ListSV đã sắp xếp và SV được sắp xếp theo đúng thứ tự ở DS mới.

3. In ra các sinh viên có cùng ngày sinh, nếu không tìm thấy sinh viên có cùng ngày sinh thì in thông báo “không tìm thấy sinh viên cùng ngày sinh”

4. Loại bỏ các sinh viên có cùng ngày sinh ra khỏi danh sách ListSV
 * @version 0.1
 * @date 2024-10-25
 * @note Em xin phép typedef lại tên Struct cô đã khai báo để quen với thói quen code hằng ngày của em ạ.
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct Ngay
{
    int ngay, thang, nam;
}date;


typedef struct SinhVien
{
    char maSV[8];
    char hoTen[50];
    int gioitinh;
    date ngaysinh;
    char diachi[100];
    char lop[12];
    char khoa[7];
}student;

struct Node {
    student data;          
    struct Node* next;
};

typedef struct List
{
    struct Node *first;
    struct Node *last;
}list;


/**
 * Enter Student Information
 * @param sv Pointer to Student Object
 */
void inputStudent(student *sv) {
    /**Enter Student Code */
    printf("Nhap ma SV: ");
    gets(sv->maSV);
    /**Enter Student Name */
    printf("Nhap ho ten: ");
    getchar(); // Clear buffer
    gets(sv->hoTen);
    /**Enter Student Gender */
    printf("Nhap gioi tinh (1-Nam, 0-Nu): ");
    scanf("%d", &sv->gioitinh);
    /**Enter Student Birthday */
    printf("Nhap ngay sinh (dd mm yyyy): ");
    scanf("%d %d %d", &sv->ngaysinh.ngay, &sv->ngaysinh.thang, &sv->ngaysinh.nam);
    /**Enter Student Address */
    printf("Nhap dia chi: ");
    getchar(); // Clear buffer
    gets(sv->diachi);
    /**Enter Student Class */
    printf("Nhap lop: ");
    gets(sv->lop);
    /**Enter Student Major */
    printf("Nhap khoa: ");
    gets(sv->khoa);
}



/**
 * @brief Initialize a linked list with a given pointer to the list
 * @param lst Pointer to the linked list to be initialized
 * @note This function sets the first and last pointers of the list to NULL
 */
void initList(list* lst) 
{
    /**Pointer to Null when initialize */
    lst->first = lst->last = NULL;
}

/**
 * @brief Allocate memory for a node in a linked list and assign its data with  sv
 * @param sv student structure
 * @return pointer to the newly allocated node or  NULL if memory allocation failed
 * @note The newly allocated node is not linked to any other node in the linked list
 */
struct Node* createNode(student sv) 
{
    /**Create a new Node */
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    /**data of the new Node (struct SV) */
    newNode->data = sv;
    /**next of the new Node is NULL */
    newNode->next = NULL;
    return newNode;
}
/**Compare 2 string */
/**
 * @brief Idea is minus each character of 2 string, if 2 string is the same we will have 00000000000000....
 */
int compare(student sv1, student sv2) {
    int i = 0;
    while (sv1.maSV[i] != '\0' && sv2.maSV[i] != '\0') {
        if (sv1.maSV[i] != sv2.maSV[i]) {
            return sv1.maSV[i] - sv2.maSV[i];
        }
        i++;
    }
    return sv1.maSV[i] - sv2.maSV[i];
}

/**Add New Student */
void addStudent(list* lst, student sv) {
    struct Node* newNode = createNode(sv);
    if (lst->first == NULL) {
        lst->first = lst->last = newNode;
    } else {
        lst->last->next = newNode;
        lst->last = newNode;
    }
}
/**Sort Student by Student Code */
void sortListByMaSV(list* lst) {
    if (lst->first == NULL || lst->first->next == NULL) {
        return; //Dont' need to sort if just 1 elements
    }
    struct Node *i, *j;
    student temp;
    for (i = lst->first; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (compare(i->data, j->data) > 0) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// Hàm thêm sinh viên vào danh sách đã sắp xếp theo MSSV và sắp xếp lại
void addStudentAndSort(list* lst, student sv) {
    addStudent(lst, sv); // Thêm sinh viên mới vào cuối danh sách
    sortListByMaSV(lst); // Sắp xếp lại danh sách theo MSSV
}

// Hàm in thông tin sinh viên
void printStudent(student sv) {
    printf("MaSV: %s, HoTen: %s, GioiTinh: %s, NgaySinh: %02d/%02d/%04d, DiaChi: %s, Lop: %s, Khoa: %s\n",
        sv.maSV, sv.hoTen, sv.gioitinh ? "Nam" : "Nu", sv.ngaysinh.ngay, sv.ngaysinh.thang, sv.ngaysinh.nam,
        sv.diachi, sv.lop, sv.khoa);
}

// Hàm in danh sách sinh viên
void printList(list lst) {
    struct Node* current = lst.first;
    while (current != NULL) {
        printStudent(current->data);
        current = current->next;
    }
}



int main() {
    list lst;
    initList(&lst);
    int n, i;
    student sv;

    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);

    // Nhập danh sách sinh viên
    for (i = 0; i < n; i++) {
        printf("\nNhap thong tin sinh vien thu %d:\n", i + 1);
        inputStudent(&sv);
        addStudent(&lst, sv);
    }

    // Sắp xếp danh sách sinh viên theo mã sinh viên
    sortListByMaSV(&lst);

    // In danh sách sinh viên đã sắp xếp theo mã sinh viên
    printf("\nDanh sach sinh vien da sap xep theo ma sinh vien:\n");
    printList(lst);

    // Thêm sinh viên mới vào danh sách và sắp xếp lại
    printf("\nNhap thong tin sinh vien moi can them:\n");
    inputStudent(&sv);
    addStudentAndSort(&lst, sv);

    // In lại danh sách sinh viên sau khi thêm và sắp xếp
    printf("\nDanh sach sinh vien sau khi them va sap xep lai:\n");
    printList(lst);

    return 0;
}
