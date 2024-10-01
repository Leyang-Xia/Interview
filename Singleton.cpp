#include <iostream>
using namespace std;

//c++11标准中有一个特性：如果当变量在初始化的时候，并发同时进入声明语句，并发线程将会阻塞等待初始化结束。
//这样保证了并发线程在获取静态局部变量的时候一定是初始化过的，所以具有线程安全性。
class Singleton {
public:
    ~Singleton() {}
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;

    static Singleton & getInstance() {
        static Singleton instance;
        return instance;
    }
private:
    Singleton() {
        cout << "Singleton constructor" << endl;
    }
};


int main() {
    static Singleton & instance = Singleton::getInstance();
    return 0;
}
