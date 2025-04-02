#include <iostream>
#include<omp.h>
#include <iomanip> 
#include <string>

int main()
{
    long double pi = 0;
    int n;
    std::cin >> n;

#pragma omp parallel
    {
        int s = omp_get_thread_num();
        long double local_pi = 0;
#pragma omp for
        for (int i = 0; i < n; ++i) {
            long double x = (i + 0.5) * 1 / n;
            local_pi += 4 / (1 + x * x);
        }

#pragma omp critical
        {
            pi += local_pi;
        }
    }

    long double result = pi / n;

    std::string str = std::to_string(n);
    int c = str.length();
    std::cout << std::fixed << std::setprecision(c);
    std::cout << result;
}
