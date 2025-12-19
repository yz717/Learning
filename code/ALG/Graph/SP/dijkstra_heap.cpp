#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int N = 1e5 + 10;
typedef pair<int, int> PII;
vector<PII> adj[N];
int dist[N];
bool st[N];
int n, m, s;

void dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, s}); //  <距离， 编号>
    while(heap.size()) {
        auto p = heap.top(); heap.pop();
        int u = p.second;
        if(st[u]) continue;
        st[u] = true;
        for(auto& pair : adj[u]) {
            int v = pair.first;
            int w = pair.second;
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                heap.push({dist[v], v});
            }
        }
    }
    for(int i = 1; i <= n; i++) cout << dist[i] << " ";
}
int main() {
    cin >> n >> m >> s;
    int u, v, w;
    for(int i = 1; i <= m; i++){
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    dijkstra();
    return 0;
}