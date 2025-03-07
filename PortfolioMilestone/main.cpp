//
//  main.cpp
//  PortfolioMilestone
//
//  Created by Kaley Schlimgen on 3/6/25.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int counter = 0;
std::mutex counter_mutex;
std::condition_variable cv;
bool reached_20 = false;

void increment_counter() {
    std::lock_guard<std::mutex> lock(counter_mutex);
    std::cout << "First thread counting up to 20: " << std::endl;
    for (int i = 1; i <= 20; ++i) {
        counter = i;
        std::cout << counter << std::endl;
    }
    reached_20 = true;
    cv.notify_one();
}

void decrement_counter() {
    std::unique_lock<std::mutex> lock(counter_mutex);
    cv.wait(lock, [] { return reached_20; });
    
    std::cout << "\nSecond thread counting down to 1: " << std::endl;
    for (int i = 20; i > 0; --i) {
        counter = i;
        std::cout << counter << std::endl;
    }
}

int main() {
    std::thread firstThread(increment_counter);
    std::thread secondThread(decrement_counter);

    firstThread.join();
    secondThread.join();
    
    return 0;
}

