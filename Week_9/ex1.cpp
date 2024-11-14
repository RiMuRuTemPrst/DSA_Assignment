/**
 * @file ex1.c
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief 1)     Bài 1: Định nghĩa một cấu trúc danh sách liên kết đơn để lưu trữ các file trong một thư mục D>Document trên máy tính. 
 * Các file được sắp xếp theo trật tự thời gian. Sau đó thực hiện tao tác:  

Khai báo cấu trúc của danh sách liên kết. Các thông tin chứa ở mỗi node sinh viên tự đưa vào để đảm bảo các nội dung sau được thực hiện 
Copy paste một file từ thư mục khác sang thư mục trên sao do file luôn được chèn vào theo trật tự thời gian  
Thực hiện tính toán kích thước các file trong thư mục 
Người ta muốn sao lưu các file trong thư mục trên vào một ổ USB có kích thước 32G. Hãy thực hiện loại bỏ dần nếu cần một số file có kích thước nhỏ nhất để có thể thực hiện được thao tác trên.  
 * @version 0.1
 * @date 2024-11-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#define STR_LEN 50

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(char *)str1 - *(char *)str2;
}

class FileData {
    public:
        char name[STR_LEN]; 
        int size; // Kích thước tính bằng MB
        FileData (char *name, int size) {
            int i = 0;
            while (name[i] != '\0') {
                this->name[i] = name[i];
                i++;
            }
            this->name[i] = '\0';
            this->size = size;  // Gán kích thước cho đối tượng.
        }
        ~FileData() {}
};

class FileNode {
    public: 
        FileNode *next; 
        FileData *data;
        FileNode (char *name, int size) {
            next = NULL;
            data = new FileData(name, size);  // Khởi tạo con trỏ dữ liệu.
        }
        ~FileNode() {
            if(next != NULL) delete next;
            if(data != NULL) delete data;
        }
}; 

class Directory {
    public:
        FileNode *head;
        FileNode *tail;
        char name[STR_LEN];

        Directory(char *name) {
            head = NULL;
            tail = NULL;
            int i = 0;
            while (name[i] != '\0') {
                this->name[i] = name[i];
                i++;
            }
            this->name[i] = '\0';
        }

        ~Directory() {
            if(head != NULL) delete head; 
            if(tail != NULL) delete tail;
        }

        // Hàm thêm file vào thư mục
        void addFile(FileNode *file) {
            if (this->head == NULL) {
                this->head = file;
                this->tail = file;
            } else {
                this->tail->next = file;
                this->tail = file;
            }
        }

        // Hàm in các file trong thư mục
        void printDirectory() {
            FileNode *current = this->head;
            while (current != NULL) {
                std::cout << current->data->name << " (" << current->data->size << " MB)" << std::endl;
                current = current->next;
            }
        }

        // Hàm xóa file trong thư mục
        void deleteFile(char *name) {
            FileNode *current = this->head;
            FileNode *prev = NULL; 

            if (this->head != NULL && strcmp(this->head->data->name, name) == 0) {
                this->head = this->head->next;
                if (this->head == NULL) this->tail = NULL;
                delete current;
                return;
            }

            while (current != NULL && strcmp(current->data->name, name) != 0) {
                prev = current;
                current = current->next;
            }

            if (current == NULL) return;
            prev->next = current->next;
            if (current == this->tail) this->tail = prev;
            delete current;
            return;
        }

        // Hàm tính tổng kích thước các file trong thư mục
        int getTotalSize() {
            if (this->head == NULL) return 0; 
            FileNode *current = this->head;
            int totalSize = 0; 
            while (current != NULL) {
                totalSize += current->data->size;
                current = current->next;
            }
            return totalSize; 
        }

        // Hàm tìm file trong thư mục
        FileNode *findFile(char *name) {
            FileNode *current = this->head; 
            while (current != NULL && strcmp(current->data->name, name) != 0) {
                current = current->next;
            }
            if (current == NULL) return NULL;
            return current;
        }

        // Hàm tìm file có kích thước nhỏ nhất
        FileNode* getSmallestFile() {
            FileNode *smallest = this->head;
            FileNode *current = this->head;
            while (current != NULL) {
                if (current->data->size < smallest->data->size) {
                    smallest = current;
                }
                current = current->next;
            }
            return smallest; 
        }
}; 

// Hàm sao chép file từ thư mục này sang thư mục khác
bool copyFile(char *filename, Directory *source, Directory *destination) {
    FileNode *file = source->findFile(filename);
    if (file == NULL) return false;
    FileNode *newFile = new FileNode(file->data->name, file->data->size);
    destination->addFile(newFile);
    return true;
}

// Hàm chuyển file vào USB với dung lượng tối đa
int transferToUSB(Directory *source, int maxSize) {
    int totalSize = source->getTotalSize(); 
    while (totalSize > maxSize) {
        FileNode *smallest = source->getSmallestFile(); 
        if (smallest == NULL) return -1; 
        totalSize -= smallest->data->size; 
        source->deleteFile(smallest->data->name);
    }
    if (totalSize == 0) return -1;
    return 0;
}

int main(int argc, char **argv) {
    int n, availableSize;  
    scanf("%d", &n);

    Directory *documentFolder = new Directory("document");
    Directory *backupFolder = new Directory("backup");

    for (int i = 0; i < n; i++) {
        char filename[STR_LEN];
        int size; 
        std::cin.ignore();
        fgets(filename, sizeof(filename), stdin);
        int j = 0; 
        while (filename[j] != '\0') {
            j++;
        }
        filename[j - 1] = '\0';  // Loại bỏ ký tự xuống dòng khỏi tên file.

        scanf("%d", &size); 
        
        FileNode *file = new FileNode(filename, size);
        documentFolder->addFile(file);
    }
    scanf("%d", &availableSize);
    std::cout << "Tổng kích thước thư mục document: " << documentFolder->getTotalSize() << " MB" << std::endl;

    std::cout << "Các file trong thư mục document: " << std::endl;
    documentFolder->printDirectory();

    documentFolder->deleteFile("Quoc");
    std::cout << "Các file trong thư mục document sau khi xóa: " << std::endl;
    documentFolder->printDirectory();

    copyFile("Anh", documentFolder, backupFolder); 
    
    std::cout << "Thư mục backup sau khi sao chép: " << std::endl;
    backupFolder->printDirectory();

    std::cout << "Sau khi chuyển file vào USB: " << std::endl;
    transferToUSB(documentFolder, availableSize);

    documentFolder->printDirectory();

    return 0;
}
