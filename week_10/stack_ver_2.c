/**
 * @file stack_ver_2.c
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief 
 * @version 0.1
 * @date 2024-11-15
 * 
 * @copyright Copyright (c) 2024
 * @note: 
 * Key Operations on Stack Data Structures
Push: Adds an element to the top of the stack.
Pop: Removes the top element from the stack.
Peek: Returns the top element without removing it.
IsEmpty: Checks if the stack is empty.
IsFull: Checks if the stack is full (in case of fixed-size arrays).
 * Src: https://www.geeksforgeeks.org/stack-data-structure/?ref=header_outind#basic-operations-of-stack-data-structures
 */
#include <stdio.h>
#include <stdlib.h>


typedef struct Node 
{
    int data;
    struct Node *next;
} Node;




/**
 * @brief Initializes an empty stack
 * @return An empty stack
 */
Node* init() {
    return NULL;
}



/**
 * @brief Check if the stack is empty
 * @param top Pointer to the top of the stack
 * @return 1 if the stack is empty, 0 otherwise
 */
int isEmpty(Node *top) {
    return top == NULL;
}

/**
 * @brief Push a new element onto the stack
 * 
 * @param top Double pointer to the top of the stack
 * @param value The value to be pushed onto the stack
 * 
 * @note Allocates memory for a new node and assigns it the given value. 
 *       If memory allocation fails, prints an error message and does not modify the stack.
 */
void push(Node **top, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = *top;
    *top = newNode;
}


/**
 * @brief Removes and returns the top element of the stack
 * 
 * @param top Double pointer to the top of the stack
 * @return The top element of the stack, or -1 if the stack is empty
 * 
 * @note Removes the top element of the stack and returns its value. If the stack is empty, prints an error message and returns -1.
 */
int pop(Node **top) {
    if (isEmpty(*top)) {
        printf("Stack is empty!\n");
        return -1;
    }
    Node *temp = *top;
    int value = temp->data;
    *top = temp->next;
    free(temp);
    return value;
}


/**
 * @brief Get the top element of the stack without removing it
 * 
 * @param top Pointer to the top of the stack
 * @return The top element of the stack, or -1 if the stack is empty
 * 
 * @note Does not modify the stack. If the stack is empty, prints an error message and returns -1.
 */
int peek(Node *top) {
    if (isEmpty(top)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return top->data;
}


/**
 * @brief Frees all the memory allocated for the stack
 * 
 * @param top Double pointer to the top of the stack
 * 
 * @note Frees all the memory allocated for the stack by repeatedly popping the stack until it is empty.
 */
void freeStack(Node **top) {
    while (!isEmpty(*top)) {
        pop(top);
    }
}

int main() {
    Node *stack = init();

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top: %d\n", peek(stack)); // 30
    printf("Pop: %d\n", pop(&stack)); // 30
    printf("Pop: %d\n", pop(&stack)); // 20

    freeStack(&stack);
    return 0;
}
