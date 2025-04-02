#include <iostream>
#include <omp.h>


int main() {
    const int k = 4;  // потоков
    const int N = 10; // итераций

    std::cout << "Running with " << k << " threads and " << N << " iterations\n";

    int sum = 0;

    #pragma omp parallel for num_threads(k) reduction(+:sum) schedule(static)
    // #pragma omp parallel for num_threads(k) reduction(+:sum) schedule(static, 1)
    // #pragma omp parallel for num_threads(k) reduction(+:sum) schedule(static, 2)
    // #pragma omp parallel for num_threads(k) reduction(+:sum) schedule(dynamic)
    // #pragma omp parallel for num_threads(k) reduction(+:sum) schedule(dynamic, 2)
    // #pragma omp parallel for num_threads(k) reduction(+:sum) schedule(guided)
    // #pragma omp parallel for num_threads(k) reduction(+:sum) schedule(guided, 2)
    for (int i = 1; i <= N; i++) {
        sum += i;
        printf("[%d]: calculation of the iteration number %d\n", omp_get_thread_num(), i);
    }

    std::cout << "Final sum = " << sum << std::endl;
}