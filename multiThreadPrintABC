#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
std::mutex mtx;
std::condition_variable cv;
int turn = 0;

void print(int id, char ch) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [id] { return turn == id; });
        std::cout << ch;
        turn = (id + 1) % 3;
        cv.notify_all();
    }
}


int main() {
    std::thread t1(print, 0, 'A');
    std::thread t2(print, 1, 'B');
    std::thread t3(print, 2, 'C');

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
