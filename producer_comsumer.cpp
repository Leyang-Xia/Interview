#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <random>


using namespace std;

mutex mtx;
condition_variable cv;
queue<int> buffer;
const int bufferSize = 10;

void consumer() {
    for (int i = 0; i< 20; i++) {
        this_thread::sleep_for(std::chrono::seconds(random() % 5));
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [](){ return !buffer.empty(); });
        int val = buffer.front();
        buffer.pop();
        cout << "Consumed: " << val << endl;
        cv.notify_one();
    }
}

void producer() {
    for (int i = 0; i< 20; i++) {

        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [](){ return buffer.size() < bufferSize; });
        buffer.push(i);
        cout << "Produced: " << i << endl;
        cv.notify_one();
    }
}



int main() {
    thread consumer_thread(consumer);
    thread producer_thread(producer);

    producer_thread.join();
    consumer_thread.join();
    return 0;
}
