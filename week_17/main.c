/**
 * @file main.c
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief Cài đặt cây AVL với các hàm theo yêu cầu sau:
Khai báo cấu trúc cây AVL
Cài đặt hàm thực hiện các phép xoay đơn, xoay kép để cân bằng cây 
Cài đặt hàm bổ sung thêm một node mới trên cây AVL 
Sử dụng mảng cho trên lớp để làm bộ kiểm tra đầu vào, in ra cây AVL theo từng bước bổ sung thêm phân tử theo các phép duyệt cây 
 * @version 0.1
 * @date 2024-12-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>

// define AVL struct
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;


/**
 * @brief Calculate the height of a given node in the AVL tree.
 * 
 * @param N Pointer to the node whose height is to be calculated.
 * @return int The height of the node. Returns 0 if the node is NULL.
 */

int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

/**
 * @brief Return the maximum of two integers.
 * 
 * @param a The first integer.
 * @param b The second integer.
 * @return int The maximum of the two integers.
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}


/**
 * @brief Create a new AVL tree node with the given data.
 * 
 * @param data The integer data to be stored in the node.
 * @return Node* Pointer to the newly created node.
 * 
 * This function allocates memory for a new node, initializes its data
 * with the given value, sets left and right children to NULL, and sets
 * the height to 1. It returns a pointer to the created node.
 */

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    return(node);
}


/**
 * @brief Performs a right rotation on the given subtree
 * 
 * @param y Pointer to the root of the subtree to be rotated
 * @return Node* Pointer to the new root after the rotation
 * 
 * This function performs a right rotation on the subtree rooted at the given node y.
 * It adjusts the pointers accordingly and updates the heights of the affected nodes.
 */

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Thực hiện xoay
    x->right = y;
    y->left = T2;

    // Cập nhật chiều cao
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;


    return x;
}


/**
 * @brief Performs a left rotation on the given subtree
 * 
 * @param x Pointer to the root of the subtree to be rotated
 * @return Node* Pointer to the new root after the rotation
 * 
 * This function performs a left rotation on the subtree rooted at the given node x.
 * It adjusts the pointers accordingly and updates the heights of the affected nodes.
 */

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Thực hiện xoay
    y->left = x;
    x->right = T2;

    // Cập nhật chiều cao
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;


    return y;
}
/**
 * @brief Get the balance factor of a given node in the AVL tree.
 * 
 * @param N Pointer to the node for which the balance factor is to be calculated.
 * @return int The balance factor of the node. A positive value indicates that the
 * left subtree is taller, a negative value indicates that the right subtree 
 * is taller, and zero indicates that both subtrees are of equal height.
 */

/**
 * @brief Calculates the balance factor of a given node in the AVL tree.
 * 
 * The balance factor is defined as the difference between the height of the
 * left subtree and the height of the right subtree. A positive value indicates
 * that the left subtree is taller, a negative value indicates that the right
 * subtree is taller, and zero indicates that both subtrees are of equal height.
 * 
 * @param N Pointer to the node for which the balance factor is to be calculated.
 * @return int The balance factor of the node.
 */
int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

/**
 * @brief Inserts a new node with the given data into the AVL tree.
 * 
 * @param node Pointer to the root of the current subtree.
 * @param data The data to be inserted into the tree.
 * @return Node* Pointer to the root of the modified subtree.
 * 
 * This function inserts a new node with the given data into the AVL tree rooted at the
 * current node. It performs the insertion as in a normal binary search tree and then
 * updates the height of the current node. It then checks the balance factor of the node
 * and performs the necessary rotations to rebalance the tree if required.
 */
Node* insert(Node* node, int data) {
    //Thực hiện chèn bình thường
    if (node == NULL)
        return(newNode(data));

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Dữ liệu đã tồn tại
        return node;

    //Cập nhật chiều cao của node ông cha
    node->height = 1 + max(height(node->left), height(node->right));

    //Lấy hệ số cân bằng của node tổ tiên để kiểm tra xem node có bị mất cân bằng không
    int balance = getBalance(node);

    // Nếu node bị mất cân bằng, có 4 trường hợp

    // Trường hợp Left Left
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Trường hợp Right Right
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Trường hợp Left Right
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Trường hợp Right Left
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }


    return node;
}


/**
 * @brief Prints the AVL tree in pre-order traversal
 * 
 * @param root Pointer to the root node of the AVL tree
 * 
 * @note This function performs a pre-order traversal, which visits the current node first,
 * then recursively visits the left subtree, followed by the right subtree. The data of
 * each node is printed in the order they are visited.
 */

void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}


/**
 * @brief Entry point of the program.
 * 
 * This function demonstrates the insertion of elements into the AVL tree.
 * It creates an empty AVL tree and then inserts elements from an array one by one.
 * After each insertion, it prints the current state of the AVL tree using the pre-order
 * traversal.
 * 
 * @return int Program exit status.
 */
int main() {
    Node* root = NULL;


    int arr[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(arr)/sizeof(arr[0]);

    
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
        printf("AVL tree after inserting %d: ", arr[i]);
        preOrder(root);
        printf("\n");
    }

    return 0;
}