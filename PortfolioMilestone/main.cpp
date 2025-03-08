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
    try {
        std::lock_guard<std::mutex> lock(counter_mutex);
        std::cout << "First Thread Counting Up to 20: " << std::endl;
        for (int i = 0; i <= 20; ++i) {
            counter = i;
            std::cout << counter << std::endl;
        }
        reached_20 = true;
        cv.notify_one();
    } catch (const std::exception& e) {
        std::cerr <<"Error in First Thread: " << e.what() << std::endl;
    }
}

void decrement_counter() {
    try {
        std::unique_lock<std::mutex> lock(counter_mutex);
        cv.wait(lock, [] { return reached_20; });
        
        std::cout << "\nSecond Thread Counting Down to 0: " << std::endl;
        for (int i = 20; i >= 0; --i) {
            counter = i;
            std::cout << counter << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in Second Thread: " << e.what() << std::endl;
    }
}

int main() {
    try {
        std::thread firstThread(increment_counter);
        std::thread secondThread(decrement_counter);
        
        firstThread.join();
        secondThread.join();
    } catch (const std::exception& e) {
        std::cerr << "Error in Main Class: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

