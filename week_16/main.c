/**
 * @file main.c
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief Mục lục của một cuốn sách được lưu trữ dưới dạng một cây trong đó mỗi node có thể là chapter, section, subsection, subsubsection.  
Khai báo cấu trúc cây để biểu diễn cuốn sách. Các thông tin chứa ở mỗi node sinh viên tự đưa vào để đảm bảo các nội dung sau được thực hiện:  
Xác định số chương của cuốn sách 
Tìm chương dài nhất của cuốn sách 
Thực hiện tìm một mục và xoá mục đó khỏi sách. Lưu ý cập nhật lại số trang của từng mục.  
 * @version 0.1
 * @date 2024-12-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the tree
typedef struct Node {
    char title[100];
    int pageCount;
    struct Node* firstChild;
    struct Node* nextSibling;
} Node;


/**
 * @brief Create a new node
 * 
 * @param title Title of the node
 * @param pageCount Number of pages in the node
 * @return Pointer to the newly created node
 * 
 * This function allocates memory for a new node, initializes its fields with
 * the provided title and page count, and sets the firstChild and nextSibling
 * pointers to NULL.
 */
Node* createNode(const char* title, int pageCount) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    int i = 0;
    while (title[i] != '\0' && i < 99) {
        newNode->title[i] = title[i];
        i++;
    }
    newNode->title[i] = '\0';
    newNode->pageCount = pageCount;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}


/**
 * @brief Adds a child node to the parent node
 * 
 * @param parent Pointer to the parent node to which the child will be added
 * @param child Pointer to the child node to be added
 * 
 * @note If the parent node has no children, the child node is added as the first child.
 * Otherwise, it is added as the last sibling of the existing children.
 */

void addChild(Node* parent, Node* child) {
    if (parent->firstChild == NULL) {
        parent->firstChild = child;
    } else {
        Node* temp = parent->firstChild;
        while (temp->nextSibling != NULL) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}

/**
 * @brief Counts the number of child nodes of the given node
 * 
 * @param root Pointer to the node whose children are to be counted
 * 
 * @return The number of child nodes
 * 
 * @note This function traverses the sibling list of the given node and
 * increments a counter for each child node it finds.
 */
int countChapters(Node* root) {
    int count = 0;
    Node* temp = root->firstChild;
    while (temp != NULL) {
        count++;
        temp = temp->nextSibling;
    }
    return count;
}


/**
 * @brief Finds the child node with the highest page count
 * 
 * @param root Pointer to the node whose children are to be searched
 * 
 * @return Pointer to the child node with the highest page count, or NULL if the
 * node has no children
 * 
 * @note This function traverses the sibling list of the given node and
 * compares the page count of each child node with the current highest page count.
 * If a child node has a higher page count, it becomes the new highest page count
 * node. The function returns the child node with the highest page count found.
 */
Node* findLongestChapter(Node* root) {
    Node* longest = NULL;
    Node* temp = root->firstChild;
    while (temp != NULL) {
        if (longest == NULL || temp->pageCount > longest->pageCount) {
            longest = temp;
        }
        temp = temp->nextSibling;
    }
    return longest;
}

/**
 * @brief Compares two strings for equality
 * 
 * @param str1 First string to compare
 * @param str2 Second string to compare
 * 
 * @return 1 if the strings are equal, 0 otherwise
 * 
 * @note This function compares two strings character by character until it finds a mismatch
 * or reaches the end of either string. If the strings are the same, it returns 1, otherwise 0.
 */
int compareStrings(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0;
        }
        i++;
    }
    return str1[i] == str2[i];
}

/**
 * @brief Removes a child node with the given title from the parent node
 * 
 * @param root Pointer to the parent node from which the child will be removed
 * @param title Title of the child node to be removed
 * 
 * @note This function traverses the sibling list of the parent node to find the child
 * node with the given title. If the child node is found, it is removed from the list
 * and its memory is freed.
 */
void removeNode(Node* root, const char* title) {
    Node* temp = root->firstChild;
    Node* prev = NULL;
    while (temp != NULL && !compareStrings(temp->title, title)) {
        prev = temp;
        temp = temp->nextSibling;
    }
    if (temp != NULL) {
        if (prev == NULL) {
            root->firstChild = temp->nextSibling;
        } else {
            prev->nextSibling = temp->nextSibling;
        }
        free(temp);
    }
}

int main() {
    // Example usage
    Node* root = createNode("Book", 0);
    Node* chapter1 = createNode("Chapter 1", 10);
    Node* chapter2 = createNode("Chapter 2", 20);
    Node* chapter3 = createNode("Chapter 3", 15);
    Node* chapter4 = createNode("Chapter 4", 25);
    Node* chapter5 = createNode("Chapter 5", 30);
    Node* chapter6 = createNode("Chapter 6", 5);
    Node* chapter7 = createNode("Chapter 7", 12);
    Node* chapter8 = createNode("Chapter 8", 18);
    Node* chapter9 = createNode("Chapter 9", 22);
    Node* chapter10 = createNode("Chapter 10", 8);

    addChild(root, chapter1);
    addChild(root, chapter2);
    addChild(root, chapter3);
    addChild(root, chapter4);
    addChild(root, chapter5);
    addChild(root, chapter6);
    addChild(root, chapter7);
    addChild(root, chapter8);
    addChild(root, chapter9);
    addChild(root, chapter10);

    printf("Number of chapters: %d\n", countChapters(root));
    Node* longest = findLongestChapter(root);
    if (longest != NULL) {
        printf("Longest chapter: %s with %d pages\n", longest->title, longest->pageCount);
    }

    removeNode(root, "Chapter 1");
    printf("Number of chapters after removal: %d\n", countChapters(root));

    return 0;
}