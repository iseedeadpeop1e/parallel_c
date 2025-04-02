#include <iostream>
#include <omp.h>

int main()
{
    unsigned int k;
    std::cin >> k;
    int rank;
#pragma omp parallel private(rank) num_threads(k)
    {
        rank = omp_get_thread_num();
        printf("I am %d thread.\n", rank);
    }
    return 0;
}
