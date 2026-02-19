#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

std::vector<long long> fibCache;
std::mutex mtx;

long long fibonacci(size_t n) {

    {
        std::lock_guard<std::mutex> lock(mtx);
        if (fibCache[n] != 0 || n == 0)
            return fibCache[n];
    }

    long long result = fibonacci(n - 1) + fibonacci(n - 2);

    {
        std::lock_guard<std::mutex> lock(mtx);
        fibCache[n] = result;
    }

    return result;
}

void compute(long long n, long long& result) {
    result = fibonacci(n);
}

int main(int argc, const char* argv[]) {

    size_t n = 15;

    fibCache.resize(n + 1, 0);
    fibCache[0] = 0;
    if (n > 0) fibCache[1] = 1;

    long long r1 = 0;
    long long r2 = 0;

    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(compute, n - 1, std::ref(r1));
    std::thread t2(compute, n - 2, std::ref(r2));

    t1.join();
    t2.join();

    long long result = r1 + r2;

    std::cout<< n << "th number of fibonacci is: " << result << std::endl;

    return 0;
}
