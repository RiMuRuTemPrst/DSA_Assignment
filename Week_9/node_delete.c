/**
 * @file node_delete.c
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief Cài đặt giải thuật xoá node trong 1 danh sách ở 3 vị trí: Đầu danh sách, cuối danh sách và sau 1 nodec cho trước 
 * @version 0.1
 * @date 2024-11-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

/**
 * @brief Allocate memory for a node in a linked list and assign its data with  data
 * @param data Data to be assigned to the node
 * @return Pointer to the newly allocated node or  NULL if memory allocation failed
 * @note The newly allocated node is not linked to any other node in the linked list
 */
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


/**
 * @brief Delete the first node in a linked list
 * 
 * @param head Pointer to the head of the linked list
 * 
 * @note This function deletes the first node in the linked list and
 * updates the head of the list to point to the next node if it exists.
 * If the list is empty, a message is printed and nothing is done.
 */
void deleteFirstNode(Node** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}


/**
 * @brief Delete the last node in a linked list
 * 
 * @param head Pointer to the head of the linked list
 * 
 * @note This function deletes the last node in the linked list and
 * updates the second to last node to have a NULL next pointer.
 * If the list is empty, a message is printed and nothing is done.
 * If the list has only one node, the node is deleted and the head of the list is set to NULL.
 */
void deleteLastNode(Node** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    Node* current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}


/**
 * @brief Deletes the node after a given node in a linked list
 * 
 * @param prevNode Previous node in the linked list
 * 
 * @note This function deletes the node after the given node and
 * updates the previous node to have the next pointer pointing to the node after the deleted node.
 * If the given node is NULL or if there is no node to delete after it, a message is printed and nothing is done.
 */
void deleteNodeAfter(Node* prevNode) {
    if (prevNode == NULL || prevNode->next == NULL) {
        printf("Previous node is NULL or there is no node to delete after it\n");
        return;
    }
    Node* temp = prevNode->next;
    prevNode->next = temp->next;
    free(temp);
}

/**
 * @brief Print the linked list for testing purposes
 * 
 * @param head Pointer to the head of the linked list
 */
void printList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    printf("Original list:\n");
    printList(head);

    deleteFirstNode(&head);
    printf("After deleting the first node:\n");
    printList(head);

    deleteLastNode(&head);
    printf("After deleting the last node:\n");
    printList(head);

    deleteNodeAfter(head->next); // Deleting node after the second node
    printf("After deleting the node after the second node:\n");
    printList(head);

    return 0;
}