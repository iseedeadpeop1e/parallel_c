#include <iostream>
#include <omp.h>

const unsigned int k = 5;

int main()
{
#pragma omp parallel num_threads(k)
    {
        int total_threads = omp_get_num_threads();
        int thread_num = omp_get_thread_num();
        if (!(thread_num % 2)) // Модификация программы из второй части задания
            printf("I am %d thread from %d threads!\n", thread_num, total_threads);
    }
    return 0;
}
