#include <iostream>
#include <omp.h>

// int main()
// {
//     const unsigned int k = 2;
//     int n = 0;
//     std::cin >> n;

//     int sum = 0;
// #pragma omp parallel num_threads(k) reduction(+ : sum)
//     {
//         int thread_num = omp_get_thread_num();
//         if (thread_num == 0)
//         {
//             for (int i = 1; i <= n; i += 2)
//             {
//                 sum += i;
//             }
//             printf("[%d]: Sum = %d\n", thread_num, sum);
//         }
//         else if (thread_num == 1)
//         {
//             for (int i = 2; i <= n; i += 2)
//             {
//                 sum += i;
//             }
//             printf("[%d]: Sum = %d\n", thread_num, sum);
//         }
//     }
//     printf("Sum = %d", sum);
//     return 0;
// }

// Модификация алгоритма
int main()
{
    unsigned int k = 0;
    std::cout << "Enter number of threads: ";
    std::cin >> k;
    int n = 0;
    std::cout << "Enter N: ";
    std::cin >> n;

    int sum = 0;
#pragma omp parallel num_threads(k) reduction(+ : sum)
    {
        int thread_num = omp_get_thread_num();
        {
            for (int i = thread_num + 1; i <= n; i += k)
            {
                sum += i;
            }
            printf("[%d]: Sum = %d\n", thread_num, sum);
        }
    }
    printf("Sum = %d", sum);
    return 0;
}