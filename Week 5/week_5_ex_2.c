/**
 * @file week_5_ex_2.c
 * @author Trương Quốc Ánh (anh.tq224430@sis.hust.edu.vn)
 * @brief 
 * Bài 2: Thiết kế giải thuật và cài đặt để tạo ra một mảng số nửa nguyên tố (Blum) nhỏ hơn một số N cho trước và thực hiện hai yêu cầu sau
- Tìm ra tất cả các cặp số Blum có tổng cũng là một số Blum nhỏ hơn N
- Kiểm tra xem một số Blum M có tồn tại trong dãy số Blum được tạo ra hay không
 * @version 0.1
 * @date 2024-10-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX 10000 // Maximum limit for N

/**
 * @brief Check a number is prime number or not
 * 
 * @param n: Number to check
 * @return true: Prime Number
 * @return false: Not a Prime Number
 */
bool isPrime(int n) 
{
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) 
    {
        if (n % i == 0) return false;
    }
    return true;
}

/**
 * @brief Check Blum
 * 
 * @param n: input number
 * @return true 
 * @return false 
 */
bool isBlum(int n) 
{
    for (int p = 2; p * p <= n; p++) 
    {
        if (isPrime(p) && p % 4 == 3) 
        {
            if (n % p == 0)
            {
                int q = n / p;
                if (q != p && isPrime(q) && q % 4 == 3) 
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// Function to generate an array of Blum integers less than N
int generateBlumNumbers(int N, int blumArray[]) 
{
    int count = 0;
    for (int i = 2; i < N; i++) 
    {
        if (isBlum(i)) 
        {
            blumArray[count++] = i;
        }
    }
    return count; 
}

// Function to check if a number is in the array
bool isNumberInArray(int arr[], int size, int num) 
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == num) 
        {
            return true;
        }
    }
    return false;
}

// Find pairs of Blum integers whose sum is also a Blum integer less than N
void findBlumPairs(int blumArray[], int count, int N) 
{
    printf("Pairs of Blum integers whose sum is also a Blum integer less than %d:\n", N);
    for (int i = 0; i < count; i++) 
    {
        for (int j = i + 1; j < count; j++) 
        {
            int sum = blumArray[i] + blumArray[j];
            if (sum < N && isBlum(sum)) 
            {
                printf("(%d, %d)\n", blumArray[i], blumArray[j]);
            }
        }
    }
}

// Main program
int main() {
    int N, M;
    int blumArray[MAX];
    
    printf("Enter N: ");
    scanf("%d", &N);
    
    // Generate the array of Blum integers less than N
    int count = generateBlumNumbers(N, blumArray);
    printf("Array of Blum integers less than %d:\n", N);
    for (int i = 0; i < count; i++) 
    {
        printf("%d ", blumArray[i]);
    }
    printf("\n");
    
    // Find pairs of Blum integers whose sum is also a Blum integer less than N
    findBlumPairs(blumArray, count, N);
    
    // Check if Blum integer M exists in the array
    printf("Enter Blum integer M to check: ");
    scanf("%d", &M);
    
    if (isNumberInArray(blumArray, count, M)) 
    {
        printf("%d exists in the Blum integer array.\n", M);
    } else 
    {
        printf("%d does not exist in the Blum integer array.\n", M);
    }
    
    return 0;
}


