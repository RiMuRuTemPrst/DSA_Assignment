/**
 * @file week_5.c
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief 
 * Bài 1:  Nhập vào n đối tượng có màu đỏ (red), trắng (white) và xanh (blue), sắp xếp theo trật tự như sau: các đối tượng cùng mầu nằm kế tiếp nhau và theo thứ tự đỏ, trắng, xanh.
Input {xanh, đỏ, xanh, đỏ, đỏ, trắng, đỏ, xanh, trắng}
Output {đỏ, đỏ, đỏ, đỏ, trắng, trắng, xanh, xanh, xanh}
Gợi ý:
Có thể mã hóa các mầu bằng các số nguyên 0, 1, 2 để biểu diễn lần lượt mầu đỏ, trắng và xanh tương ứng.
Chú ý: Không sử dụng các thư viện hàm sắp xếp có sẵn để giải quyết bài toán trên khi cài đặt chương trình

 * @version 0.1
 * @date 2024-10-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#define RED 0
#define WHITE 1
#define BLUE 2
/**
 * @brief Sort Colors 
 * 
 * @param arr: Array of Color
 * @param n: Number of Index
 * @output: Sorted Array
 */
void sort_Colors (int arr[], int n);
/**
 * @brief Print the array as color instead of number
 * 
 * @param arr: Array we want to print
 * @param n: Number of Index
 */
void print_colors(int arr[], int n);

int main()
{
    int arr[] = {BLUE, RED, BLUE, RED, RED, WHITE, RED, BLUE, WHITE};
    int n = sizeof(arr)/sizeof(arr[0]);

    sort_Colors(arr, n);
    print_colors(arr, n);
    
}

void sort_Colors (int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void print_colors (int arr[], int n)
{
    for (int i = 0; i < n; i++) 
    {
        if (arr[i] == 0) printf("RED ");
        else if (arr[i] == 1) printf("WHITE ");
        else if (arr[i] == 2) printf("BLUE ");
    }
}
