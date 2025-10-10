#include "BSTree.hpp"

int arr[] = {5,3,7,6,8,4,2,1,0,9};
// test insertIter 
void test1() {
    BSTree<int> tree;
    for(int key : arr) {
        tree.InsertIter(key);
    }
    tree.Inorder(); // Expected output: 0 1 2 3 4 5 6 7 8 9
    std::cout << std::endl; 
}

// test insertRec
void test2() {
    BSTree<int> tree;
    for(int key : arr) {
        tree.InsertRec(key);
    }
    tree.Inorder(); // Expected output: 0 1 2 3 4 5 6 7 8 9
    std::cout << std::endl;
}

// test searchIter
void test3() {
    BSTree<int> tree;
    for(int key : arr) {
        tree.InsertRec(key);
    }
    for(int i = 0; i <= 9; i++) {
        if(!tree.SearchIter(i)) {
            std::cout << "Error: " << i << " not found!" << std::endl;
        }
    }
    if(tree.SearchIter(10)) {
        std::cout << "Error: 10 found!" << std::endl;
    } else {
        std::cout << "10 not found, as expected." << std::endl;
    }
}

// test searchRec
void test4() {
    BSTree<int> tree;
    for(int key : arr) {
        tree.InsertRec(key);
    }
    for(int i = 0; i <= 9; i++) {
        if(!tree.SearchRec(i)) {
            std::cout << "Error: " << i << " not found!" << std::endl;
        }
    }
    if(tree.SearchRec(10)) {
        std::cout << "Error: 10 found!" << std::endl;
    } else {
        std::cout << "10 not found, as expected." << std::endl;
    }
}

// test deleteIter
void test5() {
    BSTree<int> tree;
    for(int key : arr) {
        tree.InsertRec(key);
    }
    tree.Inorder(); // Expected output: 0 1 2 3 4 5 6 7 8 9
    std::cout << std::endl;

    for(int i = 0; i <= 9; i++) {
        tree.DeleteIter(i);
        tree.Inorder();
    }
}

// test deleteRec
void test6() {
    BSTree<int> tree;
    for(int key : arr) {
        tree.InsertRec(key);
    }
    tree.Inorder(); // Expected output: 0 1 2 3 4 5 6 7 8 9
    std::cout << std::endl;

    for(int i = 0; i <= 9; i++) {
        tree.DeleteRec(i);
        tree.Inorder();
    }
}

int main() {
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();
    return 0;
}