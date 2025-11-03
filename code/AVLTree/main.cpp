#include "AVLTree.hpp" // 只需要包含 .hpp 文件
#include <iostream>
#include <vector>
#include <string>
#include <cassert>   
#include <stdlib.h>  
#include <time.h>    

// 辅助测试函数
void RunTest(const std::string& testName, const std::vector<int>& keys) {
    std::cout << "--- STARTING TEST: " << testName << " ---" << std::endl;
    AVLTree<int> tree;

    for (int key : keys) {
        std::cout << "Inserting: " << key << std::endl;
        tree.Insert(key);

        // 每次插入后都进行全套体检
        assert(tree.isBST());
        assert(tree.isBalanced());
        assert(tree.hasCorrectParentPointers());
    }

    std::cout << "--- TEST PASSED: " << testName << " ---" << std::endl << std::endl;
}

// 压力测试
void FuzzTest(int numInsertions, int keyRange) {
    std::cout << "--- STARTING FUZZ TEST (" << numInsertions << " insertions) ---" << std::endl;
    srand(time(NULL));
    AVLTree<int> fuzz_tree;

    for (int i = 0; i < numInsertions; ++i) {
        int key = rand() % keyRange;
        fuzz_tree.Insert(key);

        // 为提高效率，可以每 1000 次检查一次
        if (i % 1000 == 999) {
            std::cout << "Fuzz test checkpoint " << i+1 << "/" << numInsertions << std::endl;
            assert(fuzz_tree.isBST());
            assert(fuzz_tree.isBalanced());
            assert(fuzz_tree.hasCorrectParentPointers());
        }
    }
    
    // 最后再检查一次
    std::cout << "Final check..." << std::endl;
    assert(fuzz_tree.isBST());
    assert(fuzz_tree.isBalanced());
    assert(fuzz_tree.hasCorrectParentPointers());

    std::cout << "--- FUZZ TEST PASSED ---" << std::endl << std::endl;
}

int main() {
    
    // 1. 专门测试四种旋转
    RunTest("RR Rotation", {10, 20, 30});
    RunTest("LL Rotation", {30, 20, 10});
    RunTest("LR Rotation", {30, 10, 20});
    RunTest("RL Rotation", {10, 30, 20});

    // 2. 测试你原来的数组 (会触发多种旋转)
    RunTest("Complex Sequence (User's)", {10, 20, 30, 25, 28, 27, 5});

    // 3. 更多复杂测试
    RunTest("Sequential Insertion", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    RunTest("Reverse Sequential Insertion", {10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
    RunTest("Duplicates Test", {10, 10, 10, 20, 5, 20, 5, 10});
    
    // 4. 压力测试
    FuzzTest(20000, 50000); // 插入 20,000 个 0-49999 之间的随机数

    std::cout << "========= ALL TESTS PASSED SUCCESSFULLY! ==========" << std::endl;

    return 0;
}