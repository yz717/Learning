#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),right(right) {}
};

// 前序遍历非递归实现
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ret;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    // 1. 先访问左路节点
    // 2. 同样的方式访问左路节点的右子树


    while(cur || !st.empty()) {
        while(cur) { // 访问左路节点
            ret.push_back(cur->val); // 入栈时就访问
            st.push(cur);
            cur = cur->left;
        }
        
        // 左路走完，访问右子树
        TreeNode* top = st.top();
        st.pop();
        cur = top->right;
        
    }
    return ret;
}

// 中序遍历非递归实现
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ret;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    // 1. 先访问左路节点
    // 2. 同样的方式访问左路节点的右子树

    while(cur || !st.empty()) {
        while(cur) {
            st.push(cur);
            cur = cur->left;
        }

        TreeNode* top = st.top();
        st.pop();
        ret.push_back(top->val); // 出栈时访问

        cur = top->right;
    }
    return ret;
}

// 后序遍历非递归实现
vector<int> postorderTraversal(TreeNode* root) {  
    vector<int> ret;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    TreeNode* prev = nullptr; // 记录上一次访问的节点

    while(cur || !st.empty()) {
        while(cur) {
            st.push(cur);
            cur = cur->left;
        }

        TreeNode* top = st.top();
        if(top->right == nullptr || top->right == prev) {
            ret.push_back(top->val);
            st.pop();
            prev = top;
        } else {
            cur = top->right;
        }
    }
    return ret;
}
int main() {
    // 构建一个简单的二叉树进行测试
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    vector<int> ret = preorderTraversal(root);
    // 1 2 4 5 3 6 7
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;

    ret = inorderTraversal(root);
    // 4 2 5 1 6 3 7
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;

    ret = postorderTraversal(root);
    // 4 5 2 6 7 3 1
    for(int val : ret) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}