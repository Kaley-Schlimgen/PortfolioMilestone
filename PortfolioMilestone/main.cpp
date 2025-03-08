/*
*  main.cpp
*  PortfolioMilestone
*
* Created by Kaley Schlimgen on 3/6/25.
*
*  Program:
*  Create a C++ program that will exhibit concurrency concepts.
*  Create two threads that will act as counters.
*  The first thread counts up to 20.
*  After the first thread reaches 20, the second thread counts down to 0.
*
*/


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int counter = 0;
//the mutex, condition variable, and boolean flag
//will ensure proper synchronization between threads
std::mutex counter_mutex;
std::condition_variable cv;
bool reached_20 = false;

//first thread will count up to 20 and print each number
void increment_counter() {
    try {
        std::lock_guard<std::mutex> lock(counter_mutex);
        std::cout << "First Thread Counting Up to 20: " << std::endl;
        for (int i = 0; i <= 20; ++i) {
            counter = i;
            std::cout << counter << std::endl;
        }
        //once the for loop is finished, the boolean = true,
        //so thread two can begin
        reached_20 = true;
        cv.notify_one();
    } catch (const std::exception& e) {
        std::cerr <<"Error in First Thread: " << e.what() << std::endl;
    }
}

//second thread will count down to 0 and print each number
void decrement_counter() {
    try {
        std::unique_lock<std::mutex> lock(counter_mutex);
        //the condition variable requires that the second thread waits until
        //the boolean = true before it can begin
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
        //starts both threads
        std::thread firstThread(increment_counter);
        std::thread secondThread(decrement_counter);
        
        //main thread waits for the first and second threads to complete before exiting
        firstThread.join();
        secondThread.join();
    } catch (const std::exception& e) {
        std::cerr << "Error in Main Class: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

