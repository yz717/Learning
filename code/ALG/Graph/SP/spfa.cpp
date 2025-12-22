#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> PII;
const int N = 1e4 + 10, INF = 2147483647;
vector<PII> adj[N];
int dist[N];
bool st[N]; // 标记结点是否在队列中
int n, m, s;

void spfa() {
    for(int i = 1; i <= n; i++) dist[i] = INF;
    dist[s] = 0; st[s] = true;
    queue<int> q;
    q.push(s);
    while(q.size()) {
        int u = q.front(); q.pop(); st[u] = false;
        for(auto& p : adj[u]) {
            int v = p.first;
            int w = p.second;
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if(!st[v]) q.push(v);
                st[v] = true;
            }
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
    spfa();
    return 0;
}