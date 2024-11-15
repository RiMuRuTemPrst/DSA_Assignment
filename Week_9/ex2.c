/**
 * @file ex2.c
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief 
 * 2)   Bài 2: Một câu tiếng việt cấu thành từ nhiều từ khác nhau. Mỗi từ được lưu thành một node trong một danh sách liên kết đơn  

Khai báo cấu trúc danh sách liên kết. Các thông tin chứa ở mỗi node sinh viên tự đưa vào để đảm bảo các nội dung sau được thực hiện 
Xác định từ xuất hiện nhiều nhất trong câu  
Nếu xuất hiện từ láy (cấu thành từ hai từ giống nhau ví dụ: xanh xanh), thực hiện loại bỏ một từ 
Thực hiện đếm số từ vựng xuất hiện trong câu. 
 * @version 0.1
 * @date 2024-11-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>
/**
 * @brief 
 * 
 */
typedef struct Node {
    char word[50];
    int count;
    struct Node* next;
} Node;

/**
 * @brief Allocate memory for a node in a linked list and assign its data with  word
 * @param word Word to be assigned to the data of the node
 * @return pointer to the newly allocated node or  NULL if memory allocation failed
 * @note The newly allocated node is not linked to any other node in the linked list
 */
Node* createNode(const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    int i = 0;
    while (word[i] != '\0') {
        newNode->word[i] = word[i];
        i++;
    }
    newNode->word[i] = '\0';
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

/**
 * @brief Compare two words to see if they are the same 
 * @param word1 First word to compare
 * @param word2 Second word to compare
 * @return 1 if the words are the same, 0 if they are not
 * @note This function compares two words character by character until it finds a mismatch
 * or reaches the end of either string
 */
int compareWords(const char* word1, const char* word2) {
    int i = 0;
    while (word1[i] != '\0' && word2[i] != '\0') {
        if (word1[i] != word2[i]) {
            return 0; // Not the same word
        }
        i++;
    }
    return word1[i] == word2[i];
}


/**
 * @brief Add a word to the linked list of words
 * @param head Pointer to the head of the linked list
 * @param word Word to be added to the linked list
 * @note If the word already exists in the list, its count is incremented; otherwise, a new node is added at the end of the list
 */
void addWord(Node** head, const char* word) {
    Node* temp = *head;
    
    // If the list is empty, add the first node
    if (*head == NULL) {
        *head = createNode(word);
        return;
    }

    // Traverse the list to find if the word already exists
    while (temp) {
        if (compareWords(word, temp->word)) {
            temp->count++; // Increment the count if the word exists
            return;
        }
        if (temp->next == NULL) {
            break;
        }
        temp = temp->next;
    }

    // Add a new word at the end of the list if not found
    Node* newNode = createNode(word);
    temp->next = newNode;
}

/**
 * @brief Finds the node with the highest word count in the linked list
 * @param head Pointer to the head of the linked list
 * @return Pointer to the node with the highest word count
 * @note If the list is empty, returns NULL
 */
Node* findMostFrequentWord(Node* head) {
    Node* maxNode = head;
    while (head) {
        if (head->count > maxNode->count) {
            maxNode = head;
        }
        head = head->next;
    }
    return maxNode;
}

/**
 * @brief Remove duplicate consecutive words from the linked list
 * 
 * @param head Pointer to the head of the linked list
 * 
 * @note This function compares each word with the next one in the list,
 * removing the next word if they are the same, effectively ensuring that
 * all words in the list are unique in sequential order.
 */
void removeDuplicateWords(Node** head) {
    Node* current = *head;
    Node* prev = NULL;
    while (current && current->next) {
        if (compareWords(current->word, current->next->word)) {
            // If the next word is the same, remove it
            Node* duplicate = current->next;
            current->next = duplicate->next;
            free(duplicate);
        } else {
            current = current->next;
        }
    }
}

/**
 * @brief Counts the number of unique words in the linked list
 * @param head Pointer to the head of the linked list
 * @return Number of unique words in the linked list
 * @note This function traverses the list once and increments a counter for each
 * node, so the time complexity is O(n) where n is the length of the list.
 */
int countUniqueWords(Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

/**
 * @brief Prints the sentence after removing duplicate words
 * @param head Pointer to the head of the linked list
 * @note This function traverses the list once and prints each word
 * separated by a space, so the time complexity is O(n) where n is the
 * length of the list.
 */
void printSentence(Node* head) {
    printf("Cau sau khi bo tu lay: ");
    while (head) {
        printf("%s ", head->word);
        head = head->next;
    }
    printf("\n");
}


void processSentence(Node** head, char* sentence) {
    char word[50];
    int i = 0, j = 0;
    while (sentence[i] != '\0') {
        if (sentence[i] == ' ' || sentence[i] == '\n') {
            if (j > 0) {
                word[j] = '\0';
                addWord(head, word);
                j = 0;
            }
        } else {
            word[j++] = sentence[i];
        }
        i++;
    }
    if (j > 0) {
        word[j] = '\0';
        addWord(head, word);
    }
}

int main() {
    Node* head = NULL;
    char sentence[500];
    
    printf("Nhap cau: ");
    fgets(sentence, sizeof(sentence), stdin);
    
    int i = 0;
    while (sentence[i] != '\n' && sentence[i] != '\0') {
        i++;
    }
    sentence[i] = '\0';

    processSentence(&head, sentence);
    removeDuplicateWords(&head);
    
    Node* mostFrequent = findMostFrequentWord(head);
    int uniqueCount = countUniqueWords(head);
    
    printf("Tu xuat hien nhieu nhat: %s (%d lan)\n", mostFrequent->word, mostFrequent->count);
    printf("So tu vung trong cau: %d\n", uniqueCount);

    printSentence(head);
    
    return 0;
}
