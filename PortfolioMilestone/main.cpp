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
    std::lock_guard<std::mutex> lock(counter_mutex);
    for (int i = 0; i < 100; ++i) {
        counter++;
    }
}

int main() {
    std::thread firstThread(increment_counter);
    std::thread secondThread(increment_counter);

    firstThread.join();
    secondThread.join();
    
    std::cout << counter << std::endl;
    return 0;
}

