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
 * @brief Allocate memory for a node in a linked list and assign its data with  coefficient and exponent
 * @param coefficient Coefficient of the term
 * @param exponent Exponent of the term
 * @return pointer to the newly allocated node or  NULL if memory allocation failed
 * @note The newly allocated node is not linked to any other node in the linked list
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
 * @brief Insert a node into the linked list in descending order of exponent
 * 
 * @param head: Pointer to the head of the linked list
 * @param coefficient: Coefficient of the term to be inserted
 * @param exponent: Exponent of the term to be inserted
 * 
 * @note If a node with the same exponent already exists, it will be inserted before it
 */
void insertNode(Node** head, int coefficient, int exponent) 
{
    Node* newNode = createNode(coefficient, exponent);
    if (*head == NULL || (*head)->exponent < exponent) 
    {
        newNode->next = *head;
        *head = newNode;
    } else {
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
 * @brief Prints the polynomial in the format ax^n + bx^(n-1) + ... + cx + d
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
            printf("%d", current->coefficient);
        } else if (current->exponent == 1) 
        {
            if (current->coefficient == 1) 
            {
                printf("x");
            } else {
                printf("%dx", current->coefficient);
            }
        } else 
        {
            if (current->coefficient == 1) {
                printf("x^%d", current->exponent);
            } else {
                printf("%dx^%d", current->coefficient, current->exponent);
            }
        }
        current = current->next;
    }
    printf("\n");
}


/**
 * @brief Add two polynomials and return the result as a linked list
 * 
 * @param poly1 The first polynomial
 * @param poly2 The second polynomial
 * @return The linked list representing the result of adding the two polynomials
 * 
 * @note The linked list is in descending order of exponent
 */
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;

    while (poly1 != NULL || poly2 != NULL) {
        int coef, exp;

        if (poly1 == NULL) {
            coef = poly2->coefficient;
            exp = poly2->exponent;
            poly2 = poly2->next;
        } else if (poly2 == NULL) {
            coef = poly1->coefficient;
            exp = poly1->exponent;
            poly1 = poly1->next;
        } else if (poly1->exponent > poly2->exponent) {
            coef = poly1->coefficient;
            exp = poly1->exponent;
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            coef = poly2->coefficient;
            exp = poly2->exponent;
            poly2 = poly2->next;
        } else {
            coef = poly1->coefficient + poly2->coefficient;
            exp = poly1->exponent;
            Node* temp1 = poly1;
            Node* temp2 = poly2;
            poly1 = poly1->next;
            poly2 = poly2->next;

            // Giải phóng bộ nhớ cho các node có hệ số bằng 0
            if (coef == 0) {
                free(temp1);
                free(temp2);
                continue;
            }
        }

        if (coef != 0) {
            insertNode(&result, coef, exp);
        }
    }

    return result;
}


void inputPolynomial(Node** poly) \
{
    int n;
    printf("Enter the number of the polynomial ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) 
    {
        int coefficient, exponent;
        printf("Enter the cofficient and exponent of term %d: ", i + 1);
        printf("\nCoefficient = ");
        scanf("%d", &coefficient);
        printf("Exponent = ");
        scanf("%d", &exponent);
        insertNode(poly, coefficient, exponent);
    }
}

int main() 
{
    Node* f = NULL;
    Node* g = NULL;

    printf("Enter the polynomial f(x):\n");
    inputPolynomial(&f);
    printf("Enter the polynomial g(x):\n");
    inputPolynomial(&g);

    printf("f(x) = "); 
    printPolynomial(f);

    printf("g(x) = ");
    printPolynomial(g);

    Node* h = addPolynomials(f, g);

    printf("h(x) = ");
    printPolynomial(h);

    return 0;
}
