#include <iostream>
template <typename T>
class  shared_ptr {
private:
    int* count;
    T* ptr;
    void release() {
        if (ptr && --(*count) == 0) {
            delete ptr;
            delete count;
        }
    }
public:
    shared_ptr(T* ptr = nullptr) : ptr(ptr), count(new int(1)) {}
    shared_ptr(const shared_ptr<T>& other) {
        ptr = other.ptr;
        count = other.count;
        (*count) += 1;
    }
    shared_ptr(shared_ptr<T>&& other) : ptr(other.ptr), count(other.count) {
        other.count = nullptr;
        other.ptr = nullptr;
    }

    ~shared_ptr() {
        release();
    }

    shared_ptr<T>& operator=(const shared_ptr<T>& other) {
        if (*this != other) {
            release();
            this->ptr = other.ptr;
            this->count = other.count;
            (*count) += 1;
        }
        return *this;
    }

    shared_ptr<T>& operator=(shared_ptr<T>&& other) {
        if (*this != other) {
            release();
            this->ptr = other.ptr;
            this->count = other.count;
            other.ptr = nullptr;
            other.count = nullptr;
        }
        return *this;
    }

    int use_count() const{
        return *count;
    }

    T& operator*() {
        return *ptr;
    }
};

int main() {
    shared_ptr<int> ptr(new int(42));
    std::cout << "Value: " << *ptr << ", use count: " << ptr.use_count() << std::endl;

    shared_ptr<int> ptr2(std::move(ptr));
    std::cout << "Value: " << *ptr2 << ", use count: " << ptr2.use_count() << std::endl;

    shared_ptr<int> ptr3 = std::move(ptr2);
    std::cout << "Value: " << *ptr3 << ", use count: " << ptr3.use_count() << std::endl;
    return 0;
}

