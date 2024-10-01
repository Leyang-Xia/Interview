#include <iostream>
#include <mutex>
#include <memory>
using namespace std;

class Singleton {
public:
    ~Singleton() {
        std::cout << "destructor called!" << std::endl;
    }
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;

    static shared_ptr<Singleton> getInstance() {
        if (m_instance_ptr == nullptr) {
            lock_guard<mutex> lock(m);
            if (m_instance_ptr == nullptr) {
                m_instance_ptr.reset(new Singleton());
            }
        }
        return m_instance_ptr;
    }
private:
    Singleton() {
        cout << "Singleton constructor" << endl;
    }
    static shared_ptr<Singleton> m_instance_ptr;
    static mutex m;
};

shared_ptr<Singleton> Singleton::m_instance_ptr = nullptr;
mutex Singleton::m;

int main() {
    auto instance1 = Singleton::getInstance();
    auto instance2 = Singleton::getInstance();

    cout << "Instances are equal: " << (instance1 == instance2) << endl;
    return 0;
}
