#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <cmath>
#include <mutex>
#include <iomanip>
#include <cstdint> 

const int MAX_NUM = 100000000; // 10^8

bool isPrime(int num)
{
    if (num <= 1) {
        return false; 
    }

    if (num == 2 || num == 3) {
        return true; 
    }

    if(num % 2 == 0){
        return false;
    }

    if (num % 2 == 0 || num % 3 == 0) {
        return false; 
    }

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

void threadPrimeCalculation(int start, int end, std::vector<int>& primes, std::mutex& mutex)
{
    for (int i = start; i <= end; ++i) {
        if (isPrime(i)) {
            std::lock_guard<std::mutex> lock(mutex);
            primes.push_back(i);
        }
    }
}

int main() {
    // start time
    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    std::vector<int> primes;
    std::mutex primesMutex;

    
    // the 8 threads each get equal section                                 
    for (int i = 0; i < 8; ++i) {
        int start = i * (MAX_NUM / 8) + 1;
        int end = (i + 1) * (MAX_NUM / 8);
        threads.emplace_back(threadPrimeCalculation, start, end, std::ref(primes), std::ref(primesMutex));
    }
        
    // join the threads together
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    // end time
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;

    // write results to primes.txt
    std::ofstream outputFile("primes.txt");
    if (outputFile.is_open()) {
        // outputs the duration, total primes, and sum of primes
        outputFile << "Duration (seconds): " << std::setprecision(6) << duration.count() << "\n";
        outputFile << "Total Primes: " << primes.size() << "\n";
        outputFile << "Sum of Primes: " << std::accumulate(primes.begin(), primes.end(), 0LL) << "\n\n";

        // outputs the  top ten maximum primes
        outputFile << "Top Ten Maximum Primes:\n";
        std::sort(primes.rbegin(), primes.rend());
        for (int i = 0; i < std::min(10, static_cast<int>(primes.size())); ++i) {
            outputFile << "Prime " << i + 1 << ": " << primes[i] << "\n";
        }

        outputFile.close();
        std::cout << "Results written to primes.txt\n";
    } else {
        std::cerr << "Unable to open primes.txt for writing\n";
    }

    return 0;
}

