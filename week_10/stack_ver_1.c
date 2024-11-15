/**
 * @file stack_ver_1.c
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief 
 * @version 0.1
 * @date 2024-11-15
 * 
 * @copyright Copyright (c) 2024
 * @note:Key Operations on Stack Data Structures
    Push: Adds an element to the top of the stack.
    Pop: Removes the top element from the stack.
    Peek: Returns the top element without removing it.
    IsEmpty: Checks if the stack is empty.
    IsFull: Checks if the stack is full (in case of fixed-size arrays). 
    Src: https://www.geeksforgeeks.org/stack-data-structure/?ref=header_outind#basic-operations-of-stack-data-structures
 */

#include <stdio.h>
#define MAX 100 

typedef struct 
{
    int data[MAX];
    int top;
} Stack;


/**
 * @brief Initialize the stack
 * 
 * @param s Pointer to the stack to be initialized
 * @note This function sets the top index of the stack to -1, indicating that the stack is empty
 */
void init(Stack *s) 
{
    s->top = -1;
}


/**
 * @brief Check if the stack is empty
 * 
 * @param s Pointer to the stack
 * @return int Returns 1 if the stack is empty, otherwise 0
 */
int isEmpty(Stack *s) 
{
    return s->top == -1;
}


/**
 * @brief Check if the stack is full
 * 
 * @param s Pointer to the stack
 * @return int Returns 1 if the stack is full, otherwise 0
 */
int isFull(Stack *s) 
{
    return s->top == MAX - 1;
}

/**
 * @brief Thêm một phần tử vào stack
 * 
 * @param s Stack sẽ được thêm phần tử
 * @param value Giá trị của phần tử cần thêm
 * 
 * @note Nếu stack đầy, sẽ in ra thông báo và không thêm gì
 */
void push(Stack *s, int value) 
{
    if (isFull(s)) {
        printf("Stack is full!\n");
        return;
    }
    s->data[++(s->top)] = value;
}


/**
 * @brief Remove and return the top element of the stack
 * 
 * @param s Pointer to the stack
 * @return int The top element of the stack, or -1 if the stack is empty
 */
int pop(Stack *s) 
{
    if (isEmpty(s)) 
    {
        printf("Stack is empty!\n");
        return -1;
    }
    return s->data[(s->top)--];
}


/**
 * @brief Get the top element of the stack without removing it
 * 
 * @param s Pointer to the stack
 * @return int The top element of the stack, or -1 if the stack is empty
 */
int peek(Stack *s) 
{
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return s->data[s->top];
}

int main() 
{
    Stack s;
    init(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("Top: %d\n", peek(&s)); 
    printf("Pop: %d\n", pop(&s)); 
    printf("Pop: %d\n", pop(&s)); 

    return 0;
}
