#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include <iostream>

#include <vector>     
#include <algorithm>  
#include <cmath>      
#include <stdexcept>  

template <class K>
struct AVLNode {
    K key_;
    AVLNode *left_;
    AVLNode *right_;
    AVLNode *parent_;
    int bf_; // balance factor

    AVLNode(const K &key) : key_(key), left_(nullptr), right_(nullptr), parent_(nullptr), bf_(0) {}
};

template <class K>
class AVLTree {
    using Node = AVLNode<K>;
public:
    bool Insert(const K &key);
    AVLTree() : root_(nullptr) {}

    // 验证接口
    bool isBST();
    bool isBalanced();
    bool hasCorrectParentPointers();
private:
    Node *root_;
    void RotateL(Node* parent);
    void RotateR(Node* parent);
    void RotateLR(Node* parent);
    void RotateRL(Node* parent);

    // 验证辅助函数
    void _InOrder(Node* node, std::vector<K>& keys);
    int _getHeightAndCheckBalance(Node* node);
    bool _checkParentPointers(Node* node);

};


template <class K>
bool AVLTree<K>::Insert(const K &key) {
    if(root_ == nullptr) {
        root_ = new Node(key);
        return true;
    }

    Node *cur = root_;
    Node *parent = nullptr;
    while(cur) {
        parent = cur;
        if(key < cur->key_) {
            cur = cur->left_;
        } else if(key > cur->key_) {
            cur = cur->right_;
        } else {
            return false; // key already exists
        }
    }

    Node *newnode = new Node(key);
    newnode->parent_ = parent;
    if(key < parent->key_) {
        parent->left_ = newnode;
    } else {
        parent->right_ = newnode;
    }

    // 此时已经完成了二叉搜索树的插入，接下来调整平衡因子
    // 插入节点只会影响其祖先的平衡因子，故需要一路往上走
    cur = newnode; //从新节点开始
    while(parent) {
        // 插入右子树，说明右子树高度加1， 故bf++
        if(cur == parent->right_) parent->bf_++;
        else parent->bf_--;

        if(parent->bf_ == 0) { //平衡因子为0，说两边一样高了不影响祖先，直接结束了
            break;
        } else if(parent->bf_ == 1 || parent->bf_ == -1) { // 平衡因子为 1 or -1 说明树变高了，需要继续更新
            cur = parent;
            parent = parent->parent_;
        } else { //平衡因子为 2 or -2 说明失衡了，需要旋转
            if(parent->bf_ == 2) {
                if(cur->bf_ == 1) { // RR
                    RotateL(parent);
                    parent->bf_ = 0;
                    cur->bf_ = 0;
                } else { // RL
                    RotateRL(parent);
                }
            } else { // -2
                if(cur->bf_ == -1) { // LL
                    RotateR(parent);
                    parent->bf_ = 0;
                    cur->bf_ = 0;
                } else { // LR
                    RotateLR(parent);   
                }
            }
            break; // 旋转后高度不变，结束
        }
    }
    return true;
}

template <class K>
void AVLTree<K>::RotateL(Node* parent) {
    Node *subR = parent->right_;
    Node *subRL = subR->left_;
    Node *gparent = parent->parent_; // 记录parent 的父节点

    // 处理subRL 给它找孩子找爹
    if(subRL) subRL->parent_ = parent;

    // 处理parent
    parent->right_ = subRL;
    parent->parent_ = subR;

    // 处理subR
    subR->left_ = parent;
    subR->parent_ = gparent;
    if(gparent == nullptr) {
        root_ = subR;
    } else {
        if(gparent->left_ == parent) gparent->left_ = subR;
        else gparent->right_ = subR;
    }
}

template <class K>
void AVLTree<K>::RotateR(Node* parent) {
    Node *subL = parent->left_;
    Node *subLR = subL->right_;
    Node *gparent = parent->parent_;

    // 处理subLR 找孩子找爹
    if(subLR) subLR->parent_ = parent;

    // 处理pareent
    parent->left_ = subLR;
    parent->parent_ = subL;

    // 处理subL
    subL->right_ = parent;
    subL->parent_ = gparent;
    if(gparent == nullptr) {
        root_ = subL;
    } else {
        if(gparent->left_ == parent) gparent->left_ = subL;
        else gparent->right_ = subL;
    }
}

