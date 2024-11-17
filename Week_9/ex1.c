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
#define USB_SIZE 32 * 1024 * 1024 // USB 32GB

typedef struct file_infor {
    char name[STR_LEN]; // File Name
    int size;           // File Size (Unit: KB)
    int timestamp;      // File Created how many days ago
    struct file_infor* next;
} fileNode;

typedef struct folder_struct {
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
    }
    int i;
    for ( i = 0; i < STR_LEN - 1 && name[i] != '\0'; i++)
    {
        newNode->name[i] = name[i];
    }
    newNode->name[i] = '\0';
    newNode->size = size;
    newNode->timestamp = timestamp;
    newNode->next = NULL;
    return newNode;
}

/**
 * @brief Inserts a new file into the folder linked list sorted by timestamp
 * 
 * @param head Pointer to the head of the folder linked list
 * @param name The name of the file to be inserted
 * @param size The size of the file to be inserted
 * @param timestamp The creation timestamp of the file to be inserted
 * 
 * This function creates a new file node with the given name, size, and timestamp, and
 * inserts it into the folder linked list at the correct position to maintain the
 * sorted order by timestamp.
 */
void insertFile(folderNode **head, const char* name, int size, int timestamp)
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

/**
 * @brief Calculates the total size of all files in a folder linked list
 * 
 * @param head Pointer to the head of the folder linked list
 * 
 * @return The total size of all files in the linked list
 * 
 * This function traverses the linked list, accumulating the size of each file,
 * and returns the total size of all files in the list.
 */
int calculateTotalSize(folderNode* head) {
    int totalSize = 0;
    while (head != NULL) {
        totalSize += head->file->size;
        head = head->next;
    }
    return totalSize;
}


/**
 * @brief Sorts the files in a folder linked list by size in descending order
 * 
 * @param head Pointer to the head of the folder linked list
 * 
 * This function uses a bubble sort algorithm to rearrange the files in the linked list
 * such that the files are ordered by their size from largest to smallest.
 * It iterates through the list, swapping adjacent file nodes if they are out of order,
 * and repeats the process until no more swaps are needed.
 */
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

/**
 * @brief Adjusts the list of files to fit within a USB size limit
 * 
 * @param head Pointer to the head of the folder linked list
 * 
 * This function sorts the files by size in descending order and attempts to fit them
 * into a USB drive of a predefined size limit. Files are added until the total size 
 * exceeds the USB size limit, at which point excess files are removed from the list.
 */
void fitIntoUSB(folderNode** head) {
    sort_file_by_size(head);

    int currentSize = 0;
    folderNode* current = *head;
    folderNode* prev = NULL;

    while (current != NULL) {
        if (currentSize + current->file->size <= USB_SIZE) {
            currentSize += current->file->size;
            prev = current;
            current = current->next;
        } else {
            folderNode* toDelete = current;
            current = current->next;
            if (prev != NULL) {
                prev->next = current;
            } else {
                *head = current;
            }
            free(toDelete->file);
            free(toDelete);
        }
    }
}

/**
 * @brief Prints the details of each file in the folder
 * 
 * @param head Pointer to the head of the folder linked list
 * 
 * @note This function traverses the linked list and prints the name,
 * size, and timestamp of each file node.
 */
void printList(folderNode* head) {
    while (head != NULL) {
        printf("File: %s, Size: %d, Timestamp: %d\n", head->file->name, head->file->size, head->file->timestamp);
        head = head->next;
    }
}

int main() {
    folderNode* head = NULL;

    // Adder file to Folder
    // (Total size > 32GB to test USB adder function)
    insertFile(&head, "file1", 10240, 3);
    insertFile(&head, "file2", 2048, 1);
    insertFile(&head, "file3", 5120, 4);
    insertFile(&head, "file4", 4096, 2);
    insertFile(&head, "file5", 81920, 5);
    insertFile(&head, "file6", 16384, 6);
    insertFile(&head, "file7", 32768, 7);
    insertFile(&head, "file8", 65536, 8);
    insertFile(&head, "file9", 131072, 9);
    insertFile(&head, "file10", 262144, 10);
    insertFile(&head, "file11", 524288, 11); 
    insertFile(&head, "file12", 1048576, 12); 
    
    printf("Folder before Sorting\n");
    printList(head);

    //Sort files in Folder by size
    sort_file_by_size(&head);
    printf("Folder after sorting\n");
    printList(head);

    //Copy file to USB 
    fitIntoUSB(&head);
    printf("Folder after fitting into USB\n");
    printList(head);

    return 0;
}




