#include <iostream>
using namespace std;
const int N = 1e6 + 10;
int tree[N][26], p[N], e[N];
int idx;

void insert(string& s) {
    int cur = 0;
    p[cur]++;
    for(auto& ch : s) {
        int path = ch - 'a';
        if(tree[cur][path] == 0) tree[cur][path] = ++idx;
        cur = tree[cur][path];
        p[cur]++;
    }
    e[cur]++;
}

int find(string& s) {
    int cur = 0;
    for(auto& ch : s) {
        int path = ch - 'a';
        if(tree[cur][path] == 0) return 0;
        cur = tree[cur][path];
    }
    return e[cur];
}

int find_pre(string& s) {
    int cur = 0;
    for(auto& ch : s) {
        int path = ch - 'a';
        if(tree[cur][path] == 0) return 0;
        cur = tree[cur][path];
    }
    return p[cur];
}
int main() {
    
    return 0;
}