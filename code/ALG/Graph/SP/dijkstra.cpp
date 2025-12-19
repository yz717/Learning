#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, int> PII;
const int N = 1e4 + 10, INF = 2147483647;
int n, m, s;
vector<PII> adj[N];
int dist[N];
bool st[N];
void dijkstra() {
    for(int i = 1; i <= n; i++) dist[i] = INF;
    dist[s] = 0;

    for(int i = 1; i < n; i++) {
        int u = -1; // 标记在为确定的点中最短路的点
        for(int j = 1; j <= n; j++) 
            if(!st[j] && (u == -1 || dist[j] < dist[u])) u = j;
        st[u] = true;
        // 松弛操作
        for(auto p : adj[u]) {
            int v = p.first, w = p.second;
            if(dist[u] + w < dist[v]) dist[v] = dist[u] + w;
        }
    }
    for(int i = 1; i <= n; i++) cout << dist[i] << " ";
}
int main() {
    cin >> n >> m >> s;
    int u, v, w;
    for(int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    dijkstra();
    return 0;
}