/**
 * @file khogo.c
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief 
 * Bài tập: Kho gỗ:
- Quản lý kho gỗ bao gồm: Loại gỗ, Kích thước, tuổi gỗ
Cài đặt danh sách loại gỗ trong kho theo kiểu stack => Đếm số lượng thanh gỗ cùng tuổi gỗ

 * @version 0.1
 * @date 2024-11-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Struct of Wood
 * 
 */
typedef struct 
{
    char type[50];  // Type of Wood
    char size[20];  // Size of Wood (Area Unit: m^2)
    int age;        // Age of Wood
} Wood;

/**
 * @brief Struct of Node (List of Wood)
 * 
 */
typedef struct Node 
{
    Wood wood;
    struct Node *next;
} Node;

/**
 * @brief Initializes an empty stack
 * @return An empty stack
 */
Node* initStack() 
{
    return NULL;
}

/**
 * @brief Checks if the stack is empty
 * @param top Pointer to the top of the stack
 * @return int 1 if the stack is empty, 0 otherwise
 */
int isEmpty(Node *top) 
{
    return top == NULL;
}

// Hàm sao chép chuỗi
void copyString(char *dest, const char *src) 
{
    while ((*dest++ = *src++) != '\0');
}

// Thêm gỗ vào stack
void push(Node **top, Wood wood) 
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) 
    {
        printf("Memory allocation failed!\n");
        return;
    }
    copyString(newNode->wood.type, wood.type);
    copyString(newNode->wood.size, wood.size);
    newNode->wood.age = wood.age;
    newNode->next = *top;
    *top = newNode;
}

// Lấy gỗ ra khỏi stack
Wood pop(Node **top) 
{
    if (isEmpty(*top)) 
    {
        printf("Stack is empty!\n");
        Wood empty = {"", "", -1}; // Giá trị rỗng
        return empty;
    }
    Node *temp = *top;
    Wood wood = temp->wood;
    *top = temp->next;
    free(temp);
    return wood;
}

/**
 * @brief Count the Wooden sticks
 * 
 * @param top 
 * @param age 
 * @return int 
 */
int countByAge(Node *top, int age) 
{
    int count = 0;
    Node *current = top;
    while (current != NULL) {
        if (current->wood.age == age) 
        {
            count++;
        }
        current = current->next;
    }
    return count;
}

/**
 * @brief Print Stack of Wood
 * 
 * @param top 
 */
void printStack(Node *top) 
{
    Node *current = top;
    printf("List of Wood in Stack:\n");
    while (current != NULL) {
        printf("Type: %s, Size %s, Age: %d\n", 
            current->wood.type, current->wood.size, current->wood.age);
        current = current->next;
    }
}

int main() 
{
    Node *stack = initStack();

    // Thêm dữ liệu gỗ vào stack
    Wood wood1 = {"Wood 1", "8", 55};
    Wood wood2 = {"Wood 2", "10", 42};
    Wood wood3 = {"Wood 3", "12", 10};
    Wood wood4 = {"Wood 4", "5", 35};
    Wood Wood5 = {"Wood 5", "7", 10};

    push(&stack, wood1);
    push(&stack, wood2);
    push(&stack, wood3);
    push(&stack, wood4);
    push(&stack, Wood5);

    // In danh sách gỗ
    printStack(stack);

    // Example: Count number of Wooden Stick 10 years old
    int ageToCount = 10;
    int count = countByAge(stack, ageToCount);
    printf("Number of Wooden Stick 10 Years old %d: %d\n", ageToCount, count);

    return 0;
}
