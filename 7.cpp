#include <iostream>
#include <omp.h>
#include <map>
#include <set>
#include <iomanip>
#include <cstdlib>

using namespace std;

typedef map<string, map<int, int>> statisic_map;

void run(const int k, const int n, statisic_map& stat_map)
{
    const char* omp_schedule = getenv("OMP_SCHEDULE");
    if (omp_schedule) {
        cout << "OMP_SCHEDULE = " << omp_schedule << "\n";
    } else {
        cout << "OMP_SCHEDULE is not set." << "\n";
    }

     int total_sum = 0;
     #pragma omp parallel num_threads(k)
    {
        int local_sum = 0; 
        #pragma omp for schedule(runtime) reduction(+:total_sum)
        for (int i = 1; i <= n; ++i)
        {   
            printf("[%d]: calculation of the iteration number %d\n", omp_get_thread_num(), i);
            stat_map[omp_schedule][i] = omp_get_thread_num();
            local_sum += i; // Каждый поток суммирует свои элементы
            total_sum += i; // Общая сумма (редукция)
        }

        printf("[%d]: Sum = %d\n", omp_get_thread_num(), local_sum);
    }

    printf("Sum = %d\n", total_sum);
}

void printStatisticTable(const statisic_map& data) {
    if (data.empty()) {
        cout << "No data to display." << "\n";
        return;
    }

    // Собираем все уникальные int-ключи (идентификаторы строк)
    set<int> all_row_ids;
    for (const auto& col : data) {
        for (const auto& row : col.second) {
            all_row_ids.insert(row.first);
        }
    }

    // Определяем ширину колонок
    const int KEY_WIDTH = 10;
    const int COLUMN_WIDTH = 15;

    // Вывод заголовков таблицы
    cout << left << setw(KEY_WIDTH) << "Iteration";
    for (const auto& col : data) {
        cout << setw(COLUMN_WIDTH) << col.first;
    }
    cout << "\n" << string(KEY_WIDTH + data.size() * COLUMN_WIDTH, '-') << "\n";

    // Вывод данных
    for (int row_id : all_row_ids) {
        cout << left << setw(KEY_WIDTH) << row_id;
        
        for (const auto& col : data) {
            auto it = col.second.find(row_id);
            if (it != col.second.end()) {
                cout << setw(COLUMN_WIDTH) << it->second;
            } else {
                cout << setw(COLUMN_WIDTH) << "-";
            }
        }
        cout << "\n";
    }
}



int main() 
{
    int k, n;
    cout << "Enter num_threads: ";
    cin >> k;
    cout << "Enter N: "; 
    cin >> n;
    statisic_map iterations_by_shedule_type;

    getenv("OMP_SCHEDULE");
    
    _putenv("OMP_SCHEDULE=static");
    run(k, n, iterations_by_shedule_type);

    _putenv("OMP_SCHEDULE=static,1");
    run(k, n, iterations_by_shedule_type);
    
    _putenv("OMP_SCHEDULE=static,2");
    run(k, n, iterations_by_shedule_type);

    _putenv("OMP_SCHEDULE=dynamic");
    run(k, n, iterations_by_shedule_type);

    _putenv("OMP_SCHEDULE=dynamic,2");
    run(k, n, iterations_by_shedule_type);

    _putenv("OMP_SCHEDULE=guided");
    run(k, n, iterations_by_shedule_type);

    _putenv("OMP_SCHEDULE=guided,2");
    run(k, n, iterations_by_shedule_type);
    
    printStatisticTable(iterations_by_shedule_type);
}