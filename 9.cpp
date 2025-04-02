#include <iostream>
#include<omp.h>
#include<vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }

    std::vector<std::vector<int>> b(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> b[i][j];
        }
    }

    std::vector<std::vector<int>> c(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
#pragma omp parallel reduction (+ : sum)
            {
#pragma omp for
                for (int m = 0; m < n; m++) {
                    sum += a[i][m] * b[m][j];
                }

            }
            c[i][j] = sum;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << c[i][j] << " ";
        }
        std::cout << "\n";
    }
}
