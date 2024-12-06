/**
 * @file main.c
 * @author Trương Quốc Ánh
 * @brief 
 * Dựng cây biểu thức 
Dựng cây biểu thức tương ứng với biểu thức cho trên bảng theo yêu cầu 
Các node cha lưu toán tử 
Các node lá lưu toán hạng 
Cài đặt cây biểu thức và in thứ tự các phần tử trong biểu thức theo 3 cách duyệt 
 
 * @version 0.1
 * @date 2024-12-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/**
 * @file main.c 
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief 
 *       -
        / \
        +   +
        / \ / \
    a  / c  *
    / \   / \
   5 b  ^  d  ^
/ \   / \
         c   8 e   1/2
 * @version 0.1
 * @date 2024-12-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
} Node;
/**
 * @brief Create a Node object
 * 
 * @param data 
 * @return Node* 
 */
Node* createNode (char data)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/**
 * @brief Prints the tree in pre-order traversal
 * 
 * @param node Pointer to the root node of the tree
 * 
 * @note This function prints the tree in pre-order traversal, i.e.,
 * parent node, left subtree, right subtree.
 */
void pre_order(Node* node)
{
    if (node == NULL) return;
    printf("%c ", node->data);
    pre_order(node->left);
    pre_order(node->right);
}


/**
 * @brief Prints the tree in post-order traversal
 * 
 * @param node Pointer to the root node of the tree
 * 
 * @note This function prints the tree in post-order traversal, i.e.,
 * left subtree, right subtree, parent node.
 */

void between_order(Node* node) 
{
    if (node == NULL) return;
    between_order(node->left);
    printf("%c ", node->data);
    between_order(node->right);
}



/**
 * @brief Prints the tree in post-order traversal
 * 
 * @param node Pointer to the root node of the tree
 * 
 * @note This function prints the tree in post-order traversal, i.e.,
 * left subtree, right subtree, parent node.
 */
void post_order(Node* node) 
{
    if (node == NULL) return;
    post_order(node->left);
    post_order(node->right);
    printf("%c ", node->data);
}
/**
 * @brief Frees all nodes in a binary tree
 * 
 * @param node Pointer to the root node of the tree to be freed
 * 
 * @note This function traverses the tree in post-order and frees memory
 * allocated for each node, ensuring that the entire tree is deallocated.
 */
void freeTree(Node* node)
{
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    // Xây dựng cây biểu thức
    Node* root = createNode('-');
    root->left = createNode('+');
    root->right = createNode('+');
    root->left->left = createNode('a');
    root->left->right = createNode('/');
    root->left->right->left = createNode('5');
    root->left->right->right = createNode('b');
    root->right->left = createNode('^');
    root->right->left->left = createNode('c');
    root->right->left->right = createNode('8');
    root->right->right = createNode('*');
    root->right->right->left = createNode('d');
    root->right->right->right = createNode('^');
    root->right->right->right->left = createNode('e');
    root->right->right->right->right = createNode('1/2');

    printf("Duyet tren");
    pre_order(root);
    printf("\n");

    printf("In-order traversal: ");
    between_order(root);
    printf("\n");

    printf("Post-order traversal: ");
    post_order(root);
    printf("\n");

    free(root);

    return 0;
}