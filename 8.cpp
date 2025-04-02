#include <iostream>
#include <iomanip>
#include <cmath>
#include <omp.h>

int main() {
    int N;
    // ввод точности вычисления
    std::cin >> N; 
    
    double sum = 0.0;
    const double h = 1.0 / N; 
    
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; ++i){

        double x = (i + 0.5) * h; 
        sum += 4.0 / (1.0 + x * x); 
    }
    
    double pi = sum * h; 
    std::cout << std::fixed << std::setprecision(10) << pi;
    
    return 0;
}