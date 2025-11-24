#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

void BubbleSort(vector<int>& arr) {
    int n = arr.size();
    // 外层循环控制趟数 n - 1 趟
    for(int i = 1; i < n; ++i) {
        // 内层循环控制每一趟比较的次数
        for(int j = n -1; j >= i; --j) {
            if(arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
            }
        }
    }
}


// void BubbleSort(vector<int>& arr) {
//     int n = arr.size();
//     bool exchange;
//     for(int i = 1; i < n; ++i) {
//         exchange = false;
//         for(int j = n - 1; j >= i; --j) {
//             if(arr[j] < arr[j - 1]) {
//                 swap(arr[j], arr[j - 1]);
//                 exchange = true;
//             }
//         }
//         if(exchange == false) return;
//     }
// }

void InsertSort(vector<int>& arr) {
    int n = arr.size();
    // 维护一个有序区间 arr[0...i-1]
    for(int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        // 在有序区间中找到合适的位置插入 key
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void BinaryInsertSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 1; i < n; ++i) {
        int key = arr[i];
        int left = 0;
        int right = i - 1;
        // 在有序区间 arr[0...i-1] 中使用二分查找找到 key 的插入位置
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(arr[mid] > key) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        for(int j = i - 1; j >= left; --j) {
            arr[j + 1] = arr[j];
        }
        arr[left] = key;
    }
}

void ShellSort(vector<int>& arr) {
    int n = arr.size();
    int gap = n;
    while(gap > 1) {
        gap = gap / 3 + 1; // 动态缩小增量
        // 相关与以gap为一个元素的插入排序
        for(int i = gap; i < n; ++i) {
            int key = arr[i];
            int j = i - gap;
            while(j >= 0 && arr[j] > key) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = key;
        }
    }
}

void SelectSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for(int j = i + 1; j < n; ++j) {
            if(arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if(minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

void HeapSort(vector<int>& arr) {
    int n = arr.size();
    priority_queue<int> maxHeap;
    for(int i = 0; i < n; ++i) maxHeap.push(arr[i]);
    for(int i = 0; i < n; ++i) {
        arr[n - 1 - i] = maxHeap.top();
        maxHeap.pop();
    }
}

void MergeSort(vector<int>& arr, int left, int right) {
    if(left >= right) return;
    int mid = left + (right - left) / 2;
    MergeSort(arr, left, mid);
    MergeSort(arr, mid + 1, right);
    // Merge two sorted halves
    vector<int> tmp(right - left + 1);
    int cur1 = left, cur2 = mid + 1, i = 0;
    while(cur1 <= mid && cur2 <= right) 
        tmp[i++] = (arr[cur1] <= arr[cur2]) ? arr[cur1++] : arr[cur2++];
    while(cur1 <= mid) tmp[i++] = arr[cur1++];
    while(cur2 <= right) tmp[i++] = arr[cur2++];

    for(int i = left; i <= right; ++i) 
        arr[i] = tmp[i - left];
}

void MergeSortIterative(vector<int>& arr) {
    int n = arr.size();
    // 当前每个子段的大小
    for(int size = 1; size < n; size *= 2) {
        // 每次合并两个子段
        for(int left = 0; left < n - size; left += 2 * size) {
            // 左段结尾
            int mid = left + size - 1; 
            // 右段结尾
            int right = min(left + 2 * size - 1, n - 1); 
            // Merge arr[left...mid] and arr[mid+1...right]
            vector<int> tmp(right - left + 1);
            int cur1 = left, cur2 = mid + 1, i = 0;
            while(cur1 <= mid && cur2 <= right) 
                tmp[i++] = (arr[cur1] <= arr[cur2]) ? arr[cur1++] : arr[cur2++];
            while(cur1 <= mid) tmp[i++] = arr[cur1++];
            while(cur2 <= right) tmp[i++] = arr[cur2++];

            for(int i = left; i <= right; ++i) 
                arr[i] = tmp[i - left];
        }
    }
}

void LSDRadixSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    int exp = 1; // 1, 10, 100...

    while (maxVal / exp > 0) {
        vector<int> bucket[10];
        for (int num : arr)
            bucket[(num / exp) % 10].push_back(num);

        int idx = 0;
        for (int i = 0; i < 10; i++)
            for (int num : bucket[i])
                arr[idx++] = num;

        exp *= 10;
    }
}

void CountSort(vector<int>& arr) {
    int n = arr.size();

    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());

    int range = maxVal - minVal + 1;
    vector<int> count(range, 0);
    vector<int> nums(n);

    // 统计次数
    for(auto num : arr) count[num - minVal]++;

    // 统计前缀和
    for(int i = 1; i < range; ++i) count[i] += count[i-1];

    // 从后往前确定位置
    for(int i = n - 1; i >= 0; i--) {
        // 计算索引
        int idx = arr[i] - minVal;
        // count[idx] - 1 即为该元素在排序后数组中的位置
        nums[count[idx] - 1] = arr[i];
        count[idx]--;
    }

    arr = nums;
}

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    CountSort(arr);
    cout << "Sorted array: \n";
    for (int i : arr) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}