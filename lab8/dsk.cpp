#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <x86intrin.h>
#include <climits>

using namespace std;

const int MIN_CACHE_SIZE = 256; // 1 KB
const int MAX_CACHE_SIZE = 32 * 1024 * 1024; // 32 MB

void initialize_array(vector<int>& arr, const string& mode) {
    int n = arr.size();

    if (mode == "direct") {
        for (int i = 0; i < n; i++) {
            arr[i] = (i + 1) % n;
        }
    }
    else if (mode == "reverse") {
        for (int i = 0; i < n; i++) {
            arr[i] = (i - 1 + n) % n;
        }
    }
    else if (mode == "random") {
        vector<int> permutation(n);
        iota(permutation.begin(), permutation.end(), 0);

        random_device rd;
        mt19937 gen(rd());
        shuffle(permutation.begin(), permutation.end(), gen);

        for (int i = 0; i < n - 1; ++i) {
            arr[permutation[i]] = permutation[i + 1];
        }
        arr[permutation[n - 1]] = permutation[0];
    }
}

double measure_access_time(const vector<int>& arr, int iterations) {
    int n = arr.size();
    volatile int k = 0;

    // рогрев кэша - многократный проход
    for (int i = 0; i < n * 10; ++i) {
        k = arr[k];
    }

    uint64_t total_cycles = 0;
    const int steps = 1000000; // Фиксированное количество шагов

    for (int iter = 0; iter < iterations; iter++) {
        k = 0;
        uint64_t start = __rdtsc();

        // Измеряем время множественных обращений
        for (int i = 0; i < steps; i++) {
            k = arr[k];
        }

        uint64_t end = __rdtsc();
        total_cycles += (end - start);

        // Предотвращаем оптимизацию
        asm volatile("" : "+r" (k));
    }

    return (int)total_cycles / (iterations * steps);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <iterations>" << endl;
        return 1;
    }

    int iterations = stoi(argv[1]);

    cout << "Size(Bytes)\tDirect\tReverse\tRandom" << endl;

    int i = 0;
    for (int size_bytes = MIN_CACHE_SIZE; size_bytes <= MAX_CACHE_SIZE; size_bytes += 256 * i) {
        i ++;
        int size_elements = size_bytes / sizeof(int);

        if (size_elements < 1) continue;

        vector<int> arr(size_elements);

        cout << size_bytes << ": ";

        // Прямой обход
        initialize_array(arr, "direct");
        cout << measure_access_time(arr, iterations) << " ";

        // Обратный обход
        initialize_array(arr, "reverse");
        cout << measure_access_time(arr, iterations) << " ";

        // Случайный обход
        initialize_array(arr, "random");
        cout << measure_access_time(arr, iterations) << endl;
    }
    return 0;
}