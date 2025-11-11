#include <iostream>
#include <vector>

using namespace std;

class UnionFindSet {
public:
    UnionFindSet(int n) : _parent(n, -1) {}
    int Find(int x) {
        while(_parent[x] >= 0) {
            x = _parent[x];
        }
        return x;
    }

    // int Find(int x) {
    //     if(_parent[x] < 0) return x;
    //     else return Find(_parent[x]);
    // }
    
    int FindWithPathCompressionIterative(int x) {
        int root = x;
        // find root
        while(_parent[root] >= 0) {
            root = _parent[root];
        }

        // Path compression
        while(x != root) {
            int parent = _parent[x];
            _parent[x] = root;
            x = parent;
        }
        return root;
    }

    // int FindWithPathCompression(int x) {
    //     if(_parent[x] < 0) return x;
    //     return _parent[x] = FindWithPathCompression(_parent[x]);
    // }
    void Union(int x, int y) {
        int rootX = Find(x);
        int rootY = Find(y);
        if(rootX == rootY) return;
        // Merge y into x
        _parent[rootX] += _parent[rootY];
        _parent[rootY] = rootX;
    }

    size_t Size() {
        size_t size = 0;
        for(auto e : _parent) {
            if(e < 0) ++size;
        }
        return size;
    }
private:
    vector<int> _parent;
};

void test() {
    UnionFindSet ufs(10);
    ufs.Union(1, 2);
    ufs.Union(2, 3);
    ufs.Union(4, 5);
    ufs.Union(6, 7);
    ufs.Union(5, 6);
    cout << "Find 3: " << ufs.Find(3) << endl;
    cout << "Find 7: " << ufs.Find(7) << endl;
    cout << "Number of disjoint sets: " << ufs.Size() << endl;
}

int main() {
    test();
    return 0;
}