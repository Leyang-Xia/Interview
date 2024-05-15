#include <iostream>
#include <vector>
#include <cstdlib> // 用于rand()和srand()
#include <ctime>   // 用于time()


// 随机化基准值选择并分割数组
int partition(std::vector<int>& arr, int low, int high) {
    // 随机选择基准值，并将其与最后一个元素交换
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);

    int pivot = arr[high];
    int i = low;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

// 快速排序函数
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 打印数组元素
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::srand(std::time(nullptr)); // 用当前时间作为随机数生成的种子

    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();
    std::cout << "原始数组为：";
    printArray(arr);
    quickSort(arr, 0, n - 1);
    std::cout << "排序后的数组为：";
    printArray(arr);
    return 0;
}
