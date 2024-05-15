#include <iostream>
#include <vector>

// 合并两个有序的子数组到一个临时数组，再复制回原数组
void merge(std::vector<int>& arr, int left, int mid, int right) {

    // 创建一个临时数组
    std::vector<int> tempArr(right - left + 1);

    int i = left;     // 左子数组的起始索引
    int j = mid + 1;  // 右子数组的起始索引
    int k = 0;        // 临时数组的起始索引

    // 合并左子数组和右子数组到临时数组
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            tempArr[k++] = arr[i++];
        } else {
            tempArr[k++] = arr[j++];
        }
    }

    // 复制左子数组的剩余元素
    while (i <= mid) {
        tempArr[k++] = arr[i++];
    }

    // 复制右子数组的剩余元素
    while (j <= right) {
        tempArr[k++] = arr[j++];
    }

    // 将临时数组的内容复制回原数组
    for (k = 0; k < tempArr.size(); ++k) {
        arr[left + k] = tempArr[k];
    }
}

// 归并排序函数
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // 递归排序左右子数组
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // 合并左右子数组
        merge(arr, left, mid, right);
    }
}

// 打印数组
void printArray(const std::vector<int>& arr) {
    for (auto num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    std::cout << "Original: ";
    printArray(arr);

    mergeSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted: ";
    printArray(arr);
    return 0;
}
