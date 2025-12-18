#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int N = 110;
vector<int> adj[N]; 
int in_degree[N]; 
int n;
bool topo_sort() {
    queue<int> q;
    vector<int> result;
    for(int i = 1; i <= n; i++) {
        if(in_degree[i] == 0) q.push(i);
    }
    while(q.size()) {
        int u = q.front(); 
        q.pop();
        result.push_back(u); 
        for(auto v : adj[u]) {
            in_degree[v]--;
            if(in_degree[v] == 0) q.push(v);
        }
    }
    if(result.size() == n) {
        for(int x : result) cout << x << " ";
        cout << endl;
        return true;
    } else {
        return false; // 图中有环，无法拓扑排序
    }
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int v;
        while(cin >> v && v) {
            adj[i].push_back(v);
            in_degree[v]++;
        }
    }
    return 0;
}