#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, int> PII;
const int N = 1e4 + 10, INF = 2147483647;
vector<PII> adj[N];
int dist[N];
int n, m, s;

void BF() {
    for(int i = 1; i <= n; i++) dist[i] = INF;
    dist[s] = 0;

    for(int i = 1; i < n; i++) {
        bool change = false;
        for(int u = 1; u <= n; u++) {
            if(dist[u] == INF) continue;
            for(auto& p : adj[u]) {
                int v = p.first;
                int w = p.second;
                if(dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    change = true;
                }
            }
        }
        if(!change) break;
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
    BF();
    return 0;
}