// 5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include<omp.h>
#include <iostream>
#include<math.h>

int main() {
    int k, n;
    std::cin >> k >> n;

    int total_sum = 0;
    omp_set_num_threads(k);

#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int local_sum = 0;

#pragma omp for
        for (int i = 1; i <= n; i++) {
            local_sum += i;
        }
        printf("[%d]: sum = %d;\n", thread_id, local_sum);

#pragma omp atomic
        total_sum += local_sum;
    }
    printf("sum = %d;", total_sum);

    return 0;
}