//
//  main.cpp
//  PortfolioMilestone
//
//  Created by Kaley Schlimgen on 3/6/25.
//

#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex counter_mutex;

void increment_counter() {
    std::cout << "First thread that counts up to 20:" << std::endl;
    
    std::lock_guard<std::mutex> lock(counter_mutex);
    for (int i = 0; i < 20; ++i) {
        counter++;
        std::cout << counter << std::endl;
    }
}

void decrement_counter() {
    std::cout << "Second thread that counts down to 0:" << std::endl;
    
    std::lock_guard<std::mutex> lock(counter_mutex);
    for (int i = 20; i > 0; --i) {
        counter--;
        std::cout << counter << std::endl;
    }
}

int main() {
    std::thread firstThread(increment_counter);
    std::thread secondThread(decrement_counter);

    firstThread.join();
    secondThread.join();
    
    //std::cout << counter << std::endl;
    return 0;
}

