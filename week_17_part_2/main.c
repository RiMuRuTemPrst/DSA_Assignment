/**
 * @file main.c
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief 
 * Ma trận lưu trữ đỉnh liền kề:
 *  0101101
 *  0011010
 *  0101011
 *  1010011
 *  0101011
 *  1110101
 *  0000100
 * Instructions
Cài đặt cấu trúc đồ thị cho trên bảng và thực hiện các hàm sau 
Nhập các đỉnh và liên kết của đồ thị G(V,E) 
Duyệt đồ thị theo 2 cách BFS, DFS và in thứ tự các đỉnh duyệt 

 *  
 * @version 0.1
 * @date 2025-01-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define V  7

// Ma trận lưu trữ đỉnh liền kề
int graph[V][V] = {
    {0, 1, 0, 1, 1, 0, 1},
    {0, 0, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 0, 1, 1},
    {0, 1, 0, 1, 0, 1, 1},
    {1, 1, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 1, 0, 0}
};


/**
 * @brief A utility function to perform a depth-first traversal of the graph.
 * 
 * @param[in] v The index of the current vertex to be visited.
 * @param[in,out] visited An array to keep track of which vertices have been visited.
 * The array is sized to V, and visited[i] is set to 1 if vertex i has been visited.
 * 
 * @note This function is a recursive helper for the DFS function, which
 * performs a depth-first traversal of the graph. This function visits a
 * vertex and all of its adjacent vertices before backtracking.
 */
void DFSUtil(int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", v);
    int i;
    for ( i = 0; i < V; i++) {
        if (graph[v][i] && !visited[i]) {
            DFSUtil(i, visited);
        }
    }
}

/**
 * @brief Performs a depth-first traversal of the graph starting from the given vertex.
 * 
 * @param[in] v The index of the starting vertex.
 * 
 * @note This function calls the DFSUtil helper to perform the actual traversal.
 */
void DFS(int v) {
    int visited[V] = {0};
    DFSUtil(v, visited);
}


/**
 * @brief Performs a breadth-first traversal of the graph starting from the given vertex.
 * 
 * @param[in] start The index of the starting vertex.
 * 
 * @note This function uses a queue to traverse the graph. It visits all of the
 * adjacent vertices to the current vertex before visiting any of the adjacent
 * vertices to the adjacent vertices.
 */
void BFS(int start) {
    int visited[V] = {0};
    int queue[V];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v);
        int i;
        for ( i = 0; i < V; i++) {
            if (graph[v][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}



int main() {
    printf("DFS algorithm: \n");
    DFS(0);
    printf("\n");

    printf("BFS algorithm: \n");
    BFS(0);
    printf("\n");

    return 0;
}