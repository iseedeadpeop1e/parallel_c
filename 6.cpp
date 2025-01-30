#include <iostream>
#include <omp.h>

using namespace std;

int main() 
{
    int k, n;

    cout << "Enter num_threads: ";
    cin >> k;
    cout << "Enter N: "; 
    cin >> n;

    int total_sum = 0;

    #pragma omp parallel num_threads(k)
    {
        int local_sum = 0;

        #pragma omp for reduction(+:total_sum)
        for (int i = 1; i <= n; ++i)
        {
            local_sum += i; // Каждый поток суммирует свои элементы
            total_sum += i; // Общая сумма (редукция)
        }

        printf("[%d]: Sum = %d\n", omp_get_thread_num(), local_sum);
    }

    printf("Sum = %d", total_sum);
}