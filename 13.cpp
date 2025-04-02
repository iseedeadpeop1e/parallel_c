#include <iostream>
#include<omp.h>
#include<vector>
#include<chrono>

int main()
{
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = i;
        }
    }

    std::vector<std::vector<int>> b(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i][j] = j;
        }
    }

    auto t1 = std::chrono::steady_clock::now();
    std::vector<std::vector<int>> c(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
#pragma omp parallel num_threads(k) reduction (+ : sum)
            {
#pragma omp for
                for (int m = 0; m < n; m++) {
                    sum += a[i][m] * b[m][j];
                }

            }
            c[i][j] = sum;
        }
    }
    auto t2 = std::chrono::steady_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1);
    std::cout << dt.count() << " ";

    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << c[i][j] << " ";
        }
        std::cout << "\n";
    }*/

}
