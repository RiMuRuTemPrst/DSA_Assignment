/**
 * @file main.c
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief Cài đặt giải thuật để nhập và in ra hai đa thức theo định dạng như sau:
f(x) = x^10 + 1;
g(x) = x^15 + x^7 + x^2 + 1; 
In ra tổng của 2 đa thức h(x) = f(x) + g(x) (*)
Ưu tiên cài đặt CTDL và giải thuật để sử dụng bộ nhớ tối ưu nhất  
 * @version 0.1
 * @date 2024-11-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Stuct Node
 * 
 */
typedef struct Node 
{
    int coefficient;
    int exponent;
    struct Node* next;
} Node;


/**
 * @brief Tạo một node trong danh sách liên kết
 * 
 * @param coefficient Hệ số của đa thức
 * @param exponent Mũ của đa thức
 * 
 * @return Node* con trỏ đến node mới được tạo
 */
Node* createNode(int coefficient, int exponent) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;
    return newNode;
}


/**
 * @brief Insert a node into the linked list in ascending order of exponent
 * 
 * @param head Head of the linked list
 * @param coefficient Coefficient of the polynomial
 * @param exponent Exponent of the polynomial
 * 
 * @note The time complexity of this function is O(n) where n is the length of the linked list
 */
void insertNode(Node** head, int coefficient, int exponent) 
{
    Node* newNode = createNode(coefficient, exponent);
    if (*head == NULL || (*head)->exponent < exponent) 
    {
        newNode->next = *head;
        *head = newNode;
    } else
    {
        Node* current = *head;
        while (current->next != NULL && current->next->exponent > exponent) 
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}


/**
 * @brief print the polynomial
 * 
 * @param head: First node in the linked list
 * 
 * @note Print the polynomial in the following format: ax^n + bx^(n-1) + ... + cx + d
 */
void printPolynomial(Node* head)
{
    Node* current = head;
    while (current != NULL) {
        if (current->coefficient > 0 && current != head)
        {
            printf(" + ");
        }
        if (current->exponent == 0) 
        {
            printf(" %d", current->coefficient);
        } else if (current->exponent == 1) 
        {
            if (current->coefficient == 1)
            {
                printf(" x");
            }
            else printf(" %dx", current->coefficient);
        } else 
        {   
            if (current->coefficient == 1)
            {
                printf(" x^%d", current->exponent);
            }
            else
            printf(" %dx^%d", current->coefficient, current->exponent);
        }
        current = current->next;
    }
    printf("\n");
}


/**
 * @brief Tinh tong hai da thuc
 * 
 * @param poly1 da thuc thu nhat
 * @param poly2 da thuc thu hai
 * 
 * @return da thuc tong
 * 
 * @note chay tuong tu nhu merge sort
 */
Node* addPolynomials(Node* poly1, Node* poly2) 
{
    Node* result = NULL;
    while (poly1 != NULL || poly2 != NULL) 
    {
        int coef, exp;
        if (poly1 == NULL) 
        {
            coef = poly2->coefficient;
            exp = poly2->exponent;
            poly2 = poly2->next;
        } else if (poly2 == NULL) 
        {
            coef = poly1->coefficient;
            exp = poly1->exponent;
            poly1 = poly1->next;
        } else if (poly1->exponent > poly2->exponent) 
        {
            coef = poly1->coefficient;
            exp = poly1->exponent;
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) 
        {
            coef = poly2->coefficient;
            exp = poly2->exponent;
            poly2 = poly2->next;
        } else 
        {
            coef = poly1->coefficient + poly2->coefficient;
            exp = poly1->exponent;
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
        insertNode(&result, coef, exp);
    }
    return result;
}

int main() 
{
    Node* f = NULL;
    Node* g = NULL;

    insertNode(&f, 5, 10);
    insertNode(&f, 1, 0);

    insertNode(&g, 10, 15);
    insertNode(&g, -2, 7);
    insertNode(&g, 3, 2);
    insertNode(&g, -7, 0);

    printf("f(x) = ");
    printPolynomial(f);

    printf("g(x) = ");
    printPolynomial(g);

    Node* h = addPolynomials(f, g);

    printf("h(x) = ");
    printPolynomial(h);

    return 0;
}
