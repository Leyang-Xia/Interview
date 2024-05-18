#include <iostream>
#include <vector>

// 调整堆，使得以节点i为根的子树满足堆的性质
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i; // 初始化根节点为最大值
    int left = 2 * i + 1; // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 比较左子节点和根节点的值
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // 比较右子节点和当前最大节点的值
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // 如果最大值不是根节点，则交换它们，并递归调整被交换的子树
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// 堆排序函数
void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }

    // 逐步取出堆顶元素，并重建堆
    for (int i = n - 1; i >= 0; --i) {
        swap(arr[0], arr[i]); // 将堆顶元素（最大值）与当前最后一个元素交换
        heapify(arr, i, 0); // 调整剩余元素，使其满足堆的性质
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
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();
    std::cout << "原始数组为：";
    printArray(arr);
    heapSort(arr);
    std::cout << "排序后的数组为：";
    printArray(arr);
    return 0;
}
