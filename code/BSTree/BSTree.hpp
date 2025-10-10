// BSTree.hpp
#ifndef BSTREE_HPP
#define BSTREE_HPP
#include <iostream>

template <class K>
struct BSTNode {
    K key_;
    BSTNode *left_;
    BSTNode *right_;

    BSTNode(const K &key) : key_(key), left_(nullptr), right_(nullptr) {}
};

template <class K>
class BSTree {
    using Node = BSTNode<K>;
public:
    BSTree() : root_(nullptr) {}
    ~BSTree();

    bool InsertIter(const K &key);
    bool InsertRec(const K &key);

    bool SearchIter(const K &key);
    bool SearchRec(const K &key);

    bool DeleteIter(const K &key);
    bool DeleteRec(const K &key);

    void Inorder() const;
private:
    Node *root_;

    bool InsertRecHelper(Node *&node, const K &key); // pass by reference
    bool SearchRecHelper(Node *node, const K &key);
    bool DeleteRecHelper(Node *&node, const K &key); // pass by reference
    void InorderHelper(Node *node) const;
    void Destroy(Node *node);
};

template <class K>
bool BSTree<K>::InsertIter(const K &key) {
    if(!root_) {
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
    if(key < parent->key_) {
        parent->left_ = new Node(key);
    } else {
        parent->right_ = new Node(key);
    }
    return true;
}


template <class K>
bool BSTree<K>::InsertRec(const K &key) {
    return InsertRecHelper(root_, key);
}

template <class K>
bool BSTree<K>::InsertRecHelper(Node *&node, const K &key) {
    if(node == nullptr) {
        node = new Node(key);
        return true;
    }
    if(key < node->key_) {
        return InsertRecHelper(node->left_, key);
    } else if(key > node->key_) {
        return InsertRecHelper(node->right_, key);
    } else {
        return false; // key already exists
    }
}

template <class K>
bool BSTree<K>::SearchIter(const K &key) {
    Node *cur = root_;
    while(cur) {
        if(key < cur->key_) {
            cur = cur->left_;
        } else if(key > cur->key_) {
            cur = cur->right_;
        } else {
            return true; // key found
        }
    }
    return false; // key not found
}

template <class K>
bool BSTree<K>::SearchRec(const K &key) {
    return SearchRecHelper(root_, key);
}

template <class K>
bool BSTree<K>::SearchRecHelper(Node *node, const K &key) {
    if(node == nullptr) return false;
    if(key < node->key_) {
        return SearchRecHelper(node->left_, key);
    } else if(key > node->key_) {
        return SearchRecHelper(node->right_, key);
    } else {
        return true;
    }
}

template <class K>
bool BSTree<K>::DeleteRec(const K& key) {
    return DeleteRecHelper(root_, key);
}

template <class K>
bool BSTree<K>::DeleteRecHelper(Node *&node, const K &key) {
    if(node == nullptr) return false;

    if(key < node->key_) {
        return DeleteRecHelper(node->left_, key);
    } else if(key > node->key_) {
        return DeleteRecHelper(node->right_, key);
    } else {
        Node* tmp = node;

        if(node->left_ == nullptr) {
            // 直接修改 node。因为 node 是引用，
            // 即父节点的指针 (parent->left_ 或 parent->right_)也被同步修改为指向 node 的右孩子
            node = node->right_;
            delete tmp;
            return true;
        } else if(node->right_ == nullptr) {
            node = node->left_;
            delete tmp;
            return true;
        } else {
            // 找到中序后继节点 (右子树的最小节点)
            Node* successor = node->right_;
            while (successor->left_) {
                successor = successor->left_;
            }

            // 将后继节点的值复制到当前节点
            node->key_ = successor->key_;
            
            // 在右子树中递归地删除那个后继节点
            return DeleteRecHelper(node->right_, successor->key_);
        }
    }
}

template <class K>
bool BSTree<K>::DeleteIter(const K &key) {
    // 查找要删除的节点及其父节点
    Node* cur = root_;
    Node* parent = nullptr;
    while(cur) {
        if(cur->key_ == key) break;

        parent = cur;
        if(key < cur->key_) cur = cur->left_;
        else cur = cur->right_;
    }

    // 如果循环结束时 cur 为空，说明树中没有这个 key
    if(cur == nullptr) return false;

    // 左子树空，用右子女填补
    if(cur->left_ == nullptr) {
        if(parent == nullptr) {
            root_ = cur->right_;
        } else if(parent->left_ == cur) {
            parent->left_ = cur->right_;
        } else {
            parent->right_ = cur->right_;
        }
        delete cur;
    } 
    // 右子树空，用左子女填补
    else if(cur->right_ == nullptr) {
        if(parent == nullptr) {
            root_ = cur->left_;
        } else if(parent->left_ == cur) {
            parent->left_ = cur->left_;
        } else {
            parent->right_ = cur->left_;
        }
        delete cur;
    }
    // 左右子树都不为空，找到 cur 的中序后继 (successor)，也就是其右子树中的最小节点填补
    else {
        Node* successor_parent = cur;
        Node* successor = cur->right_;
        while(successor->left_) {
            successor_parent = successor;
            successor = successor->left_;
        }
        cur->key_ = successor->key_;

        if(successor_parent->left_ == successor) {
            successor_parent->left_ = successor->right_;
        } else {
            successor_parent->right_ = successor->right_;
        }

        delete successor;
    }
    return true;
}

template <class K>
void BSTree<K>::Inorder() const {
    InorderHelper(root_);
    std::cout << std::endl;
}

template <class K>
void BSTree<K>::InorderHelper(Node *node) const {
    if(node == nullptr) return;
    InorderHelper(node->left_);
    std::cout << node->key_ << " ";
    InorderHelper(node->right_);
}

template <class K>
BSTree<K>::~BSTree() {
    Destroy(root_);
}

template <class K>
void BSTree<K>::Destroy(Node *node) {
    if(node == nullptr) return;
    Destroy(node->left_);
    Destroy(node->right_);
    delete node;
}

#endif // BSTREE_HPP