template <class K>
void AVLTree<K>::RotateLR(Node* parent) {
    Node *subL = parent->left_;
    Node *subLR = subL->right_;
    int bf = subLR->bf_;
    RotateL(subL);
    RotateR(parent);
    // 根据bf 更新parent 和 subL 的平衡因子
    if(bf == 1) {
        parent->bf_ = 0;
        subL->bf_ = -1;
    } else if(bf == -1) {
        parent->bf_ = 1;
        subL->bf_ = 0;
    } else {
        parent->bf_ = 0;
        subL->bf_ = 0;  
    }
    subLR->bf_ = 0;
}

template <class K>
void AVLTree<K>::RotateRL(Node* parent) {
    Node *subR = parent->right_;
    Node *subRL = subR->left_;
    int bf = subRL->bf_;
    RotateR(subR);
    RotateL(parent);
    // 根据bf 更新parent 和 subR 的平衡因子
    if(bf == 1) {
        parent->bf_ = -1;
        subR->bf_ = 0;
    } else if(bf == -1) {
        parent->bf_ = 0;
        subR->bf_ = 1;
    } else {
        parent->bf_ = 0;
        subR->bf_ = 0;  
    }
    subRL->bf_ = 0;
}

// --- 验证函数实现 ---
template <class K>
bool AVLTree<K>::isBST() {
    std::vector<K> keys;
    _InOrder(root_, keys);
    for (size_t i = 0; i < keys.size() - 1; ++i) {
        if (keys[i] >= keys[i+1]) { 
            std::cerr << "BST FAILED: " << keys[i] << " >= " << keys[i+1] << std::endl;
            return false;
        }
    }
    return true;
}

template <class K>
bool AVLTree<K>::isBalanced() {
    if (_getHeightAndCheckBalance(root_) == -1) {
        return false;
    }
    return true;
}

template <class K>
bool AVLTree<K>::hasCorrectParentPointers() {
    if (root_ && root_->parent_ != nullptr) {
         std::cerr << "ROOT PARENT FAILED: root->parent is not NULL" << std::endl;
        return false;
    }
    return _checkParentPointers(root_);
}

template <class K>
void AVLTree<K>::_InOrder(Node* node, std::vector<K>& keys) {
    if (node == nullptr) return;
    _InOrder(node->left_, keys);
    keys.push_back(node->key_);
    _InOrder(node->right_, keys);
}

template <class K>
int AVLTree<K>::_getHeightAndCheckBalance(Node* node) {
    if (node == nullptr) {
        return 0; // 空节点高度为 0
    }

    int leftHeight = _getHeightAndCheckBalance(node->left_);
    if (leftHeight == -1) return -1; 

    int rightHeight = _getHeightAndCheckBalance(node->right_);
    if (rightHeight == -1) return -1; 

    if (std::abs(rightHeight - leftHeight) > 1) {
         std::cerr << "BALANCE FAILED: Node " << node->key_ << " has heights L:" 
                   << leftHeight << ", R:" << rightHeight << std::endl;
        return -1;
    }

    if (node->bf_ != (rightHeight - leftHeight)) {
         std::cerr << "BF_ VALUE FAILED: Node " << node->key_ << " stored bf=" 
                   << node->bf_ << " but calculated bf=" 
                   << (rightHeight - leftHeight) << std::endl;
        return -1;
    }
    return 1 + std::max(leftHeight, rightHeight);
}

template <class K>
bool AVLTree<K>::_checkParentPointers(Node* node) {
    if (node == nullptr) {
        return true;
    }
    if (node->left_) {
        if (node->left_->parent_ != node) {
            std::cerr << "PARENT FAILED: " << node->left_->key_ << "->parent is ";
            if (node->left_->parent_) {
                std::cerr << node->left_->parent_->key_;
            } else {
                std::cerr << "NULL";
            }
            std::cerr << " but should be " << node->key_ << std::endl;
            return false;
        }
        if (!_checkParentPointers(node->left_)) return false;
    }
    if (node->right_) {
         if (node->right_->parent_ != node) {
             std::cerr << "PARENT FAILED: " << node->right_->key_ << "->parent is ";
            if (node->right_->parent_) {
                std::cerr << node->right_->parent_->key_;
            } else {
                std::cerr << "NULL";
            }
             std::cerr << " but should be " << node->key_ << std::endl;
            return false;
        }
        if (!_checkParentPointers(node->right_)) return false;
    }
    return true;
}

#endif // AVLTREE_HPP