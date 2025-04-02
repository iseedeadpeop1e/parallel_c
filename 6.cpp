#include <iostream>
#include <omp.h>

int main()
{
    unsigned int k = 0;
    std::cout << "Enter number of threads: ";
    std::cin >> k;
    int n = 0;
    std::cout << "Enter N: ";
    std::cin >> n;

    int sum = 0;
#pragma omp parralel for num_threads(k) reduction(+ : sum)
    {

        for (int i = 1; i <= n; i += 1)
        {
            sum += i;
        }
        printf("[%d]: Sum = %d\n", omp_get_thread_num(), sum);
    }
    printf("Sum = %d", sum);
    return 0;
}