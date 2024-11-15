/**
 * @file ex1.c
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief 1)  Bài 1: Định nghĩa một cấu trúc danh sách liên kết đơn để lưu trữ các file trong một thư mục D>Document trên máy tính. Các file được sắp xếp theo trật tự thời gian. Sau đó thực hiện tao tác:  

Khai báo cấu trúc của danh sách liên kết. Các thông tin chứa ở mỗi node sinh viên tự đưa vào để đảm bảo các nội dung sau được thực hiện 
Copy paste một file từ thư mục khác sang thư mục trên sao do file luôn được chèn vào theo trật tự thời gian  
Thực hiện tính toán kích thước các file trong thư mục 
Người ta muốn sao lưu các file trong thư mục trên vào một ổ USB có kích thước 32G. Hãy thực hiện loại bỏ dần nếu cần một số file có kích thước nhỏ nhất để có thể thực hiện được thao tác trên.  
 * @version 0.1
 * @date 2024-11-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define STR_LEN 50

/**
 * @brief Format of a file
 * 
 */
typedef struct file_infor
{
    char name[STR_LEN]; // File Name
    int size;           // File Size
    int timestamp;  // File Creation
    struct file_infor *next;
} fileNode;

/**
 * @brief Linked list folder contain Files
 * 
 */
typedef struct folder_struct
{
    fileNode *file;
    struct folder_struct *next;
} folderNode;

/**
 * @brief Create a new file node with given details
 * 
 * @param name The name of the file
 * @param size The size of the file
 * @param timestamp The creation timestamp of the file
 * @return Pointer to the newly created file node or NULL if memory allocation fails
 * 
 * This function allocates memory for a new file node, initializes its fields with
 * the provided name, size, and timestamp, and sets the next pointer to NULL.
 */
fileNode *createFileNode(char *name, int size, int timestamp)
{
    fileNode *newNode = (fileNode *)malloc(sizeof(fileNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
        exit(1);
    }
    int i;
    for ( i = 0; i < STR_LEN - 1 && name[i] != '\0'; i++)
    {
        newNode->name[i] = name[i];
    }
    newNode->name[i] = '\0';
    newNode ->size = size;
    newNode->timestamp = timestamp;
    newNode->next = NULL;
    return newNode;
}

void insertFIle (folderNode **head, const char* name, int size, int timestamp)
{
    fileNode* newFile = createFileNode(name, size, timestamp);
    folderNode* newNode = (folderNode*)malloc(sizeof(folderNode));
    newNode->file = newFile;
    newNode->next = NULL;

    if (*head == NULL || (*head)->file->timestamp > timestamp) 
    {
        newNode->next = *head;
        *head = newNode;
    } else 
    {
        folderNode* current = *head;
        while (current->next != NULL && current->next->file->timestamp <= timestamp) 
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}
int calculateTotalSize(folderNode* head) {
    int totalSize = 0;
    while (head != NULL) {
        totalSize += head->file->size;
        head = head->next;
    }
    return totalSize;
}

void sort_file_by_size(folderNode** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; 
    }

    int swapped;
    folderNode* ptr1;
    folderNode* lptr = NULL; 

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) { 
            if (ptr1->file->size < ptr1->next->file->size) {
                fileNode* tempFile = ptr1->file;
                ptr1->file = ptr1->next->file;
                ptr1->next->file = tempFile;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1; 
    } while (swapped);
}

void printList(folderNode* head) {
    while (head != NULL) {
        printf("File: %s, Size: %d, Timestamp: %d\n", head->file->name, head->file->size, head->file->timestamp);
        head = head->next;
    }
}

int main() {
    folderNode* head = NULL;

    // Thêm file vào danh sách
    insertFIle(&head, "hehe", 1024, 3);
    insertFIle(&head, "haha", 2048, 1);
    insertFIle(&head, "hihi", 512, 4);
    insertFIle(&head, "huhu", 4096, 2);
    insertFIle(&head, "hoho", 8192, 5);
    

    printf("Folder before Sorting\n");
    folderNode* current = head;
    printList(head);

    // Gọi hàm sắp xếp
    sort_file_by_size(&head);
    printf("Folder after sorting\n");
    printList(head);

    return 0;
}






