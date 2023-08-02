// Module26.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <vector> 
#include <thread>
#include <numeric>

std::vector<int> createVector(int N) {
    std::vector<int> vec(N);
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        vec[i] = rand();
    }
    return vec;
}

// Функция, выполняемая каждым потоком
void calculateSum(const std::vector<int>& arr, int startIndex, int endIndex, long long& sum) {
    sum = std::accumulate(arr.begin() + startIndex, arr.begin() + endIndex, 0);
}

int main() {
    const int N = 20; // Размер массива
    const int M = 4; // Количество потоков
    std::vector<int> arr = createVector(N);

    std::vector<std::thread> threads(M);
    std::vector<long long> partialSums(M);
    int partSize = N / M;
    int startIndex = 0;
    int endIndex = partSize;

    // Создание и запуск потоков
    for (int i = 0; i < M; i++) {
        if (i == M - 1) {
            endIndex = N; // Последний поток обрабатывает оставшуюся часть массива
        }

        threads[i] = std::thread(calculateSum, std::ref(arr), startIndex, endIndex, std::ref(partialSums[i]));

        startIndex = endIndex;
        endIndex += partSize;
    }

    // Ожидание завершения всех потоков
    for (int i = 0; i < M; i++) {
        threads[i].join();
    }

    // Вычисление общей суммы
    long long totalSum = std::accumulate(partialSums.begin(), partialSums.end(), 0);

    std::cout << "Total sum: " << totalSum << std::endl;

    return 0;
}

